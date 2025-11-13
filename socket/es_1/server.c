#include <stdio.h>      //std in-out
#include <stdlib.h>     //per utilizzo di certe funzioni:htonl,rand,....
#include <sys/socket.h> //funz. accept+bind+listen
#include <sys/types.h>  //funz. accept
#include <netinet/in.h> //definiscono la struttura degli indirizzi
#include <string.h>     //funz. stringhe
#include <errno.h>      //gestioni errori connessione
#include <ctype.h>      //bind
#include <unistd.h>     // file header che consente l'accesso alle API dello standard POSIX

#define SERVERPORT 1450 // per il computer deve essere compreso tra 1024 65535

int main(){
    /* definizione struct */
    struct sockaddr_in servizio;
    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY); // serve ad assegnare l'indirizzo convertendolo in bit
    servizio.sin_port = htons(SERVERPORT);        // converte la porta in bit
    int structLength = sizeof(servizio);

    char stringa[20]; // definizione stringa da inviare
    int socketfd, soa; // sono fd socket, risultato della system call accept
 
    socketfd = socket(AF_INET, SOCK_STREAM, 0);                           // seleziona il tipo di comunicazione, tipo (connection oriented o less) e protocollo (0 viene scelto un protocollo in automatico)
    bind(socketfd, (struct sockaddr*)&servizio, sizeof(servizio)); // lega dell'indirizzo dell'host ad un indirizzo indicativo della socket

    listen(socketfd, 10); // si mette in ascolto e indica quanti processi riesce ad accettare in coda

    /* while true per gestire le richieste */
    while(1){
        printf("Server in ascolto...");
        fflush(stdout);
        soa = accept(socketfd, (struct sockaddr*)&servizio, &structLength); // accetta la connessione in entrata
        /* lettura dalla socket delle informazioni */
        read(soa, stringa, sizeof(stringa)); // ora ci va la soa per verificare socket e stato connessione
        printf("\nStringa ricevuta: %s\n", stringa);
        close(soa); // chiudo la connessione
    }
    return 0;
}