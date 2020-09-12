import csv
from sys import argv, exit
import cs50


# TODO
def main():
    # Check if correct number of arguments is given
    if len(argv) != 2:
        print("Usuage: python import.py filename.csv")
        exit(1)

    # Connect to database
    db = cs50.SQL("sqlite:///students.db")

    # Open file for processing
    with open(argv[1], "r") as file:

        # Using csv reader to read the file
        reader = csv.DictReader(file)
        for row in reader:

            # Process names to split first, middle and last name
            fullname = row["name"].split()

            # Check if middlename exists
            if len(fullname) == 2:
                firstname = fullname[0]
                middlename = None
                lastname = fullname[1]
            else:
                firstname = fullname[0]
                middlename = fullname[1]
                lastname = fullname[2]

            # Insert student record into students.db
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
                       firstname, middlename, lastname, row["house"], int(row["birth"]))

    exit(0)


main()