#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

string cipher(string input, string key);


int main(int argc, string argv[])
{
    // Check if there is only 1 argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Check if there is 26 letters
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Check if key is alphabets only
    else
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (isalpha(argv[1][i]) == false)
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }
    }

    // Checks is key has repeated alphabet
    for (int i = 0, n = strlen(argv[1]) - 1; i < n; i++)
    {
        for (int j = i + 1; j < n + 1; j++)
        {
            if (argv[1][i] == argv[1][j])
            {
                printf("Key must contain 26 characters.\n");
                return 1;
            }
        }
    }

    // Asks for input
    string input = get_string("plaintext: ");

    // Cipher code using key
    string message = cipher(input, argv[1]);

    // Prints out final message
    printf("ciphertext: %s\n", message);
    return 0;
}

// Function to cipher the message - used in main
string cipher(string input, string key)
{
    string message = input;

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        // Change if uppercase
        if (isupper(input[i]))
        {
            int pos = input[i] - 'A';
            key[pos] = toupper(key[pos]);
            message[i] = key[pos];
            // printf("%s\n", message);
        }

        // Change if lowercase
        if (islower(input[i]))
        {
            int pos = input[i] - 'a';
            key[pos] = tolower(key[pos]);
            message[i] = key[pos];
            // printf("%s\n", message);
        }
    }
    return message;
}