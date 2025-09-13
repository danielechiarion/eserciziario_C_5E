#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Function which generates a number */
int generateNumber(int min, int max)
{
	return (rand() % (max - min)) + min; // generate the number starting from the minimum chosen
}

/* function which fills an array using numbers */
void generateArray(int array[], int size, int minNumber, int maxNumber)
{
	/* populate the array with the numbers */
	for (int i = 0; i < size; i++)
		array[i] = generateNumber(minNumber, maxNumber);
}

/* return the sum of the elements in the array */
int sumArray(int array[], int size)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
		sum += array[i];

	return sum;
}

/* return the position of the element found,
-1 if it's not found */
int findPosition(int array[], int size, int number)
{
	for (int i = 0; i < size; i++)
		if (array[i] == number)
			return i;

	return -1;
}

/* Function to display a menu with all choices */
int displayMenu(char options[][100], int size)
{
	int choice; // define variable
	do
	{
		printf("Scegli tra le seguenti opzioni: \n");
		for (int i = 0; i < size; i++)
		{
			printf("%d) %s\n", (i + 1), options[i]);
		}
		scanf("%d", &choice); // input of the choice

		if (choice <= 0 || choice > size + 1)
			printf("Numero non valido\n");
	} while (choice <= 0 || choice > size + 1);

	return choice;
}

/* function to swap numbers */
void swapNumbers(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int main(int argc, char *argv[])
{
	/* define variables */
	int choice;
	int sizeArray, maxArrayNumber, minArrayNumber;
	int numberSearch;
	int arraySum, searchResult;
	double arrayAverage;

	/* define constant values */
	const int MINSIZEARRAY = 3;
	srand(time(NULL)); // initialize the random number generator

	/* define the choices for the menu */
	char options[][100] = {
		{"Visualizza numeri"},
		{"Visualizza l'array invertito"},
		{"Visualizza somma e media"},
		{"Visualizza numeri pari"},
		{"Visualizza numeri dispari"},
		{"Ricerca numero"},
		{"Elimina numero"},
		{"Alterna posizioni del vettore"},
		{"Ordina il vettore"},
		{"Esci"}};

	/* populate the array by the dimension,
	maximum and minimum given */
	do
	{
		printf("Inserisci la dimensione dell'array: ");
		scanf("%d", &sizeArray);

		if (sizeArray < MINSIZEARRAY)
			printf("La dimensione minima dell'array deve essere %d\n", MINSIZEARRAY);
	} while (sizeArray < MINSIZEARRAY);

	printf("Inserisci il numero minimo dell'array: ");
	scanf("%d", &minArrayNumber);

	do
	{
		printf("Inserisci il numero massimo dell'array: ");
		scanf("%d", &maxArrayNumber);

		if (maxArrayNumber <= minArrayNumber)
			printf("Il numero massimo dell'array deve essere strettamente maggiore del minimo\n");
	} while (maxArrayNumber <= minArrayNumber); // check if the maximum number of the array is higher than the minimum

	/* declare the array and use the function to instantiate it */
	int *array = malloc(sizeArray * sizeof(int));
	generateArray(array, sizeArray, minArrayNumber, maxArrayNumber);

	do
	{
		/* choose an option and pass it to
		the switch case */
		choice = displayMenu(options, sizeof(options) / sizeof(options[0]));
		switch (choice)
		{
		case 1: // display numbers
			printf("Numeri nell'array: \n");
			for (int i = 0; i < sizeArray; i++)
				printf("%d\t", array[i]);
			break;
		case 2: // display inverted array
			printf("Array invertito: \n");
			for (int i = sizeArray - 1; i >= 0; i--)
				printf("%d\t", array[i]);
			break;
		case 3: // display sum and average of the array
			arraySum = sumArray(array, sizeArray);
			arrayAverage = (double)arraySum / sizeArray;
			printf("\nLa somma dell'array e': %d\nLa media dell'array e': %.2f", arraySum, arrayAverage);
			break;
		case 4: // display even numbers
			printf("Numeri pari nell'array: \n");
			for (int i = 0; i < sizeArray; i++)
				if (array[i] % 2 == 0)
					printf("%d\t", array[i]);
			break;
		case 5: // display odd numbers
			printf("Numeri dispari nell'array: \n");
			for (int i = 0; i < sizeArray; i++)
				if (array[i] % 2 != 0)
					printf("%d\t", array[i]);
			break;
		case 6: // search for a number
			printf("Inserisci un numero: ");
			scanf("%d", &numberSearch);
			searchResult = findPosition(array, sizeArray, numberSearch);
			if (searchResult != -1)
				printf("Il numero e' stato trovato alla %d^ posizione", (searchResult + 1));
			else
				printf("Il numero non e' stato trovato");
			break;
		case 7: // delete a number
			printf("Inserisci un numero: ");
			scanf("%d", &numberSearch);
			searchResult = findPosition(array, sizeArray, numberSearch);
			if (searchResult != -1)
			{
				int *newArray = malloc((sizeArray - 1) * sizeof(int)); // new array with a size less than the previous one
				/* transfer of one position to the left all
				the numbers after the one found */
				for (int i = 0; i < sizeArray - 1; i++)
				{
					if (i < searchResult)
						newArray[i] = array[i];
					else if (i >= searchResult)
						newArray[i] = array[i + 1];
				}
				free(array);
				array = newArray; // update the array
				sizeArray--;
			}
			else
			{
				printf("Il numero non e' stato trovato");
			}
			break;
		case 8: // alternate positions of the array
			for (int i = 0; i < sizeArray - 1; i += 2)
			{
				if (i + 1 == sizeArray) // it means that the array has an odd number of elements, so the last one remains as it is
					break;
				swapNumbers(&array[i], &array[i + 1]);
			}
			break;
		case 9: // sort the array
			for (int i = 0; i < sizeArray - 1; i++)
			{
				for (int j = i + 1; j < sizeArray; j++)
				{
					if (array[i] > array[j])
					{
						swapNumbers(&array[i], &array[j]);
					}
				}
			}
			printf("Array ordinato con successo");
			break;
		default:
			printf("\nProgramma terminato");
		}
		printf("\n");
	} while (choice != sizeof(options) / sizeof(options[0])); // continue till the end button is pressed
	return 0;
}
