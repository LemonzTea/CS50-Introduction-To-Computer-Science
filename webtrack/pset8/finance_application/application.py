import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    return render_template("mainpage.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        quantity = request.form.get("amount")

        if symbol == "":
            return render_template("buy.html", message = "Symbol cannot be empty")
        elif quantity is "" or int(quantity) <= 0:
            return render_template("buy.html", message = "Quantity must be at least 1")

        # Check if symbol exists
        result = lookup(symbol)
        if result is None:
            return render_template("buy.html", message = "Symbol does not exist")

        # Check if quantity is within budget
        amount = db.execute("SELECT cash FROM users WHERE id = :id", id=session.get("user_id"))
        amount = float(amount[0]["cash"])
        transaction_total_price = float(result["price"]) * int(quantity)
        if transaction_total_price > amount:
            return render_template("buy.html", message = "Insufficient Funds in account")
        else:
            # Adds transaction into
            db.execute("INSERT INTO transactions(user_id, symbol, quantity, price_per_qty, transaction_type) " +
                       "VALUES (:user_id, :symbol, :quantity, :price_per_qty, :trans_type)",
                       user_id=session.get("user_id"),
                       symbol=symbol,
                       quantity=int(quantity),
                       price_per_qty=float(result["price"]),
                       trans_type='buy')

            # Reduce Total Available Cash
            balance = amount - transaction_total_price
            db.execute("UPDATE users SET cash = :balance WHERE id = :id", balance=balance, id=session.get("user_id"))

            # Update Asset for User
            result = db.execute("SELECT * FROM asset WHERE user_id = :user_id AND stock = :symbol",
                                user_id=session.get("user_id"),
                                symbol=symbol)

            if len(result) == 0:
                db.execute("INSERT INTO asset (user_id, stock, quantity) VALUES (:user_id, :stock, :quantity)",
                            user_id=session.get("user_id"),
                            stock=symbol,
                            quantity=quantity)
            else:
                db.execute("UPDATE asset SET quantity = :quantity WHERE user_id = :user_id AND stock = :symbol",
                           quantity=int(result[0]["quantity"]) + int(quantity),
                           user_id=session.get("user_id"),
                           symbol=symbol)

            flash("Purchase Successful")
            return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        flash('Logged in Successfully')
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        found = False
        symbol = request.form.get("symbol").upper()
        if symbol == "":
            return render_template("quote.html", message="You must enter a symbol.")

        # Helper function from helper.py to look up prices
        result = lookup(symbol)

        if result == None:
            message = "Symbol {symbol} cannot be found"
            return render_template("quote.html", message=message.format(symbol = symbol))
        else:
            message = "The current price of {name}({symbol}) is ${price:.2f}"
            return render_template("quote.html", message=message.format(name = result["name"], symbol=symbol, price=result["price"]))

        """Get stock quote."""
    else:
        return render_template("quote.html")


# Registration Page
@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method =="POST":
        # Gets all form information
        name = request.form.get("username")
        password1 = request.form.get("password")
        password2 = request.form.get("password_confirm")

        # Check if passwords entered are correct
        if password1 != password2:
            return render_template("register.html", message="Passwords entered do not match")

        # Check if username already exists in the database
        user_database_info = db.execute("SELECT username FROM users WHERE username = :name", name=name)

        if len(user_database_info) == 0:
            # If username is free, allow for account creation
            db.execute("INSERT INTO users (username, hash) VALUES (:username, :password)", username=name,
                        password=generate_password_hash(password1))

            # Logs the user in
            flash('Account created Successfully')
            return redirect("/login", code=307)


        # Show message that username already exists.
        else:
            return render_template("register.html", message="Username has been taken")

    else:
        return render_template("register.html")

    """Register user"""
    return apology("TODO")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
