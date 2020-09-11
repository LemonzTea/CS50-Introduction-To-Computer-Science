import csv
from sys import argv, exit
from math import floor


def main():
    # Ensure that there is 3 arguments when running the program, exit if does not meet equirement
    if len(argv) != 3:
        print("Usage: dna.py DNA.csv DNA.txt")
        exit(1)

    # Open the unknown DNA file and extract the DNA for processing
    unknownDNA = getUnknownDNA()

    # Open the list of known DNA and save them to a 2d list
    dnaInfo = getKnownDNA()

    # Get all DNA Types to look for in the unknown DNA
    dnaTypes = getDNAtypes(dnaInfo)

    # Find the number of each DNA STR
    count_DNA_STR(dnaTypes, unknownDNA)

    # Find & print names with similar DNA STR
    crosscheck(dnaTypes, dnaInfo)


# Extra the DNA string from the file
def getUnknownDNA():
    # Open File
    DNAfile = open(argv[2], "r")
    if DNAfile is None:
        print("Error reading file")
        exit(1)

    # Process File
    unknownDNA = DNAfile.readline()


    # Close file
    DNAfile.close()
    return unknownDNA


# Get the list of all known DNA Types and count
def getKnownDNA():
    dnaInfo = []

    # Open DNA File & automatically close files
    with open(argv[1]) as DNAfile:
        if DNAfile is None:
            print("Error reading file")
            exit(1)

        # Process File
        # Get CSV Reader
        reader = csv.reader(DNAfile, delimiter=",")
        for row in reader:
            dnaInfo.append(row)
    return dnaInfo


# Get a dict of DNA to seach
def getDNAtypes(dnaInfo):
    dnaTypes = {}

    # Using recorded STRs, look for STR in the unknown DNA
    for dnaType in dnaInfo[0]:
        # Skip first column of CSV
        if dnaType == "name":
            continue

        # seach and count number of each STR type
        dnaTypes[dnaType] = 0
    return dnaTypes


# Get a count on the longest STR of each time in the DNA_string
def count_DNA_STR(DNA_dict, DNA_string):
    for dna_type in DNA_dict.keys():
        # Look for longest dna_type STR in DNA_string
        # Maximum possible DNA STR = DNA length / DNA Type length
        possible_instance = int(floor(len(DNA_string) / len(dna_type)))

        for i in reversed(range(possible_instance + 1)):

            if (DNA_string.count(dna_type * i) == 1):
                DNA_dict[dna_type] = i
                break


# Look for names that matches the DNA STR value
def crosscheck(dnaTypes, dnaInfo):
    personFound = False

    # Look through all rows in known DNA info
    for entries in range(1, len(dnaInfo)):
        if personFound == False:
            similarDNAcount = 0

            # Look through each person's details
            for count in range(1, len(dnaInfo[0])):
                if dnaTypes.get(dnaInfo[0][count]) == int(dnaInfo[entries][count]):
                    similarDNAcount += 1

            # If all DNA STR values are similar
            if similarDNAcount == len(dnaTypes):
                found = True
                print(dnaInfo[entries][0])
                break
        else:
            break

    if personFound == False:
        print("No match")


main()

