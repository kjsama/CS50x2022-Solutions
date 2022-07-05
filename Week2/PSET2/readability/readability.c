#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
int main(void)
{
    // gets the text input
    string text = get_string("Text: ");

    float letters = 0;
    float words = 0;
    float sentences = 0;


    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // counts the letters bu ascii code
        if (text[i] >= 65 && text[i] <= 122)
        {
            letters++;
        }
        // counts the words by recognize spaces
        else if (text[i] == 32 && (text[i - 1] != 33 && text[i - 1] != 46 && text[i - 1] != 63))
        {
            words++;
        }
        // counts the sentences by finding dots, exclamation marks and interrogatives
        else if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentences++;
            words++;
        }
    }

    float L = letters * 100 / words;
    float S = sentences * 100 / words;
    // Coleman-Liau index is computed using the formula
    float index = round(0.0588 * L - 0.296 * S - 15.8);

    // Finally outputs the result to the user
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) index);
    }
}