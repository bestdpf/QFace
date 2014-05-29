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
        string str="0 0 1 1 1 0 0 1 1 1 1 0 0 0 1 0 0 0 1 1 1 1 1 1 1 1 0 0 0 0 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 1 1 1 0 1 1 1 1 42880 42752 -42880 44032 41472 -44160 -41472 8042 19132 16222 -18863 -16491 -34400000 -30400000 34400000 30400000 -8144 -7549 -8358 -7287 -8549 -7025 -9567 9274 37376 -42880 -8591 7567 44288 41088 -44160 -41216 -45312 -39936 -7930 7406 -7953 -8906 -6548 -8573 6858";
        sock->send(str.c_str(),str.length());
        sleep(10);
    }
    return 0;
}
