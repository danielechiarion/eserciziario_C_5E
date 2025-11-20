#include <stdio.h>      //std in-out
#include <stdlib.h>     //per utilizzo di certe funzioni:htonl,rand,....
#include <sys/socket.h> //funz. accept+bind+listen
#include <sys/types.h>  //funz. accept
#include <netinet/in.h> //definiscono la struttura degli indirizzi
#include <string.h>     //funz. stringhe
#include <errno.h>      //gestioni errori connessione
#include <ctype.h>      //bind
#include <unistd.h>     // file header che consente l'accesso alle API dello standard POSIX
#include <arpa/inet.h> // per la definizione di inet_addr

/* definizione constante */
#define SERVERPORT 1313 // per il computer deve essere compreso tra 1024 65535
#define DESTINATIONADDRESS "192.168.60.155"

int main()
{
    /* definizione struct */
    struct sockaddr_in servizio;
    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = inet_addr(DESTINATIONADDRESS); // serve ad assegnare l'indirizzo convertendolo in bit
    servizio.sin_port = htons(SERVERPORT);        // converte la porta in bit

    char stringa[50]; // definizione stringa da inviare
    int socketfd;     // file descriptor socket da restituire alla creazione

    socketfd = socket(AF_INET, SOCK_STREAM, 0);                           // seleziona il tipo di comunicazione, tipo (connection oriented o less) e protocollo (0 viene scelto un protocollo in automatico)
    connect(socketfd, (struct sockaddr*)&servizio, sizeof(servizio)); // verifica se la socket ha avuto successo, vuole struct per il destinatario e dimensione della struct

    /* richiedo l'inserimento della stringa */
    printf("Inserisci la stringa: ");
    scanf("%s", stringa);

    /* invio della stringa nella socket */
    write(socketfd, stringa, sizeof(stringa)); // funziona con le system call
    close(socketfd);                           // chiudo la socket

    return 0;
}