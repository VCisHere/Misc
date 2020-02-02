#include "receiver.h"

int Receiver::Init() {

    hasStarted = false;
    wVersionRequested = MAKEWORD(1, 1);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        return 1;
    }

    if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
        WSACleanup();
        return 2;
    }

    if ((sockSrv = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP)) == -1) {
        printf("socket error\n");
        return 3;
    }

    memset(&addrSrv, 0, sizeof(sockaddr_in6));
    addrSrv.sin6_port = htons(6666);
    addrSrv.sin6_family = AF_INET6;
    addrSrv.sin6_addr = in6addr_any;

    if (bind(sockSrv, (sockaddr*)&addrSrv, sizeof(sockaddr_in6)) == -1) {
        printf("bind error\n");
        return 4;
    }
    return 0;
}

void* Receiver::Listening(void *args) {
    ARG* arg = (ARG*)args;
    listen(arg->pThis->sockSrv, 5);
    sockaddr_in6 addrClient;
    int len = sizeof(sockaddr_in6);
    while (true) {
        SOCKET sockConn = accept(arg->pThis->sockSrv, (sockaddr*)&addrClient, &len);
        arg->pThis->OnReceive(sockConn);
    }
}

Receiver::Receiver() {
    Init();
}

Receiver::~Receiver() {
    closesocket(sockSrv);
    WSACleanup();
    if (hasStarted) {
        pthread_exit(NULL);
    }
}

int Receiver::Start() {
    if (hasStarted) {
        return 1;
    }

    hasStarted = true;
    
    ARG* arg = new ARG();
    arg->pThis = this;
    int ret = pthread_create(&threadID, NULL, Listening, (void*)arg);
    if (ret != 0) {
        std::cout << "pthread_create error: error_code=" << ret << std::endl;
    }
    return 0;
}

void Receiver::OnReceive(SOCKET &sockConn) {
    char sendBuf[50];
    /*sprintf_s(sendBuf, "Welcome to here!");

    send(sockConn, sendBuf, strlen(sendBuf) + 1, 0);*/

    char recvBuf[50];
    recv(sockConn, recvBuf, 50, 0);
    printf("OnReceive::%s\n", recvBuf);
    closesocket(sockConn);
}