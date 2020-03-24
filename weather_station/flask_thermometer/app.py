from flask import Flask

app = Flask(__name__)

@app.route('/')
def hello():
    return '''
    <h1>Hello, World!</h1>
    <h2>Welcome to my self-hosted web application.</h2>
    <p>Lorem Ipsum</p>
    <p>Another paragraph</p>
    '''
