#include<iostream>
#include<cstdio>
#include<Socket.h>
using namespace net;
int main(){
    TCPServerSocket * server= new TCPServerSocket(50011);
    TCPSocket * sock= server->accept();
    char buff[1024];
    while(int len=sock->recv(buff,1023)>0){
        printf("\nget: %d\n\n\n----------------\n\n %s",len,buff);
    }
    return 0;
}
