#include<WiFi.h>
#include<PubSubClient.h>
#include<Dps310.h>

//Definitions for the deep sleep mode
#define uS_TO_S_FACTOR 1000000 //Converstion factor for micro seconds to seconds
#define TIME_TO_SLEEP 20 //Time ESP32 will go to sleep (in seconds)

RTC_DATA_ATTR int bootCount = 0; //Stores the wake up times in the variable bootCount in the RTC

void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason){
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by time"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n", wakeup_reason); break;
    }
}

//wLAN credentials
const char* ssid = "FRITZ!Box 7490";
const char* wifi_password = "01059047167980913948";

//Creates a Dps310 object
Dps310 Dps310PressureSensor = Dps310();

//MQTT settings
const char* mqtt_server = "192.168.178.62";
const char* mqtt_topic = "weather_stats";
//const char* mqtt_username = "";
//const char* mqtt_password = "";
const char* clientID = "weather_station";

//Initiate the wLAN and MQTT Client objects
WiFiClient wifiClient;
PubSubClient client(mqtt_server, 1883, wifiClient);

void setup() {
  Serial.begin(115200);
  
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));
  print_wakeup_reason(); //Serial print the wakeup reason
  

  Dps310PressureSensor.begin(Wire);

  Serial.print("\n Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (client.connect(clientID)) {
    Serial.println("Connected to MQTT Broker!");
  } else {
    Serial.println("Connection to MQTT Broker failed...");
  }  



/*========================================================*/
  //Actual task for DPS310
  float pressure;
  float temperature;
  uint8_t oversampling = 7;
  int16_t ret;
  char PressureValue[15];
  char TempValue[15];

  Serial.println();

  ret = Dps310PressureSensor.measurePressureOnce(pressure, oversampling);

  dtostrf(pressure, 8, 2, PressureValue);

  if (ret != 0) {
    Serial.print("Fail! ret = ");
    Serial.print(ret);
  } else if (client.publish(mqtt_topic, PressureValue)) {
    Serial.println(PressureValue);
    Serial.println(" Pascal");
  } else {
    Serial.println("Message failed to send. Reconnecting to MQTT Broker and trying again");
    client.connect(clientID);
    delay(10);
    client.publish(mqtt_topic, PressureValue);
  }

  ret = Dps310PressureSensor.measureTempOnce(temperature, oversampling);

  dtostrf(temperature, 8, 2, TempValue);

  if (ret != 0) {
    Serial.print("Fail! ret = ");
    Serial.print(ret);
  } else if (client.publish(mqtt_topic, TempValue)) {
    Serial.println(TempValue);
    Serial.println(" degree Celsius");
  } else {
    Serial.println("Message failed to send. Reconnecting to MQTT Broker and trying again");
    client.connect(clientID);
    delay(10);
    client.publish(mqtt_topic, TempValue);
  }  

  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  esp_deep_sleep_start();
}


void loop(){
}
