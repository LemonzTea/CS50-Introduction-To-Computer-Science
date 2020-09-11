from cs50 import get_string


def main():
    while True:
        number = get_string("Number: ")
        if number.isnumeric() == True:
            number = int(number)

            if number > 0:
                length = len(str(number))

            # Check to ensure that the starting number and length is correct
            # Check for Visa
            if int(str(number)[0]) == 4 and (length == 13 or length == 16):
                if check(number) == True:
                    print("VISA")
                    exit()

            # Check for Mastercard
            elif int(str(number)[0:2]) >= 51 and int(str(number)[0:2]) <= 55 and length == 16:
                if check(number) == True:
                    print("MASTERCARD")
                    exit()

            # Check for Amex
            elif int(str(number)[0:2]) == 34 or int(str(number)[0:2]) == 37 and length == 15:
                if check(number) == True:
                    print("AMEX")
                    exit()
            print("INVALID")
            exit()


# Luhn's Algorithm to check validity of credit cards
def check(number):
    copy = number
    copy = int(copy / 10)
    sum1 = 0

    # Step 1 of Luhn's algorithm, sum of 2 * every other digit from 2nd last digit
    while copy != 0:
        step1 = (copy % 10) * 2
        if len(str(step1)) == 1:
            sum1 += step1
        else:
            counter = int(str(step1)[0]) + int(str(step1)[1])
            sum1 += counter

        copy = int(copy / 100)

    # Step 2 of luhn's algorithm, sum all other digits
    copy = number
    while copy != 0:
        step2 = copy % 10
        sum1 += step2
        copy = int(copy / 100)

    # Step 3 of luhn's algorithm, check if final digit is 0
    if str(sum1)[-1] == "0":
        return True
    else:
        return False


main()