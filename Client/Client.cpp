#include <iostream>
#include <WinSock2.h>
#include <thread>
#include <list>
#include <vector>
#include <WS2tcpip.h>
#include <locale.h>

#pragma comment(lib, "Ws2_32.lib")
//std::list<SOCKET> ClientList;
//void Run(SOCKET);

enum OPERATION {
OPEN,CLOSE,UP,DOWN
};

struct Data {
    int ID;
    char Name[32];
    double Value;
    OPERATION Operation;
};
Data userData;

void ReadServer(SOCKET);

void PrintCommand() {
    setlocale(LC_ALL, "Russian");
    std::cout << "0 - Открыть счёт\n";
    std::cout << "1 - Закрыть счёт\n";
    std::cout << "2 - Пополнить счёт\n";
    std::cout << "3 - Снять счёт\n";
}

int main()
{
    std::cout << "Enter your name: ";
    std::cin >> userData.Name;

    std::cout << "\n";

    setlocale(LC_ALL, "Russian");
    WSADATA data;
    int e = WSAStartup(MAKEWORD(2, 2), &data);
    if (e != 0) {
        std::cout << "";
        return 1;
    }
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == SOCKET_ERROR) {
        std::cout << "Socket error 1.1" << std::endl;
        return 1;
    }
    
    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.S_un.S_un_b.s_b1 = 127;
    addr.sin_addr.S_un.S_un_b.s_b2 = 0;
    addr.sin_addr.S_un.S_un_b.s_b3 = 0;
    addr.sin_addr.S_un.S_un_b.s_b4 = 1;

    e = connect(clientSocket, (sockaddr*)(&addr), sizeof(addr));
    if (e != 0) {
        std::cout << "Socket error 1.2" << std::endl;
        return 1;
    }
    //// e=connect(clie)
    //int n = send(clientSocket, "Ping", 5, 0);
    //if (n < 0) {
    //    std::cout << "socket error 1.3\n";
    //    return 1;
    //}
    //char message[512];
    //memset(message, 0, 512);

    //n = recv(clientSocket, message, 512, 0);
    //if (n < 0) {
    //    std::cout << "Socket error 1.4" << std::endl;
    //    return 1;
    //}
    //std::cout << message << std::endl;

    int operation;
    new std::thread(ReadServer, clientSocket);

    while (true)
    {
        PrintCommand();
        std::cout << "\n";
        std::cin >> operation;
        std::cout << "\n";

        userData.Operation = (OPERATION)operation;
        switch (operation)
        {
        case OPERATION::OPEN:
            std::cout << "Enter bill number\n";
            break;
        case OPERATION::CLOSE:
            std::cout << "Enter bill number\n";
            break;
        case OPERATION::UP:
            std::cout << "Enter bill number\n";
            break;
        case OPERATION::DOWN:
            std::cout << "Enter bill number\n";
            break;  
        default:
            break;
        }
        int n = send(clientSocket, (char*)(&userData), sizeof(userData), 0);
            if (n < 0) {
                closesocket(clientSocket);
                std::cout << "Disconnected....";
                return -1;
            }

        //std::cout << "Введите сообщение: ";
        ////std::cin >> message;
        //std::cout << "\n";
        //n = send(clientSocket, message, 512, 0);
        //if (n < 0) {
        //    closesocket(clientSocket);
        //    std::cout << "Disconnected....";
        //    return -1;
        //}
    }
    return 0; 
}

void ReadServer(SOCKET s){}