from cs50 import get_float

# Gets input from user
while True:
    amount = get_float("Changed owed: ")
    if amount > 0:
        amount = int(amount * 100)
        break
count = 0   # number of coins


# Number of quarters
while amount != amount % 25:
    amount -= 25
    count += 1

# Number of dimes
while amount != amount % 10:
    amount -= 10
    count += 1

# Number of nickels
while amount != amount % 5:
    amount -= 5
    count += 1

# Number of pennies
count += amount

print(count)

