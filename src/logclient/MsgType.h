#ifndef _LOG_MSG_TYPE_
#define _LOG_MSG_TYPE_

enum CMD_TYPE {
    CMD_REQUEST = 1,
    CMD_RESPONCE,
    CMD_DATA,
    CMD_FINISH,
    CMD_MAX,
};

typedef struct msg_head_st {
    CMD_TYPE cmd;
    int datalen;
    char data[0];
    msg_head_st() : cmd(CMD_MAX), datalen(0){ }
} *msg_head_t;

#endif
