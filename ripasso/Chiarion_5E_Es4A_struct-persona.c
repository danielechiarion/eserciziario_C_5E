#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

/* define structure for
the person */
typedef struct{
    char name[50];
    char surname[50];
    int age;
    char taxIDCode[16];
    double netWorth;
    int birthYear;
    char town[50];
}person_t;

/* function to clear the screen */
void clrScr()
{
#ifdef _WIN32      // Check if the OS is Windows
    system("cls"); // instruction for clearing cmd of Windows
#else
    system("clear"); // instruction for clearing shell of Linux / MacOS
#endif
}

/* function to simulate the menu for
the beverages */
int menu(char options[][100], int size)
{
    int choice;
    int i;

    do
    {
        printf("\n=== SCEGLI OPZIONE ==="); // output of the title
        for (i = 0; i < size; i++)
        {
            printf("\n[%d] %s", (i + 1), options[i]); // output of the options
        }
        printf("\n");
        scanf("%d", &choice);
        /* error message */
        if (choice < 1 || choice > size)
        {
            printf("\nValore errato. Riprova");
            clrScr();
        }
    } while (choice < 1 || choice > size); // checking value

    return choice;
}

/* find the indexes of maximum and minimum net worth */
void findMaximumMinimumNetWorth(person_t people[], int size, int *maxIndex, int *minIndex){
    int i;
    *maxIndex = 0;
    *minIndex = 0;

    for(i = 1; i < size; i++){
        if(people[i].netWorth > people[*maxIndex].netWorth){
            *maxIndex = i;
        }
        if(people[i].netWorth < people[*minIndex].netWorth){
            *minIndex = i;
        }
    }
}

/* function to sort the people by the 
year of birth */
void sortPeople(person_t people[], int size){
    person_t tempPerson;

    /* sort the people by year of registration 
    using selection sort */
    for(int i=0;i<size-1;i++){
        for(int j=i+1;j<size;j++){
            if(people[j].birthYear < people[i].birthYear){
                tempPerson = people[i];
                people[i] = people[j];
                people[j] = tempPerson;
            }
        }
    }
}

/* function to find the people by the tax ID code */
int findPersonByTaxIDCode(person_t people[], int size, char taxIDCode[]){
    for(int i=0;i<size;i++){
        if(strcmp(people[i].taxIDCode, taxIDCode) == 0) // if the tax ID codes are the same
            return i; // return the index
    }
    return -1; // if the person is not found
}

/* function to select people by a minimum net worth */
void selectPeoplebyNetWorth(person_t people[], int size, double netWorth, bool selectedPeople[]){
    for(int i=0;i<size;i++){
        selectedPeople[i] = false; // reset the position if it's necessary
        if(people[i].netWorth >= netWorth)
            selectedPeople[i] = true;
    }
}

/* function to print the selected people with the 
boolean array */
void printSelectedPeople(person_t people[], int size, bool selectedPeople[]){
    bool anySelected = false; // this variable is used if the array is empty
    for(int i=0;i<size;i++){
        if(selectedPeople[i]){ // if the person is selected
            printf("%s %s\t%d\t%s\t%.2f€\n", people[i].name, people[i].surname, people[i].birthYear, people[i].town, people[i].netWorth);
            anySelected = true;
        }
    }
    if(!anySelected)
        printf("\nNessuna persona trovata.\n");
}

/* function to calculate the average net worth */
double averageNetWorth(person_t people[], int size){
    double sum = 0;

    for(int i=0;i<size;i++)
        sum += people[i].netWorth;

    return sum/size;
}

/* function to select people using the year of birth*/
void selectPeopleByBirthYear(person_t people[], int size, int birthYear, bool selectedPeople[]){
    for(int i=0;i<size;i++){
        selectedPeople[i] = false; // reset the position if it's necessary
        if(people[i].birthYear == birthYear)
            selectedPeople[i] = true;
    }
}

/* function to select people by town */
void selectPeopleByTown(person_t people[], int size, char town[], bool selectedPeople[]){
    for(int i=0;i<size;i++){
        selectedPeople[i] = false; // put it to false if it's necessary
        if(strcmp(people[i].town, town)==0)
            selectedPeople[i] = true;
    }
}

/* function to count selected people */
int countSelectedPeople(bool selectedPeople[], int size){
    int counter = 0;

    for(int i=0;i<size;i++){
        if(selectedPeople[i])
            counter++;
    }

    return counter;
}

/* function to calculate the average age
of the population in that town */
double calculateAverageAge(person_t people[], int size, bool selectedPeople[]){
    int sumAge = 0, count=0;

    for(int i=0;i<size;i++){
        if(selectedPeople[i]){
            sumAge += people[i].age;
            count++;
        }
    }

    if(count == 0) // verify if counter is 0 to avoid maths errors
        return 0; 

    return (double)sumAge/count;
}

/* function to search people of a specific town */
void searchTownInhabitants(char inputTown[], person_t people[], int size, bool selectedPeople[]){
    /* variable declaration */
    int peopleCounter;
    double averageAge;
    /* find the town and print the results */
    printf("\n=== Citta' di %s ===\n", inputTown);
    /* use the provided size (caller must pass the people array size) */
    selectPeopleByTown(people, size, inputTown, selectedPeople);
    printSelectedPeople(people, size, selectedPeople);

    /* calculate and print number of people and average of the age */
    peopleCounter = countSelectedPeople(selectedPeople, size);
    averageAge = calculateAverageAge(people, size, selectedPeople);
    if(peopleCounter != 0)
        printf("\nI cittadini sono %d\nL'eta' media e' di %.1f anni", peopleCounter, averageAge);
}

/* function to verify if the town 
is present inside the register */
bool isTownInside(char **townRegister, int size, char town[]){
    for(int i=0;i<size;i++){
        if(strcmp(townRegister[i], town) == 0)
            return true;
    }
    return false;
}

/* function to group all the inhabitants of 
a specific town */
void groupTownInhabitants(person_t people[], int peopleSize, bool selectedPeople[]){
    char **namedTowns = NULL;
    int townsCount = 0;

    for(int i = 0; i < peopleSize; i++){
        char *town = people[i].town;
        if(!isTownInside(namedTowns, townsCount, town)){
            /* add town to namedTowns (do not print now) */
            char **tmp = realloc(namedTowns, (townsCount + 1) * sizeof(char*));
            if(!tmp){
                // allocation failed: free and return
                for(int j=0;j<townsCount;j++) free(namedTowns[j]);
                free(namedTowns);
                return;
            }
            namedTowns = tmp;
            namedTowns[townsCount] = strdup(town);
            if(!namedTowns[townsCount]){
                // strdup failed
                for(int j=0;j<townsCount;j++) free(namedTowns[j]);
                free(namedTowns);
                return;
            }
            townsCount++;
        }
    }

    /* now iterate namedTowns and print inhabitants for each */
    for(int t = 0; t < townsCount; t++){
        searchTownInhabitants(namedTowns[t], people, peopleSize, selectedPeople);
    }

    for(int j=0;j<townsCount;j++) free(namedTowns[j]);
    free(namedTowns);
}

int main(int argc, char *argv[]){
    /* define 20 people */
    person_t people[20] = {
        {"Mario", "Rossi", 30, "RSSMRA80A01H501U", 10000.0, 1995, "Milano"},
        {"Luigi", "Verdi", 25, "VRDLGU95B02F205Z", 15000.0, 2000, "Roma"},
        {"Anna", "Bianchi", 40, "BNCHNA60C03L219X", 20000.0, 1985, "Torino"},
        {"Giulia", "Neri", 35, "NERGLI70D04M345Y", 12000.0, 1990, "Napoli"},
        {"Marco", "Russo", 28, "RSSMRC85E05P456W", 18000.0, 1997, "Genova"},
        {"Sara", "Ferrari", 32, "FRRSRA90F06Q567V", 17000.0, 1993, "Bologna"},
        {"Luca", "Gallo", 27, "GLLLCA75G07R678U", 16000.0, 1998, "Firenze"},
        {"Elena", "Costa", 29, "CSTELN80H08S789T", 14000.0, 1996, "Venezia"},
        {"Paolo", "Conti", 31, "CNTPLA85I09T890S", 13000.0, 1994, "Palermo"},
        {"Francesca", "Greco", 26, "GRCFNC90J10U901R", 11000.0, 1999, "Cagliari"},
        {"Mario", "Rossi", 30, "RSSMRA80A01H501U", 10000.0, 1995, "Milano"},
        {"Luigi", "Verdi", 25, "VRDLGU95B02F205Z", 15000.0, 2000, "Roma"},
        {"Anna", "Bianchi", 40, "BNCHNA60C03L219X", 20000.0, 1985, "Torino"},
        {"Giulia", "Neri", 35, "NERGLI70D04M345Y", 12000.0, 1990, "Napoli"},
        {"Marco", "Russo", 28, "RSSMRC85E05P456W", 18000.0, 1997, "Genova"},
        {"Sara", "Ferrari", 32, "FRRSRA90F06Q567V", 17000.0, 1993, "Bologna"},
        {"Luca", "Gallo", 27, "GLLLCA75G07R678U", 16000.0, 1998, "Firenze"},
        {"Elena", "Costa", 29, "CSTELN80H08S789T", 14000.0, 1996, "Venezia"},
        {"Paolo", "Conti", 31, "CNTPLA85I09T890S", 13000.0, 1994, "Palermo"},
        {"Francesca", "Greco", 26, "GRCFNC90J10U901R", 11000.0, 1999, "Cagliari"}
    };
    /* define options for the menu */
    char options[][100] = {
        {"Vedi reddito annuale maggiore e minore"},
        {"Ordina la lista di persone per anno di nascita"},
        {"Cerca persona per codice fiscale"},
        {"Visualizza persone con reddito minimo"},
        {"Calcola media redditi"},
        {"Visualizza persone nate in un anno specifico"},
        {"Raggruppa abitanti delle città"},
        {"Fine"}
    };
    /* define variables and arrays 
    for the management of the program */
    int choice;
    int maxNetWorthIndex, minNetWorthIndex, indexResult, inputBirthYear, peopleCounter;
    bool selectedPeople[sizeof(people)/sizeof(people[0])] = {false}; // array used to select multiple numbers of people
    char inputTaxIDCode[16], inputTown[50];
    double inputNetWorth, averageAge;

    /* cycle with the functions based 
    on the user's choice */
    do{
        choice = menu(options, sizeof(options)/sizeof(options[0])); // start with the options
        clrScr();

        switch(choice){
            /* Search maximum and minimum net worth*/
            case 1:
                findMaximumMinimumNetWorth(people, 20, &maxNetWorthIndex, &minNetWorthIndex);
                printf("\nLa persona con il reddito annuo maggiore e':\t%s %s\t%s\t%.2f€\nLa persona con il reddito annuo minore è: \t%s %s\t%s\t%.2f€",
                       people[maxNetWorthIndex].name, people[maxNetWorthIndex].surname, people[maxNetWorthIndex].town, people[maxNetWorthIndex].netWorth,
                       people[minNetWorthIndex].name, people[minNetWorthIndex].surname, people[minNetWorthIndex].town, people[minNetWorthIndex].netWorth);
                break;
            /* Order array by the year of birth */
            case 2:
                sortPeople(people, sizeof(people)/sizeof(people[0]));
                printf("\nLista delle persone ordinate per anno di nascita:\n");
                for(int i=0;i<sizeof(people)/sizeof(people[0]);i++)
                    printf("%s %s\t%d\t%s\t%.2f€\n", people[i].name, people[i].surname, people[i].birthYear, people[i].town, people[i].netWorth);
                break;
            /* Find people for taxIDCode */
            case 3:
                /* ask for tax ID code */
                printf("Inserisci il codice fiscale della persona da cercare: ");
                scanf("%s", inputTaxIDCode);
                /* find the result and print it */
                indexResult = findPersonByTaxIDCode(people, sizeof(people)/sizeof(people[0]), inputTaxIDCode);
                if(indexResult == -1)
                    printf("\nPersona non trovata.\n");
                else
                    printf("\nPersona trovata:\t%s %s\t%d\t%s\t%s\n", people[indexResult].name, people[indexResult].surname, people[indexResult].birthYear, people[indexResult].town, people[indexResult].taxIDCode);
                break;
            /* view people with minimum net worth */
            case 4:
                /* ask for net worth */
                do{
                    printf("Inserisci il reddito minimo: ");
                    scanf("%lf", &inputNetWorth); 
                    if(inputNetWorth < 0)
                        printf("\nInput non può essere negativo. Riprova\n");
                }while(inputNetWorth < 0);
                /* select and print the people */
                selectPeoplebyNetWorth(people, sizeof(people)/sizeof(people[0]), inputNetWorth, selectedPeople);
                printf("\nLe persone con un reddito superiore a %.2f€ sono: \n", inputNetWorth);
                printSelectedPeople(people, sizeof(people)/sizeof(people[0]), selectedPeople);
                break;
            /* calculate average net worth */
            case 5:
                printf("\nLa media del reddito annuale delle persone e' %.2f€\n", averageNetWorth(people, sizeof(people)/sizeof(people[0])));
                break;
            /* find people born on a specific year */
            case 6:
                /* ask for year of birth */
                printf("Inserisci anno di nascita: ");
                scanf("%d", &inputBirthYear);
                /* select people and print the result */
                selectPeopleByBirthYear(people, sizeof(people)/sizeof(people[0]), inputBirthYear, selectedPeople);
                printf("\nLa persone nate nell'anno %d sono: \n", inputBirthYear);
                printSelectedPeople(people, sizeof(people)/sizeof(people[0]), selectedPeople);
                break;
            /* view inhabitants of a town */
            case 7:
                groupTownInhabitants(people, sizeof(people)/sizeof(people[0]), selectedPeople);
                break;
            default:
                printf("Uscita dal programma");
        }
    }while(choice != sizeof(options)/sizeof(options[0]));

    return 0;
}