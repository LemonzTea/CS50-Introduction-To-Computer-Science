#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

string cipher(string plaintext, int key);

// Caesar Cipher
int main(int argc, string argv[])
{
    // Check if there is 1 arguement only
    if (argc != 2)
    {
        printf("Usuage: ./caesar key\n");
        return 1;
    }

    // Check if arguemnt is a number
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (isdigit(argv[1][i]) == false)
        {
            printf("Usuage: ./caesar key\n");
            return 1;
        }
    }

    // If argument has no error, run cipher

    // Enter plaintext
    string plaintext = get_string("plaintext: ");

    // Converts into cipher text
    string ciphertext = cipher(plaintext, atoi(argv[1]));

    // Print Ciphertext
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}

string cipher(string plaintext, int key)
{
    key = key % 26;
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        // Cipher Uppercase Text
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
        {
            if (plaintext[i] + key > 'Z')
            {
                plaintext[i] = (char)(plaintext[i] + key - 26);
            }
            else
            {
                plaintext[i] = (char)(plaintext[i] + key);
            }
        }


        // Cipher Lowercase Text
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
        {
            if (plaintext[i] + key > 'z')
            {
                plaintext[i] = (char)(plaintext[i] + key - 26);
            }
            else
            {
                plaintext[i] = (char)(plaintext[i] + key);
            }
        }
    }
    return plaintext;
}