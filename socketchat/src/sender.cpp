#include "sender.h"

int Sender::Init() {
    hasSet = false;

    wVersionRequested = MAKEWORD(1, 1);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        return 1;
    }

    if (LOBYTE(wsaData.wVersion) != 1 ||
        HIBYTE(wsaData.wVersion) != 1) {
        WSACleanup();
        return 2;
    }

    return 0;
}

Sender::Sender() {
    Init();
}

Sender::~Sender() {
    WSACleanup();
}

void Sender::Set(const char *ip, const int& port) {
    memset(&addrSrv, 0, sizeof(sockaddr_in6));
    addrSrv.sin6_port = htons(port);
    addrSrv.sin6_family = AF_INET6;
    inet_pton(AF_INET6, ip, &addrSrv.sin6_addr);
    hasSet = true;
}

void Sender::Send(const char *str) {
    if (!hasSet) {
        std::cout << "please set before send" << std::endl;
        return;
    }

    sockClient = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);

    if (connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(sockaddr_in6)) != 0) {
        std::cout << "connect failed" << std::endl;
    }
    
    if (send(sockClient, str, strlen(str) + 1, 0) != strlen(str) + 1) {
        std::cout << "send failed" << std::endl;
    }
    closesocket(sockClient);
}
