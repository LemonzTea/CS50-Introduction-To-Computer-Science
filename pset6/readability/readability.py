text = input("Text: ").lower()

charaCount = 0

# Check if text is empty. if empty, there is no words.
# Otherwise, at least 1 word
if len(text) != 0:
    wordCount = 1
else:
    wordCount = 0

sentenceCount = 0

for chara in text:
    # Count the number of characters in the text
    if chara.isalpha() == True:
        charaCount += 1

    # Count the number of words in the text using spaces
    if chara == " ":
        wordCount += 1

    # Count the number of sentences in the text using end sentence markers
    if chara == "!" or chara == "." or chara == "?":
        sentenceCount += 1

# Calculate 0.0588 * L - 0.296 * S - 15.8,
# where L is the average number of letters per 100 words in the text, and
# S is the average number of sentences per 100 words in the text.
avgLetter = charaCount / wordCount * 100
avgSentence = sentenceCount / wordCount * 100


# Calculate grade
grade = round(0.0588 * avgLetter - 0.296 * avgSentence - 15.8)


# Formatting for printing grade
if grade < 1:
    print("Before Grade 1")
elif grade > 16:
    print("Grade 16+")
else:
    print(f"Grade {grade}")

