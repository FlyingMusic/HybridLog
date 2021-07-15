#ifndef __NET_CLIENT__
#define __NET_CLIENT__

#include <stdio.h>

class NetClient {
public:
    int connect(const char *ip, int port);
    int sendData();
    int close();
private:
    char m_ip[512];
    int m_port;
    int m_fd;
};

#endif
