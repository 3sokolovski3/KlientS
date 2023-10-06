#include <iostream>
#pragma comment (lib,"ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string>
#pragma warning(disable: 4996) 
SOCKET CONECTION;
void eror()
{
    std::cout << "Error " << std::endl;
    
}



void ClientHand(int index) {
    int msg_size;
    while (true)
    {
        recv(CONECTION, (char*)&msg_size, sizeof(int), NULL);
        char* msg = new char[msg_size + 1];
        msg[msg_size] = '\0';
        recv(CONECTION, msg, msg_size, NULL);
        std::cout << msg << std::endl;
        delete[] msg;
    }
}
int main()
{
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData) != 0)
    {
        eror;
        return 1;
    }
    SOCKADDR_IN addr;
    int sizeaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);
    addr.sin_family = AF_INET;
    CONECTION = socket(AF_INET, SOCK_STREAM, NULL);
    if (connect(CONECTION, (SOCKADDR*)&addr, sizeof(addr)) != 0)
    {
        eror;
        return 1;
         
    }
    std::cout << "connected" << std::endl;

    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHand, NULL, NULL, NULL);

    std::string msg1;
    while (true)
    {
        std::getline(std::cin, msg1);
        int msg_size = msg1.size();
        send(CONECTION, (char*)&msg_size, sizeof(int), NULL);
        send(CONECTION, msg1.c_str(), msg_size, NULL);
        Sleep(10);
    }
    return 0;
}
