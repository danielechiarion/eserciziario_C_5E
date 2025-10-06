#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

/* define struct for ingredients */
typedef struct
{
    char name[50];   // name of the ingredient
    double quantity; // quantity of the ingredient expressed in whatever unit
} ingredient_t;

/* define the struct for beverages */
typedef struct
{
    char name[50];               // name of the beverage
    int waterAmount;             // amount of water required for the beverage
    ingredient_t ingredients[5]; // array of ingredients for the beverage
} beverage_t;

/* define the beverages */
beverage_t beverages[5] = {
    {"Caffè", 30, {}},
    {"Cappuccino", 120, {{"Latte", 80}}},
    {"Tè", 150, {{"Limone", 10}}},
    {"Cioccolata", 120, {{"Latte", 50}, {"Cacao", 70}}},
    {"Orzo", 80, {{"Latte", 30}}}};

/* define the ingredients and
start with negative values,
so as to be verified later */
ingredient_t machineIngredients[3] = {
    {"Latte", -1},
    {"Cacao", -1},
    {"Limone", -1}};

/* define constants for the machine */
#define HEATERTEMPERATURE 60                         // expressed in °C
#define MINIMUMWATER 1000                            // expressed in mL
#define MAXIMUMTANK 10                               // maximum quantity of pods in the tank
#define WATERRELEASESPEED 5                          // quantity of water spread in mL/s
const int SUGARQUANTITIES[] = {0, 4, 8, 12, 16, 20}; // possible quanties of sugar

/* define global variables */
int currentTemperatureHeater = -1; // expressed in °C
int currentWaterLevel = -1;        // volume of water in the tank
int usedPodsCounter = -1;          // number of used pods
int sugarCounter = -1;             // counter of the grams of sugar reamined
int availablePodsCounter = -1;     // counter of the remaining available pods
int cupsCounter = -1;              // counter of plastic cups
int teaspoonsCounter = -1;         // counter of plastic teaspoons

/* START FUNCTIONS FOR THE PROGRAM */
/* function to clear the screen */
void clrScr()
{
#ifdef _WIN32      // Check if the OS is Windows
    system("cls"); // instruction for clearing cmd of Windows
#else
    system("clear"); // instruction for clearing shell of Linux / MacOS
#endif
}

/* boolean to check the water level */
bool checkWaterLevel()
{
    /* check the water level.
    In this case i put a random value */
    if (currentWaterLevel < 0)
        currentWaterLevel = (rand() % 2001) + 900;

    if (currentWaterLevel < MINIMUMWATER) // check if the water is enough
        return false;

    return true;
}

/* function to check the water into the tank */
bool checkUsedPods()
{
    /* check the used pods amounts
    In this case I generate a random number */
    if (usedPodsCounter < 0)
        usedPodsCounter = rand() % (MAXIMUMTANK + 1);

    if (usedPodsCounter == MAXIMUMTANK) // return the status
        return false;

    return true;
}

/* function to increase the temperature of the heater */
void checkTemperatureHeater()
{
    /* define variable to increase the temperature */
    const int DEGREESPERSECOND = 5;

    /* get the temperature.
    In this case I generate it if I don't have the value */
    if (currentTemperatureHeater < 0)
        currentTemperatureHeater = rand() % (HEATERTEMPERATURE + 1);

    /* continue while the heater hasn't reached
    the right temperature */
    printf("\n");
    while (currentTemperatureHeater < HEATERTEMPERATURE)
    {
        fflush(stdout);
        sleep(1);                                     // simulate the wait
        currentTemperatureHeater += DEGREESPERSECOND; // increase the temperature
        printf("\r\033Temperatura attuale: %d°C", currentTemperatureHeater);
    }
}

/* function to check the available pods
in the machine */
bool checkAvailablePods()
{
    /* if it's the first time and the value is
    not set the quantity.
    In this case I generate a random number */
    if (availablePodsCounter < 0)
        availablePodsCounter = rand() % 31;

    return availablePodsCounter > 0;
}

/* function to check the cups remaining */
bool checkCups()
{
    if (cupsCounter < 0)
        cupsCounter = rand() % 51;

    return cupsCounter > 0;
}

/* function to check the remaining teaspoons */
bool checkTeaspoons()
{
    if (teaspoonsCounter < 0)
        teaspoonsCounter = rand() % 51;

    return teaspoonsCounter > 0;
}

/* check if all the ingredients in the machine
are enough to prepare that specific beverage */
bool checkIngredients(int choice)
{
    ingredient_t *currentIngredients = beverages[choice].ingredients;
    int numIngredients = sizeof(beverages[choice].ingredients) / sizeof(beverages[choice].ingredients[0]);
    int numMachineIngredients = sizeof(machineIngredients) / sizeof(machineIngredients[0]);
    int i, j;

    for (i = 0; i < numIngredients; i++)
    {
        if (strlen(currentIngredients[i].name) == 0 || strcmp(currentIngredients[i].name, machineIngredients[j].name) != 0)
            continue;

        for (j = 0; j < numMachineIngredients; j++)
        {
            if (currentIngredients[i].quantity > machineIngredients[j].quantity)
                return false;
            else
                break;
        }

        if (j == numMachineIngredients)
            return false;
    }

    return true;
}

/* count all the secondary ingredients
contained in the machine. In this case I
will generate it randomly */
void countIngredients()
{
    for (int i = 0; i < sizeof(machineIngredients) / sizeof(machineIngredients[0]); i++)
    {
        if (machineIngredients[i].quantity < 0)
            machineIngredients[i].quantity = rand() % 301;
    }
}

/* function to simulate the menu for
the beverages */
int menu()
{
    int choice;
    int i;
    int size = sizeof(beverages) / sizeof(beverages[0]);

    do
    {
        printf("\n=== SCEGLI BEVANDA ==="); // output of the title
        for (i = 0; i < size; i++)
        {
            printf("\n[%d] %s - %dmL", (i + 1), beverages[i].name, beverages[i].waterAmount); // output of the options
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

    return choice - 1;
}

/* function to make the choice for the quantity of sugar */
int sugarChoice()
{
    int choice, indexSugar = 0; // it goes until the sugar it's available
    int size = sizeof(SUGARQUANTITIES) / sizeof(SUGARQUANTITIES[0]);

    /* control the quantity of sugar */
    if (sugarCounter < 0)
        sugarCounter = rand() % 501;

    do
    {
        printf("\n*** Scegli lo zucchero"); // output of the title
        for (int i = 0; i < size; i++)
        {
            /* check if the quantity of sugar is available
            before displaying it */
            if (SUGARQUANTITIES[i] <= sugarCounter)
                indexSugar = i;
            else
                break;

            printf("\n[%d] %d zuccheri", (i + 1), i); // output of the options
        }
        printf("\n");
        scanf("%d", &choice);
        /* error message */
        if (choice < 1 || choice > indexSugar + 1)
        {
            printf("\nValore errato. Riprova");
            clrScr();
        }
    } while (choice < 1 || choice > indexSugar + 1); // checking value

    return choice - 1;
}

/* function to make beverage */
void makeBeverage(int choice, int sugarChoice)
{
    /* check the amount of water*/
    if (beverages[choice].waterAmount > currentWaterLevel)
    {
        printf("\nQuantitativo di acqua non disponibile, riprova");
        return;
    }

    /* generate a wait time for the making
    of the beverage */
    int waitingTime = (int)ceil((double)beverages[choice].waterAmount / WATERRELEASESPEED);
    printf("\n");
    for (int i = waitingTime; i >= 0; i--)
    {
        printf("\r\033[KTempo di attesa: %ds", i); // cancella la riga prima di stampare
        fflush(stdout);
        sleep(1);
    }

    printf("\r\033Bevanda completata"); // output of the result
    fflush(stdout);

    /* update the variables */
    currentWaterLevel -= beverages[choice].waterAmount;
    usedPodsCounter++;
    availablePodsCounter--;
    if (teaspoonsCounter > 0)
        teaspoonsCounter--;
    cupsCounter--;
    sugarCounter -= SUGARQUANTITIES[sugarChoice];

    /* update the ingredients */
    ingredient_t *currentIngredients = beverages[choice].ingredients;
    int numIngredients = sizeof(beverages[choice].ingredients) / sizeof(beverages[choice].ingredients[0]);
    int numMachineIngredients = sizeof(machineIngredients) / sizeof(machineIngredients[0]);
    for (int i = 0; i < numIngredients; i++)
    {
        for (int j = 0; j < numMachineIngredients; j++)
        {
            if (strcmp(currentIngredients[i].name, machineIngredients[j].name) == 0)
                machineIngredients[j].quantity -= currentIngredients[i].quantity;
        }
    }
}

int main(int argc, char *argv[])
{
    /* variable declaration */
    int choice, choiceSugar;
    bool status;

    srand(time(NULL)); // set the time to NULL for random numbers

    countIngredients(); // generate the number of ingredients

    while (true)
    {
        status = true;
        /* check the amount of water and used pods */
        if (!checkWaterLevel())
        {
            printf("\nLivello acqua non sufficiente");
            status = false;
        }
        if (!checkUsedPods())
        {
            printf("\nSerbatoio cialde usate pieno");
            status = false;
        }
        if (!checkAvailablePods())
        {
            printf("\nNessuna cialda disponibile");
            status = false;
        }
        if (!checkCups())
        {
            printf("\nNessun bicchiere disponibile");
            status = false;
        }

        if (!status)
        {
            printf("\nSpegnimento macchina in corso...");
            sleep(5);
            exit(1);
        }

        checkTemperatureHeater(); // control the temperature of the heater and increase it

        /* get the choice and make the beverages */
        choice = menu();
        clrScr();
        choiceSugar = sugarChoice();

        /* check if the ingredients are available and
        if there's a teaspoon before making the beverage */
        if (!checkIngredients(choice))
        {
            printf("\nIngredienti non disponibili");
            sleep(3);
            clrScr();
            continue;
        }
        if (!checkTeaspoons())
            printf("\nLa bevanda non verrà servita con il cucchiaino");

        makeBeverage(choice, choiceSugar);
        clrScr();
    }

    return 0;
}
