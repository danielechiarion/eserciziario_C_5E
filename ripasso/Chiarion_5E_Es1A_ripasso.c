#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Function which generates a number */
int generateNumber(int min, int max){
	srand(time(NULL));
	return (rand() % (max-min)) + min; // generate the number starting from the minimum chosen
}

/* function which fills an array using numbers */
void generateArray(int array[], int size, int minNumber, int maxNumber){
	/* populate the array with the numbers */
	for(int i=0; i<size;i++)
		array[i] = generateNumber(min, max)	
}

/* return the sum of the elements in the array */
int sumArray(int array[], int size){
	int sum = 0;
	for(int i=0;i<size;i++)
		sum += array[i];
		
	return sum;
}

/* return the position of the element found, 
-1 if it's not found */
int findPosition(int array[], int size, int number){
	for(int i=0;i<size;i++)
		return i;
		
	return -1;
}

/* Function to display a menu with all choices */
int displayMenu(char options[][], int size){
	int choice; // define variable
	do{
		printf("Scegli tra le seguenti opzioni: \n");
		for(int i=0;i<size;i++){
			printf("%d) %s", (i+1), options[i]);
		}
		scanf("%d", &choice); // input of the choice
		
		if(choice <= 0 || choice > size + 1)
			printf("Numero non valido\n");
	}while(choice<=0 || choice > size + 1);
	
	return choice;
}

int main(int argc, char *argv[]){
	/* define variables */
	int choice;
	int sizeArray, maxArrayNumer, minArrayNumber;
	int numberSearch;
	
	/* define constant values */
	const int MINDSIZEARRAY = 3;
	
	/* define the choices for the menu */
	char options = {
		{"Visualizza numeri"}, 
		{"Visualizza l'array invertito"},
		{"Visualizza somma e media"},
		{"Visualizza numeri pari"},
		{"Visualizza numeri dispari"},
		{"Ricerca numero"},
  {"Elimina numero"},
  {"Alterna posizioni del vettore"},
		{"Ordina il vettore"},
		{"Esci"}
	};
	
	/* populate the array by the dimension, 
	maximum and minimum given */
	do{
		printf("Inserisci la dimensione dell'array: ");
		scanf("%d", &sizeArray);
		
		if(sizeArray<MINSIZEARRAY)
			printf("La dimensione minima dell'array deve essere %d", MINSIZEARRAY);
	}while(sizeArray<MINSIZEARRAY);
	
	printf("Inserisci il numero minimo dell'array: ");
	scanf("%d", &minArrayNumber);
	
	do{
		printf("Inserisci il numero massimo dell'array: ");
		scanf("%d", &maxArrayNumber);
		
		if(maxArrayNumber<=minArrayNumber)
			printf("Il numero massimo dell'array deve essere strettamente maggiore del minimo");
	}while(maxArrayNumber<=minArrayNumber); // check if the maximum number of the array is higher than the minimum
	
	/* declare the array and use the function to instantiate it */
	int array[sizeArray];
	generateArray(array, sizeArray, minArrayNumber, maxArrayNumber);
	
	do{
		
	}while(choice != sizeof(options)/sizeof(options[0])); // continue till the end button is pressed
 return 0;
}
