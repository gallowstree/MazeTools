//
// Created by Alvarado, Alejandro on 5/25/17.
//

#include "RemoteControl.h"
#include <SFML/Network.hpp>
#include <cstdlib>
#include <cstring>

void RemoteControl::forward(float cm) {
    char *buffer = (char*) malloc(64 * sizeof(char));
    sprintf(buffer, "MOTOR\nFORWARD\n%f\n", cm);
    sendData(buffer);
}

void RemoteControl::backwards(float cm) {
    char *buffer = (char*) malloc(64 * sizeof(char));
    sprintf(buffer, "MOTOR\nBACKWARDS\n%f\n", cm);
    sendData(buffer);
}

void RemoteControl::clockwise(float degrees) {
    char *buffer = (char*) malloc(64 * sizeof(char));
    sprintf(buffer, "MOTOR\nCLOCKWISE\n%f\n", degrees);
    sendData(buffer);
}

void RemoteControl::counterclockwise(float degrees) {
    char *buffer = (char*) malloc(64 * sizeof(char));
    sprintf(buffer, "MOTOR\nCOUNTERCLOCKWISE\n%f\n", degrees);
    sendData(buffer);
}

void RemoteControl::sendData(char data[]) {
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect(ip, port);
    if (status != sf::Socket::Done)
    {
        printf("error connecting\n");
    }
    printf("Sending %s\n", data);
    socket.send(data, strlen(data));
    socket.disconnect();
}