//
// Created by Alvarado, Alejandro on 5/25/17.
//

#ifndef TEST_CLIENT_REMOTECONTROL_H
#define TEST_CLIENT_REMOTECONTROL_H


class RemoteControl {

    void sendData(char *data);

    const char* ip = "192.168.1.192";
    unsigned short port = 4420;
public:
    void counterclockwise(float degrees);

    void clockwise(float degrees);

    void backwards(float cm);

    void forward(float cm);
};


#endif //TEST_CLIENT_REMOTECONTROL_H
