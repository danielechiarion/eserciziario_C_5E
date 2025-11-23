#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

/* define a struct to define the name
and the corresponding code as the input of the server */
typedef struct
{
    char name[50];
    int serverCode;
} ServerInput_t;

/* define the list of server inputs to use
KEEP THE ENDING REQUEST AS THE LAST ONE */
ServerInput_t options[] = {
    {"Sasso", 0},
    {"Carta", 1},
    {"Forbice", 2},
    {"Esci", 9}};

/* function to get the choice
from the user and check the validity */
int menu()
{
    int optionsLength = sizeof(options) / sizeof(options[0]); // get the length of the options
    int choice;                                               // declare a value for the options

    do
    {
        printf("\nSeleziona tra le seguenti opzioni:\n");
        for (int i = 1; i <= optionsLength; i++)
            printf("[%d] %s\n", i, options[i].name); // print each option
        scanf("%d", &choice);

        /* control if the option selected is correct */
        if (choice < 1 || choice > optionsLength)
            printf("Valore inserito erraton\n");
    } while (choice < 1 || choice > optionsLength);

    return choice;
}

/* function to parse the result and write them
into the corresponding variables */
void parseResult(char input[], int *matchResult, int *firstScore, int *secondScore)
{
    char *token;
    char *buffer = input;

    for (int i = 0; i < 3; i++)
    {
        token = __strtok_r(buffer, " ", &buffer); // get the part of the string
        /* select the variable where to
        save the result based on the position
        of the data just read */
        if (i == 0)
            *matchResult = atoi(token);
        else if (i == 1)
            *firstScore = atoi(token);
        else if (i == 2)
            *secondScore = atoi(token);
    }
}

int main()
{
    /* constant definition */
    const int SERVERPORT = 1450;
    const char *SERVERADDRESS = "127.0.0.1";

    /* define the struct for the address */
    struct sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr(SERVERADDRESS);
    service.sin_port = SERVERPORT;

    /* variable definition */
    int userChoice;
    int currentResult, scoreServer, scoreClient;
    char serverOutput[50];

    /* create socket and connect it
    handling errors */
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
    {
        printf("Creazione socket non riuscita\n");
        exit(1);
    }

    if (connect(socketfd, (struct sockaddr *)&service, sizeof(service)) < 0)
    {
        printf("Errore di connessione al server\n");
        exit(1);
    }

    printf("Connesso al server...\n"); // output of successful connection

    for (;;)
    {
        userChoice = menu();                                           // get the choice
        write(socketfd, &options[userChoice].serverCode, sizeof(int)); // send the option

        /* continue with the cycle
        till the user doesn't want to finish */
        if (userChoice != sizeof(options) / sizeof(options[0]))
            break;

        /* read the output of the server and process it,
        and print it */
        read(socketfd, serverOutput, sizeof(serverOutput));
        parseResult(serverOutput, &currentResult, &scoreClient, &scoreServer);
        /* understand if it's a win, a lose
        or a draw and then print thre current score */
        if (currentResult == 0)
            printf("Risultato: Pareggio\n");
        else if (currentResult == 1)
            printf("Risultato: Client vince\n");
        else
            printf("Risultato: Server vince\n");

        printf("Punteggio:\tServer: %d\tClient: %d", scoreServer, scoreClient);
    }

    /* if the connection has to be finished
    close the socket */
    close(socketfd);

    return 0;
}