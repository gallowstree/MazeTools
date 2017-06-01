//
// Created by Alvarado, Alejandro on 5/25/17.
//

#ifndef TEST_CLIENT_REMOTECONTROL_H
#define TEST_CLIENT_REMOTECONTROL_H


#include <MazeNavCommon/Queue.h>

class RemoteControl {


    const char* ip = "192.168.1.9";
    unsigned short port = 4420;
public:
    void counterclockwise(float degrees);

    void clockwise(float degrees);

    void backwards(float cm);

    void forward(float cm);

    void sendRoute(Queue<int> *route);

    void sendData(const char *data);

    void sendData(const char *data, size_t size);
};


#endif //TEST_CLIENT_REMOTECONTROL_H
