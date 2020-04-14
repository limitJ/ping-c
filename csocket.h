//
// Created by 58252 on 2020/3/31.
//

#ifndef _CSOCKET_H_
#define _CSOCKET_H_ 1
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
typedef struct __Socket{
    short domain;
    int type;
    int protocol;
    char* addr;
    int port;
	int sock_fd;
	struct sockaddr_in addr_in;
}Socket;
extern Socket init(short domain,int type,int protocol,char* addr,int port);
extern int sock_check(int sock_fd,int bind_rs);
extern void set_sockaddr(struct sockaddr_in* addr_in,Socket* sock);
extern struct sockaddr_in* get_addr(short domain,char* addr,int port);
extern char* get_sock_ip(struct sockaddr_in* addr_in);
#endif
