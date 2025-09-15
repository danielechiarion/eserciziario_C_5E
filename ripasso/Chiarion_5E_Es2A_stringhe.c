#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* function to check if a character is a letter */
bool isLetter(char character)
{
    if ((character < 'a' || character > 'z') && (character < 'A' || character > 'Z'))
        return false;

    return true;
}

/* check if the string contains only
letters */
bool checkOnlyLettersString(char string[])
{
    for (int i = 0; i < strlen(string); i++)
    {
        if (!isLetter(string[i]))
            return false;
    }

    return true;
}

/* function to count how many times
the character is in a string */
int countCharInString(char string[], char character)
{
    int count = 0;

    for (int i = 0; i < strlen(string); i++)
    {
        if (string[i] == character)
            count++;
    }

    return count;
}

/* function to separate even and odd characters
in two different strings */
void separateEvenOddCharacters(char startingString[], char evenString[], char oddString[])
{
    int indexEven = 0, indexOdd = 0; // declare and initialize the indexes for the strings

    for (int i = 0; i < strlen(startingString); i++)
    {
        if (i % 2 == 0)
            evenString[indexEven++] = startingString[i];
        else
            oddString[indexOdd++] = startingString[i];
    }
}

/* function to check if the string
contains double characters */
bool containsDouble(char string[])
{
    for (int i = 0; i < strlen(string) - 1; i++)
    {
        if (string[i] == string[i + 1])
            return true;
    }

    return false;
}

/* function to output which characters
are both in the first and second string */
void commonCharacters(char firstString[], char secondString[])
{
    bool alphabet[26] = {false}; // use the array to avoid repetitions
    printf("\nI caratteri in comune sono: \n");
    for (int i = 0; i < strlen(firstString); i++)
    {
        if (!alphabet[firstString[i] - 'a'] && countCharInString(secondString, firstString[i]) > 0)
            printf("%c\t", firstString[i]);

        alphabet[firstString[i] - 'a'] = true; // update the array
    }
}

/* function to check the number of vowels
and consonant in a string, which must be only made
of letters */
void countVowelsConsonants(char string[], int *vowelCount, int *consonantCount)
{
    for (int i = 0; i < strlen(string); i++)
    {
        if (string[i] == 'a' || string[i] == 'e' || string[i] == 'i' || string[i] == 'o' || string[i] == 'u' || string[i] == 'A' || string[i] == 'E' || string[i] == 'I' || string[i] == 'O' || string[i] == 'U')
            (*vowelCount)++;
        else
            (*consonantCount)++;
    }
}

int main(int argc, char *argv[])
{
    /* variable declaration */
    char firstString[100], secondString[100], charSearch;
    char evenString[50], oddString[50];
    int consonantCountFirst = 0, vowelCountFirst = 0, consonantCountSecond = 0, vowelCountSecond = 0;

    /* input of the string */
    do
    {
        printf("Inserisci la prima stringa (solo lettere): ");
        scanf("%s", firstString);
    } while (!checkOnlyLettersString(firstString));
    /* input of the character to search */
    do
    {
        printf("Inserisci una lettera da ricercare: ");
        scanf("%c", &charSearch);
        if (!isLetter(charSearch))
            printf("Il carattere deve essere una lettera\n");
    } while (!isLetter(charSearch));

    printf("\nIl carattere %c compare nella stringa %s %d volte", charSearch, firstString, countCharInString(firstString, charSearch)); // output of the fist result

    /* separate the string and view the results */
    separateEvenOddCharacters(firstString, evenString, oddString);
    printf("\nStringa con i caratteri pari: %s\nStringa con i caratteri dispari: %s\n", evenString, oddString);

    /* check for double characters in the string */
    if (containsDouble(firstString))
        printf("La stringa %s contiene caratteri doppi\n", firstString);
    else
        printf("La stringa %s non contiene caratteri doppi\n", firstString);

    /* input of the second string */
    printf("\n");
    do
    {
        printf("Inserisci la seconda stringa (solo lettere): ");
        scanf("%s", secondString);
    } while (!checkOnlyLettersString(secondString));
    /* decide which string is longer */
    if (strlen(firstString) > strlen(secondString))
        printf("La stringa %s e' piu' lunga della stringa %s\n", firstString, secondString);
    else if (strlen(firstString) < strlen(secondString))
        printf("La stringa %s e' piu' lunga della stringa %s\n", secondString, firstString);
    else
        printf("Le due stringhe sono lunghe uguali\n");
    /* search for common characters */
    commonCharacters(firstString, secondString);
    /* count the number of vowels and consonants in both strings,
    than print the results */
    countVowelsConsonants(firstString, &vowelCountFirst, &consonantCountFirst);
    countVowelsConsonants(secondString, &vowelCountSecond, &consonantCountSecond);
    if (consonantCountFirst > consonantCountSecond)
        printf("\nLa stringa %s ha piu' consonanti della stringa %s", firstString, secondString);
    else if (consonantCountFirst < consonantCountSecond)
        printf("\nLa stringa %s ha piu' consonanti della stringa %s", secondString, firstString);
    else
        printf("\nLe due stringhe hanno lo stesso numero di consonanti");
    if (vowelCountFirst > vowelCountSecond)
        printf("\nLa stringa %s ha piu' vocali della stringa %s", firstString, secondString);
    else if (vowelCountFirst < vowelCountSecond)
        printf("\nLa stringa %s ha piu' vocali della stringa %s", secondString, firstString);
    else
        printf("\nLe due stringhe hanno lo stesso numero di vocali");

    return 0;
}