#include "csocket.h"
Socket init(short domain,int type,int protocol,char* addr,int port){
    Socket sock = {
            sock.domain = domain,
            sock.type = type,
            sock.protocol = protocol,
						sock.addr = addr,
            sock.port = port,
						sock.sock_fd = socket(domain,type,protocol),
						sock.addr_in = *get_addr(domain,addr,port),
    };
    return sock;
}
int sock_check(int sock_fd,int bind_rs){
    if (sock_fd == -1){
        perror("socket failed!");
        return -1;
    }
    if (bind_rs < 0) {
        perror("socket bind failed!");
        return -1;
    }
    return 1;
}
void set_sockaddr(struct sockaddr_in* addr_in,Socket* sock){
	addr_in->sin_family = sock->domain;
	addr_in->sin_addr.s_addr = inet_addr(sock->addr);
	addr_in->sin_port = htons(sock->port);
}
struct sockaddr_in* get_addr(short domain,char* addr,int port){
    struct sockaddr_in* addr_in = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
    addr_in->sin_family = domain;
    addr_in->sin_addr.s_addr = inet_addr(addr);
    addr_in->sin_port = htons(port);
    return addr_in;
}
char* get_sock_ip(struct sockaddr_in* addr_in){
	struct in_addr address; 
	int addro = addr_in->sin_addr.s_addr;
	memcpy(&address,&addro,4);
	return inet_ntoa(address);
}
