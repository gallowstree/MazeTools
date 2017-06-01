//
// Created by Alvarado, Alejandro on 5/25/17.
//

#include "RemoteControl.h"
#include <SFML/Network.hpp>
#include <cstdlib>
#include <cstring>
#include <MazeNavCommon/Queue.h>

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

void RemoteControl::sendData(const char data[], size_t size) {
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect(ip, port);
    if (status != sf::Socket::Done)
    {
        printf("error connecting\n");
    }
    printf("Sending %s\n", data);
    socket.send(data, size);
    socket.disconnect();
}

void RemoteControl::sendRoute(Queue<int> * route) {
    const char *header = "ROUTE\nSTART\n";
    size_t headerLength = strlen(header);
    printf("headerLength %i\n", headerLength);
    char *buffer = new char[headerLength + route->size() + 1]();
    memcpy(buffer, header, headerLength);
    size_t i = headerLength;
    while (!route->isEmpty()) {
        int direction = route->dequeue();
        buffer[i++] = std::to_string(direction).c_str()[0];
        printf("%c,", buffer[i-1]);
    }
    buffer[i] = '\n';

    sendData(buffer);
}

void RemoteControl::sendData(const char *data) {
    sendData(data, strlen(data));
}
