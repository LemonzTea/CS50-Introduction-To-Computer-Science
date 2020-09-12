from sys import argv, exit
import cs50


def main():
    # Check if arguments provided is correct
    if len(argv) != 2:
        print("Usuage: python roster.py housename")
        exit(1)

    # Seach in db for this housename
    search_housename = argv[1]

    # Open a connection to database
    db = cs50.SQL("sqlite:///students.db")

    # Search for students in housename
    for row in db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last ASC, first ASC", search_housename):
        if row["middle"] == None:
            name = row["first"] + " " + row["last"]
        else:
            name = row["first"] + " " + row["middle"] + " " + row["last"]

        # Prints result of housename
        print(f"{name}, born {row['birth']}")


main()