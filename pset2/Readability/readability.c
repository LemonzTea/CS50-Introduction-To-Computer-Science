// Formula index = 0.0588 * L - 0.296 * S - 15.8
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

// Functions
int wordCount(string text);
float calculateAverageSentence(string text);
float calculateAverageLetter(string text);
int calculateGrade(string text);

// Main Function
int main(void)
{
    string text = get_string("Text: ");
    if (calculateGrade(text) < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (calculateGrade(text) > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", calculateGrade(text));
    }
}


// Calculate grade
int calculateGrade(string text)
{
    int index;

    // Formaula to calculate the grade
    index = round(0.0588 * calculateAverageLetter(text) - 0.296 * calculateAverageSentence(text) - 15.8);

    // Return grade of the song
    return index;
}

// Calculate Average Number of letter in 100 words
float calculateAverageLetter(string text)
{
    float averageLetter = 0;

    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            averageLetter++;
        }
    }

    // printf("No of letter: %.2f\n", averageLetter);
    averageLetter = averageLetter / wordCount(text) * 100;

    return averageLetter;
}

// Calculate Average Number of Sentence in 100 words
float calculateAverageSentence(string text)
{
    float averageSentence = 0;

    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            averageSentence++;
        }
    }

    // printf("No of sentences:=%.2f\n", averageSentence);
    averageSentence = averageSentence / wordCount(text) * 100;
    return averageSentence;
}


// Counts the number of words
int wordCount(string text)
{
    int wordCount = 0;

    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (text[i] == ' ')
        {
            wordCount++;
        }
    }

    // printf("%i words(s)\n", wordCount + 1);
    return wordCount + 1;
}