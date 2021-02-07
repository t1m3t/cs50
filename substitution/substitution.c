#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string encrypt(string plaintext, string key);

int main(int argc, string argv[])
{
    // If the number of CL arguments is none or more than one
    if (argc == 1 || argc > 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];
    // If the length of the key is not equal to 26 characters
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int i = 0, len = strlen(key); i < len; i++)
    {
        char c = key[i];
        // If character is not an uppercase or lowercase character (non-alphabetic)
        if (!isalpha(c))
        {
            printf("Key must contain only alphabetic characters.\n");
            return 1;
        }
        // Check if there are repeated characters
        for (int j = i+1; j < len; j++)
        {
            if (c == key[j])
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }

    string plaintext = get_string("plaintext:  ");
    string ciphertext = encrypt(plaintext, key);
    printf("ciphertext: %s\n", ciphertext);

    return 0;
}

string encrypt(string plaintext, string key)
{
    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        char c = plaintext[i];
        if (isupper(c))
        {
            // Convert the character c to the corresponding character in the key
            // Put the new character back into the same string
            plaintext[i] = toupper(key[c - 'A']);
        }
        else if (islower(c))
        {
            // For lowercase, use 'a' instead of 'A'
            plaintext[i] = tolower(key[c - 'a']);
        }
    }
    return plaintext;
}