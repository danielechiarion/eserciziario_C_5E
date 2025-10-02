#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

/* define the struct for beverages */
typedef struct
{
    char name[50]; //name of the beverage
    int waterAmount; //amount of water required for the beverage
}beverage_t;

/* define the beverages */
beverage_t beverages[5] = {
    {"Caffè", 30},
    {"Cappuccino", 120},
    {"Tè", 150},
    {"Cioccolata", 120},
    {"Orzo", 80}
};

/* define constants for the machine */
#define HEATERTEMPERATURE 60 // expressed in °C
#define MINIMUMWATER 1000 // expressed in mL
#define MAXIMUMTANK 10 // maximum quantity of pods in the tank
#define WATERRELEASESPEED 5 // quantity of water spread in mL/s

/* define global variables */
int currentTemperatureHeater = -1; // expressed in °C
int currentWaterLevel = -1; // volume of water in the tank
int usedPodsCounter = -1; // number of used pods

/* START FUNCTIONS FOR THE PROGRAM */
/* function to clear the screen */
void clrScr()
{
	#ifdef _WIN32 // Check if the OS is Windows
        system("cls"); // instruction for clearing cmd of Windows
    #else
        system("clear"); // instruction for clearing shell of Linux / MacOS
    #endif
}

/* boolean to check the water level */
bool checkWaterLevel(){
    /* check the water level. 
    In this case i put a random value */
    if(currentWaterLevel < 0)
        currentWaterLevel = (rand() % 2001) + 900;
    
    if(currentWaterLevel < MINIMUMWATER) // check if the water is enough
        return false;

    return true;
}

/* function to check the water into the tank */
bool checkUsedPods(){
    /* check the used pods amounts
    In this case I generate a random number */
    if(usedPodsCounter < 0)
        usedPodsCounter = rand() % (MAXIMUMTANK+1);

    if(usedPodsCounter == MAXIMUMTANK) // return the status
        return false;

    return true;
}

/* function to increase the temperature of the heater */
void checkTemperatureHeater(){
    /* define variable to increase the temperature */
    const int DEGREESPERSECOND = 5;

    /* get the temperature. 
    In this case I generate it if I don't have the value */
    if(currentTemperatureHeater < 0)
        currentTemperatureHeater = rand() % (HEATERTEMPERATURE+1);

    /* continue while the heater hasn't reached
    the right temperature */
    printf("\n");
    while(currentTemperatureHeater < HEATERTEMPERATURE){
        printf("\r\033Temperatura attuale: %d°C", currentTemperatureHeater);
        fflush(stdout);
        sleep(1); // simulate the wait
        currentTemperatureHeater += DEGREESPERSECOND; // increase the temperature
    }
}

/* function to simulate the menu for 
the beverages */
int menu() {
    int choice;
    int i;
    int size = sizeof(beverages)/sizeof(beverages[0]);

    do {
        printf("\n=== SCEGLI BEVANDA ==="); //output of the title
        for (i = 0; i < size; i++) {
            printf("\n[%d] %s - %dmL", (i+1), beverages[i].name, beverages[i].waterAmount); //output of the options
        }
        printf("\n");
        scanf("%d", &choice);
        /* error message */
        if (choice < 1 || choice > size) {
            printf("\nValore errato. Riprova");
            clrScr();
        }
    } while (choice < 1 || choice > size); //checking value

    return choice-1;
}

/* function to make beverage */
void makeBeverage(int choice){
    /* check the amount of water*/
    if(beverages[choice].waterAmount>currentWaterLevel){
        printf("\nQuantitativo di acqua non disponibile, riprova");
        return;
    }

    /* generate a wait time for the making
    of the beverage */
    int waitingTime = (int)ceil((double)beverages[choice].waterAmount / WATERRELEASESPEED);
    printf("\n");
    for(int i=waitingTime; i>=0; i--){
        printf("\r\033[KTempo di attesa: %ds", i); // cancella la riga prima di stampare
        fflush(stdout);
        sleep(1);
    }

    printf("\r\033Bevanda completata"); // output of the result
    fflush(stdout);
    
    /* update the variables */
    currentWaterLevel -= beverages[choice].waterAmount;
    usedPodsCounter++;
}

int main(int argc, char *argv[]){
    /* variable declaration */
    int choice;
    bool status;

    srand(time(NULL)); // set the time to NULL for random numbers

    while(true){
        status = true; 
        /* check the amount of water and used pods */
        if(!checkWaterLevel()){
            printf("\nLivello acqua non sufficiente");
            status = false;
        }
        if(!checkUsedPods()){
            printf("\nSerbatoio cialde usate pieno");
            status = false;
        }
        if(!status){
            printf("\nSpegnimento macchina in corso...");
            sleep(5);
            exit(1);
        }

        /* get the choice and make the beverages */
        choice = menu();
        makeBeverage(choice);
        
        clrScr();
    }

    return 0;
}
