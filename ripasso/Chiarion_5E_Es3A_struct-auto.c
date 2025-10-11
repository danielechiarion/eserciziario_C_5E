#include <string.h>
#include <stdlib.h>

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
void selectMaxMinPrice(car_t cars[], int size, int *maxPrice, int *minPrice){
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

void sortCars(car_t cars[], int size){
    car_t tempCar;

    /* sort the cars by year of registration 
    using selection sort */
    for(int i=0;i<size-1;i++){
        for(int j=i+1;j<size;j++){
            if(cars[])
        }
    }
}

int main(int argc, char *argv[])
{
    /* define the variables */
    int choice;
    int *maxPrice, *minPrice;
    /* define all the options for the menu */
    char options[][100] = {
        {"Vedi il prezzo più alto e quello più basso"},
        {"Ordina la lista di macchine"},
        {"Visualizza le auto da un certo prezzo"},
        {"Ricerca una macchina tramite targa"},
        {"Visualizza media prezzi"},
        {"Visualizza le auto con anno di immatricolazione"}};
    /* define the list of cars */
    car_t cars[] = {
        {"Model S", "Tesla", 2020, 0, 79999.99, "AB123CD"},
        {"Panda", "Fiat", 2015, 1200, 8500.00, "CF456GH"},
        {"Civic", "Honda", 2018, 1500, 19950.50, "DE789IJ"},
        {"Golf", "Volkswagen", 2012, 1400, 12500.00, "KL012MN"},
        {"Megane", "Renault", 2019, 1600, 17500.75, "OP345QR"}};

    do
    {
        choice = menu(options, sizeof(options)/sizeof(options[0]));

        switch(choice){
            /* select maximum and minimum price */
            case 1:
                selectMaxMinPrice(cars, sizeof(cars)/sizeof(cars[0]), &maxPrice, &minPrice); // select maximum and minimum price
                printf("\nIl prezzo massimo e' %d\nIl prezzo minimo e' %d", maxPrice, minPrice);
                break;
            /* order cars by the year of registration */
            case 2:
                break;
        }
    } while (choice != sizeof(options)/sizeof(options[0]));
    

    return 0;
}