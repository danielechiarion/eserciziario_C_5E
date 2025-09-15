#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* function to check if a character is a letter */
bool isLetter(char character){
    if((character<'a' || character>'z') && (character<'A' || character>'Z'))
        return false;
        
    return true;
}
 
/* check if the string contains only 
letters */
bool checkOnlyLettersString(char string[]){
    for(int i=0;i<strlen(string);i++){
    	if(!isLetter(string[i]))
        	return false;
    }
    
    return true;
}

/* function to count how many times
the character is in a string */
int countCharInString(char string[], char character){
    int count = 0;
    
	for(int i=0;i<strlen(string);i++){
        if(string[i] == character)
        	count++;
    }
    
    return count;    
}

/* function to separate even and odd characters
in two different strings */
void separateEvenOddCharacters(char startingString[], char evenString[], char oddString[]){
    int indexEven = 0, indexOdd = 0; // declare and initialize the indexes for the strings
}

int main(int argc, char *argv[]){
    /* variable declaration */
    char firstString[100], secondString[100], charSearch;
    char evenString[50], oddString[50];
    
    /* input of the string */
    do{
        printf("Inserisci la prima stringa (solo lettere) ");
    	scanf("%s", firstString);
    }while(!checkOnlyLettersString(firstString));
    /* input of the character to search */
    do{
        printf("Inserisci una lettera da ricercare: );
        scanf("%c", &charSearch);
        if(!isLetter(charSearch))
        	printf("Il carattere deve essere una lettera\n");
    }while(!isLetter(charSearch));
    
    printf("\nIl carattere %c compare nella stringa %s %d volte", charSearch, firstString, countCharInString(firsString, charSearch)); // output of the fist result
    
    return 0;
}