#include <iostream>
#include <WinSock2.h>
#include <thread>
#include <list>
#include <vector>
#include <WS2tcpip.h>
#include <locale.h>

#pragma comment(lib, "Ws2_32.lib")

struct Bill {
    int Client;
    double Balance;
};

struct Client
{
    SOCKET Socket;
    char Name[32];
    int ID;
    Client(SOCKET s, int id) {
        Socket = s;
        ID = id;
    }
};

enum OPERATION {
    OPEN, CLOSE, UP, DOWN
};

struct Data {
    int ID;
    double Value;
    OPERATION Operation;
    char Name[32];
};

std::list<Client*> ClientList;
void Run(Client*);

int main()
{
    WSADATA data;
    int e = WSAStartup(MAKEWORD(2, 2), &data);
    if (e != 0) {
        std::cout << "";
        return 1;
    }
    SOCKET serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == 0) {
        std::cout << "Socket error1" << std::endl;
        return 1;
    }
    sockaddr_in serverAdress;
    memset(&serverAdress, 0, sizeof(serverAdress));
    serverAdress.sin_family = PF_INET;
    serverAdress.sin_port = htons(8080);
    serverAdress.sin_addr.S_un.S_un_b.s_b1 = 127;
    serverAdress.sin_addr.S_un.S_un_b.s_b2 = 0;
    serverAdress.sin_addr.S_un.S_un_b.s_b3 = 0;
    serverAdress.sin_addr.S_un.S_un_b.s_b4 = 1;
    e = bind(serverSocket, (sockaddr*)(&serverAdress), sizeof(serverAdress));
    if (e ==SOCKET_ERROR) {
        std::cout << "bind socket error" << std::endl;
        return 1;
    }
    e = listen(serverSocket, 100);
    if (e < 0) {
        std::cout << "listen socket error" << std::endl;
        return 1;
    };
    int id = 1;
    while (true)
    {
        std::cout << "wait...";
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
        Client* client = new Client(clientSocket, id++);
        new std::thread(Run, client);
        ClientList.push_back(client);
    }
    return 0;
}

void Run(Client *client) {
    setlocale(LC_ALL, "Russian");
    int n = 0;
    Data recvDate;
    while (true)
    {
        n = recv(client->Socket, (char*)(&recvDate), sizeof(recvDate), 0);
        if (n < 0) {
            return;
        }
        switch (recvDate.Operation)
        {
        case OPERATION::OPEN:
            
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
    }
    ClientList.remove(client);

}