#include<iostream>
#include<cstdio>
#include<cstring>
#include<unistd.h>
#include<Socket.h>
using namespace net;
int main(){
    TCPSocket *sock= new TCPSocket("127.0.0.1",50011);
    int i;
    for(i=0;i<10;i++)
    {
        char str[128];
        sprintf(str,"xxxxxxxxxxxxx %d",i);
        sock->send(str,128);
        sleep(1);
    }
    return 0;
}
