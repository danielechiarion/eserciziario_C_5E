#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Function which generates a number */
int generateNumber(int min, int max){
	srand(time(NULL));
	return (rand() % (max-min)) + min; // generate the number starting from the minimum chosen
}

/* function which fills an array using numbers */
void generateArray(int array[], int size, zint minNumber, int maxNumber){
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

int main(){
	/* define variables */
	int choice;
	int sizeArray, numberSearch;
	
	/* define the choices for the menu */
	char options = {
		{"Popola l'array"}, 
		{"Visualizza l'array invertito"},
		{"Visualizza somma e media"},
		{"Visualizza numeri pari"},
		{"Visualizza numeri dispari"},
		{"Ricerca numero"},
    {"Elimina numero"},
    
	};
    
    return 0;

}
