#pragma once
#ifndef RECEIVER_H_
#define RECEIVER_H_

#ifndef WINSOCK2_H_
#define WINSOCK2_H_
#include <Winsock2.h>
#endif // !WINSOCK2_H_

#ifndef WS2TCPIP_H_
#define WS2TCPIP_H_
#include <Ws2tcpip.h>
#endif // !WS2TCPIP_H_

#ifndef PTHREAD_H_
#define PTHREAD_H_
#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>
#pragma comment(lib, "pthreadVC2.lib")
#endif // !PTHREAD_H_

#include <iostream>
#pragma comment(lib, "WS2_32")

class Receiver
{
private:

    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    int sockSrv;
    sockaddr_in6 addrSrv;
    bool hasStarted;
    pthread_t threadID;

    int Init();
    static void* Listening(void *args);

public:
    Receiver();
    virtual ~Receiver();
    int Start();
    virtual void OnReceive(SOCKET &sockConn);
};

struct ARG {
    Receiver* pThis;
};

#endif // ! RECEIVER_H_