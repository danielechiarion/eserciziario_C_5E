#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

int main(){
    /* constant definition */
    const int SERVERPORT = 1450;
    const int TAXINUMBER = 10;
    const char REQUEST_TAXI_CODE[] = "RICHIESTA", RETURN_TAXI_CODE[] = "RIPRISTINO";

    /* variable definition */
    char type[20], startingPoint[50], destinationPoint[50];
    int taxiCounter = TAXINUMBER;
    bool result;

    /* define the struct for the connection */
    struct sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = htonl(INADDR_ANY);
    service.sin_port = htons(SERVERPORT);
    int serviceSize = sizeof(service);

    /* create socket, bind it and 
    put it into listening mode */
    int sockefd = socket(AF_INET, SOCK_STREAM, 0);
    bind(sockefd, (struct sockaddr*)&service, sizeof(service));
    listen(sockefd, TAXINUMBER); // put the queue size as many taxi are available at maximum

    while(true){
        int soa = accept(sockefd, (struct sockaddr*)&service, &serviceSize);
        fflush(stdout);

        /* read request from client and process it */
        read(soa, type, sizeof(type));
        if(strcmp(type,REQUEST_TAXI_CODE)==0){ // if it's a request for a taxi
            /* read staring and destination point
            and print the result */
            read(soa, startingPoint, sizeof(startingPoint));
            read(soa, destinationPoint, sizeof(destinationPoint));

            /* verify if the taxis are available and 
            then print the results */
            result = taxiCounter > 0;
            write(soa, &result, sizeof(result));
            if(result){
                taxiCounter--;
                printf("Nuova richiesta di taxi da %s a %s accolta\n", startingPoint, destinationPoint);
            }else
                printf("Nuova richiesta di taxi da %s a %s rifiutata. Taxi esauriti\n", startingPoint, destinationPoint);
        }else if(strcmp(type, RETURN_TAXI_CODE)==0) { //if the taxi has finished its service
            /* but check if the
            maximum number has already been reached */
            if(taxiCounter<TAXINUMBER){
                taxiCounter++;
                printf("Taxi rientrato. Taxi disponibili: %d", taxiCounter);
            }
        }else{ // if the code is unknown
            printf("Codice richiesta %s non processabile", type);
        }
    }

    return 0;
}