#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

/* define the struct for the car */
typedef struct
{
    char carModel[50];
    char brand[50];
    int registrationYear;
    int displacement;
    double price;
    char plate[10];
} car_t;

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

/* select maxium and minimum price
in the list of cars */
void selectMaxMinPrice(car_t cars[], int size, double *maxPrice, double *minPrice){
    /* first give to the car
    maximum and minimum */
    *maxPrice = cars[0].price;
    *minPrice = cars[0].price;

    /* then choose maximum and minimum price */
    for(int i=1;i<size;i++){
        if(cars[i].price > *maxPrice)
            *maxPrice = cars[i].price;
        else if(cars[i].price < *minPrice)
            *minPrice = cars[i].price;
    }
}

/* function to sort the cars by the 
year of the registration */
void sortCars(car_t cars[], int size){
    car_t tempCar;

    /* sort the cars by year of registration 
    using selection sort */
    for(int i=0;i<size-1;i++){
        for(int j=i+1;j<size;j++){
            if(cars[j].registrationYear < cars[i].registrationYear){
                tempCar = cars[i];
                cars[i] = cars[j];
                cars[j] = tempCar;
            }
        }
    }
}

/* function to select the cars over a certain price */
void selectCarsByPrice(car_t cars[], int size, double price, bool selectedCars[]){
    for(int i=0;i<size;i++){
        selectedCars[i] = false; // reset the position if it's necessary
        if(cars[i].price >= price)
            selectedCars[i] = true;
    }
}

/* function to display the cars 
flagged with true */
void displaySelectedCars(car_t cars[], int size, bool selectedCars[]){
    bool anySelected = false;
    for(int i=0;i<size;i++){
        if(selectedCars[i]){ // if the car is selected
            printf("%s %s\t%d\t%.2f\t%s\n", cars[i].carModel, cars[i].brand, cars[i].registrationYear, cars[i].price, cars[i].plate);
            anySelected = true;
        }
    }

    if(!anySelected)
        printf("\nNessuna macchina trovata\n");
}

/* function to research cars using the plate number */
int searchCarByPlate(car_t cars[], int size, char plate[]){
    for(int i=0;i<size;i++){
        if(strcmp(cars[i].plate, plate) == 0) // if the plates are the same
            return i; // return the index
    }
    return -1; // if the car is not found
}

/* function to select cars by registration year */
void selectCarByRegistrationYear(car_t cars[], int size, int year, bool selectedCars[]){
    for(int i=0;i<size;i++){
        selectedCars[i] = false; // reset the position if it's necessary
        if(cars[i].registrationYear == year)
            selectedCars[i] = true;
    }
}

/* function to calculate the average price of the cars */
double averageCarPrice(car_t cars[], int size){
    double sum = 0.0;

    for(int i=0;i<size;i++)
        sum += cars[i].price;

    return sum/size;
}

int main(int argc, char *argv[])
{
    /* define the variables */
    int choice;
    double maxPrice, minPrice;
    double price;
    int indexResult, registrationYear;
    char carPlate[10];
    /* define all the options for the menu */
    char options[][100] = {
        {"Vedi il prezzo più alto e quello più basso"},
        {"Ordina la lista di macchine"},
        {"Visualizza le auto da un certo prezzo"},
        {"Ricerca una macchina tramite targa"},
        {"Visualizza media prezzi"},
        {"Visualizza le auto con anno di immatricolazione"},
        {"Esci"}
    };
    /* define the list of cars */
    car_t cars[] = {
        {"Model S", "Tesla", 2020, 0, 79999.99, "AB123CD"},
        {"Panda", "Fiat", 2015, 1200, 8500.00, "CF456GH"},
        {"Civic", "Honda", 2018, 1500, 19950.50, "DE789IJ"},
        {"Golf", "Volkswagen", 2012, 1400, 12500.00, "KL012MN"},
        {"Megane", "Renault", 2019, 1600, 17500.75, "OP345QR"}};
    /* define an array to select multiple cars */
    bool selectedCars[sizeof(cars)/sizeof(cars[0])] = {false};

    do
    {
        choice = menu(options, sizeof(options)/sizeof(options[0]));

        switch(choice){
            /* select maximum and minimum price */
            case 1:
                selectMaxMinPrice(cars, sizeof(cars)/sizeof(cars[0]), &maxPrice, &minPrice); // select maximum and minimum price
                printf("\nIl prezzo massimo e' %.2f€\nIl prezzo minimo e' %.2f€", maxPrice, minPrice);
                break;
            /* order cars by the year of registration */
            case 2:
                sortCars(cars, sizeof(cars)/sizeof(cars[0]));
                /* print the result */
                printf("\nLista delle macchine ordinate per anno di immatricolazione:\n");
                for(int i=0;i<sizeof(cars)/sizeof(cars[0]);i++) // display the list of cars
                    printf("%s %s\t%d\t%.2f\t%s\n", cars[i].carModel, cars[i].brand, cars[i].registrationYear, cars[i].price, cars[i].plate);
                break;
            /* display the cars that have a certain price */
            case 3:
                do{
                    printf("\nInserisci il prezzo: ");
                    scanf("%lf", &price);
                    if(price < 0)
                        printf("\nValore errato. Riprova");
                }while(price < 0);
                /* then select the cars and display them */
                selectCarsByPrice(cars, sizeof(cars)/sizeof(cars[0]), price, selectedCars);
                displaySelectedCars(cars, sizeof(cars)/sizeof(cars[0]), selectedCars);
                break;
            /* search a car by the plate */
            case 4:
                printf("Inserisci la targa: ");
                scanf("%s", carPlate);
                indexResult = searchCarByPlate(cars, sizeof(cars)/sizeof(cars[0]), carPlate);
                if(indexResult != -1) // if the car is found
                    printf("%s %s\t%d\t%.2f\t%s\n", cars[indexResult].carModel, cars[indexResult].brand, cars[indexResult].registrationYear, cars[indexResult].price, cars[indexResult].plate);
                else
                    printf("\nNessuna macchina trovata\n");
                break;
            /* display the average price of the cars */
            case 5:
                printf("\nLa media dei prezzi e' %.2f€\n", averageCarPrice(cars, sizeof(cars)/sizeof(cars[0])));
                break;
            /* select cars by registration year */
            case 6:
                do{
                    printf("\nInserisci l'anno di immatricolazione: ");
                    scanf("%d", &registrationYear);
                    if(registrationYear < 1886 || registrationYear>localtime(&(time_t){time(NULL)})->tm_year+1900) // control if the year is valid
                        printf("\nAnno non valido. Riprova");
                }while(registrationYear < 1886 || registrationYear>localtime(&(time_t){time(NULL)})->tm_year+1900);
                /* then select the cars and display them */
                selectCarByRegistrationYear(cars, sizeof(cars)/sizeof(cars[0]), registrationYear, selectedCars);
                displaySelectedCars(cars, sizeof(cars)/sizeof(cars[0]), selectedCars);
                break;
            default:
                printf("\nUscita in corso...");
                break;
        }
    } while (choice != sizeof(options)/sizeof(options[0]));

    return 0;
}