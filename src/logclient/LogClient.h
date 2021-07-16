#ifndef __LOG_CLIENT__
#define __LOG_CLIENT__

#include "NetClient.h"

class LogClient {
public:
    int sendRequest();
    int recvResponce();
    int sendData();
    int sendFinish();
private:
    NetClient m_netClient;
};

#endif
