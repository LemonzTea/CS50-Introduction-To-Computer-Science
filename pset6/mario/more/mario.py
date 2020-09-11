# Gets input from user
while True:
    height = input("Height: ")
    if height.isnumeric() and int(height) >= 1 and int(height) <= 8:
        height = int(height)
        break


for i in range(height):
    # Prints number of spaces, always start with max - 1 spaces and 1 hash
    print(" "*((height - i) - 1), end="")
    print("#"*(i + 1), end="")

    # Spacer between the two pyramids
    print("  ", end="")

    # Print 2nd pyramid
    print("#" * (i + 1), end="")
    print()
