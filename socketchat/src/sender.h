#pragma once
#ifndef SENDER_H_
#define SNEDER_H_

#ifndef WINSOCK2_H_
#define WINSOCK2_H_
#include <Winsock2.h>
#endif // !WINSOCK2_H_

#ifndef WS2TCPIP_H_
#define WS2TCPIP_H_
#include <Ws2tcpip.h>
#endif // !WS2TCPIP_H_

#include <iostream>
#pragma comment(lib, "WS2_32")

class Sender {

private:

    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    int sockClient;
    sockaddr_in6 addrSrv;
    bool hasSet;

    int Init();

public:
    Sender();
    virtual ~Sender();
    void Set(const char *ip, const int &port);
    void Send(const char *str);
};

#endif // ! SNEDER_H_