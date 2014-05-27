#include<iostream>
#include<cstdio>
#include<Socket.h>
using namespace net;
int main(){
    TCPServerSocket * server= new TCPServerSocket(5004);
    TCPSocket * sock= server->accept();
    char buff[128];
    while(sock->recv(buff,127)>0){
        printf("get:\n%s\n",buff);
    }
    return 0;
}
