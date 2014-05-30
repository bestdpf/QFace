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
        string str="0 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 1 1 1 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0";
        sock->send(str.c_str(),str.length());
        sleep(1);
    }
    return 0;
}
