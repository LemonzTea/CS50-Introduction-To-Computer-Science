from flask import Flask, render_template, request
import random

# Create a flask application from this current file
app = Flask(__name__)

# Default webpage
@app.route("/")
def index():
    return render_template("index.html")

# Create a webpage page with /goodbye
@app.route("/goodbye")
def bye():
    return "Goodbye!"

# Create a webpage from a form submission
@app.route("/hello")
def hello():
    name = request.args.get("name")
    if not name:
        return render_template("failure.html")
    return render_template("hello.html", name=name)