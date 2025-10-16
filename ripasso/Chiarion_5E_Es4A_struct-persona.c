#include <stdio.h>
#include <string.h>

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


int main(int argc, char *argv[]){
    /* define 20 persons */
    person_t persons[20] = {
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
        
    }

    return 0;
}