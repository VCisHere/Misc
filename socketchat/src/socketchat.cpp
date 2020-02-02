#include <iostream>
#include "receiver.h"
#include "sender.h"

void MoveCursorTo(int x, int y)
{
    static HANDLE m = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cp = { x,y };
    SetConsoleCursorPosition(m, cp);
}

int main() {

    Receiver *receiver = new Receiver();
    receiver->Start();
    
    std::cout << "ipv6 address:";

    char ip[60] = { '\0' };
    std::cin.get(ip, 46);
    std::cin.get();

    system("cls");

    Sender *sender = new Sender();
    sender->Set(ip, 6666);
    
    char str[255];
    while (true) {
        std::cin >> str;
        system("cls");
        MoveCursorTo(0, 0);
        sender->Send(str);
    }
}