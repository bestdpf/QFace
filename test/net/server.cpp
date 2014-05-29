#include<iostream>
#include<cstdio>
#include<Socket.h>
using namespace net;
int main(){
    TCPServerSocket * server= new TCPServerSocket(50011);
    TCPSocket * sock= server->accept();
    char buff[1024];
    while(sock->recv(buff,1023)>0){
        printf("get:\n%s\n",buff);
    }
    return 0;
}
