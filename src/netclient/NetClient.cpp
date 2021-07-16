#include "NetClient.h"
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>  
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int NetClient::connect(const char *ip, int port) {
    if (NULL == ip || port < 0) {
        printf("NetClient connect param is invalid!\n");
        return -1;
    }
    strncpy(m_ip, ip, sizeof(m_ip));
    m_port = port;
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket < 0) {
        printf("socket fd[%d] is invalid!\n", socketfd);
        return -1;
    }
    printf("pthreadid[%lu]: socket[%d] success...\n", pthread_self(), socketfd);

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(m_port);
    inet_aton(m_ip, &server_addr.sin_addr);
    unsigned long ul = 1;
    ioctl(socketfd, FIONBIO, &ul); //非阻塞 需要自己控制等待时间
    int connect_ret = -1; 
    int connect_count = 0;
    int max_try_times = 3;

    do {
        connect_ret = ::connect(socketfd, (const struct sockaddr *)&server_addr, sizeof(server_addr));
        if (0 == connect_ret) {
            break;
        }
        if (EINPROGRESS == errno || EINTR == errno) {
            connect_count++;
            usleep(200 * connect_count);
            continue;
        } else {
            break;
        }
    } while(connect_count < max_try_times);

    if(0 != connect_ret) {
        printf("pthreadid[%lu]: connect error[%s]\n", pthread_self(), strerror(errno));
        ::close(socketfd);
        return -1;
    }
    printf("pthreadid[%lu]: connect success!\n", pthread_self());
    m_fd = socketfd;
    return 0;
}
int NetClient::sendData(void *data, int len) {
    int sendlen = send(m_fd, data, len, MSG_DONTWAIT);
    if(sendlen != len) {
        printf("pthreadid[%lu]: send request error[%s]\n", pthread_self(), strerror(errno));
        return -1;
    }
    printf("pthreadid[%lu]: send request success\n", pthread_self());
    return 0;
}
int NetClient::close() {
    if (-1 != m_fd) {
        ::close(m_fd);
    }
    m_fd = -1;
    return 0;
}
