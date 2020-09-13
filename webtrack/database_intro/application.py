from flask import Flask, render_template, request, redirect
from cs50 import SQL

app = Flask(__name__)

# Connect to database
db = SQL("sqlite:///lecture.db")

@app.route("/")
def index():
    # Read information from database
    rows = db.execute("SELECT * FROM registrants")
    return render_template("index.html", rows=rows)


@app.route("/register", methods=["GET", "POST"])
def register():
    # Respond to a GET request
    if request.method == "GET":
        return render_template("register.html")

    # Respond to a POST registration request
    else:

        # Data Validation for Name
        name = request.form.get("name")
        if not name:
            return render_template("apology.html", message="You must provide a name.")

        # Data Validation for Email
        email = request.form.get("email")
        if not email:
            return render_template("apology.html", message="You must provide an email.")

        # Insert registration into SQL database and redirect to main page
        db.execute("INSERT INTO registrants (name, email) VALUES (:name, :email)", name=name, email=email)
        return redirect("/")