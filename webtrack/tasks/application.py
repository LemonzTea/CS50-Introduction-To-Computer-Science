from flask import Flask, render_template, request, redirect, session
from flask_session import Session


app = Flask(__name__)

app.config["SESSION_PERMERNANT"] = False

# Where to save the data regarding the session
app.config["SESSION_TYPE"] = "filesystem"

# Enable session on app
Session(app)


@app.route("/")
def tasks():
    # Access "todos" in session, and create a list if empty
    if "todos" not in session:
        session["todos"]=[]

    return render_template("tasks.html", todos=session["todos"])

# State the list of methods this link takes
@app.route("/add", methods=["GET", "POST"])
def add():
    if request.method == "GET":
        return render_template("add.html")
    else:
        # Access data from a POST method
        todo = request.form.get("task")

        # Add task to session's todo list
        session["todos"].append(todo)
        return redirect("/")
        
        