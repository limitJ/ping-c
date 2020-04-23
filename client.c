#include "csocket.h"
#include "tools.h"
#include "icmp.h"
#include <sys/epoll.h>
#include <sys/time.h>
#include <sys/types.h>
#include <pthread.h>
#include "clientSocket.h"
#define MAX_EVENTS 256
char ip[15];
void* run(void* arg);
int main(void){
    char dest_ip[15];
		memset(ip, 0, sizeof(ip));
    memset(dest_ip,0,sizeof(dest_ip));
		struct epoll_event ev,events[MAX_EVENTS];
		printf("pid = %d\n",getpid());
    Socket sock = init(AF_INET,SOCK_STREAM,IPPROTO_TCP,"127.0.0.1",8888);
    int sock_fd = sock.sock_fd;
    struct sockaddr_in addr_in = sock.addr_in;
		printf("sock_fd = %d",sock_fd);
    puts("正在与服务端建立连接...\n");
    if(connect(sock_fd,(struct sockaddr*)&addr_in,sizeof(addr_in)) == -1){
        perror("建立连接失败!\n");
        return -1;
    }else{
			recv(sock_fd, ip, sizeof(ip), 0);
      printf("分配到ip:%s\n", ip);
			puts("建立连接成功");
		}
		int epfd = epoll_create(MAX_EVENTS);
		ev.events = EPOLLIN | EPOLLOUT | EPOLLET;
		ev.data.fd = sock_fd;
		epoll_ctl(epfd, EPOLL_CTL_ADD, sock_fd,&ev);
		fputs("ping ", stdout);
		fgets(dest_ip, sizeof(dest_ip), stdin);
		*strchr(dest_ip, '\n') = '\0';
		Icmp* icmp = (Icmp*)malloc(sizeof(Icmp));
		set_pkg(icmp,ip,dest_ip);
		Icmp icmp_result;
		while(1){
			int fds = epoll_wait(epfd, events, 256, 500);
			for (int i = 0; i < fds; ++i) {
					if (events[i].events & EPOLLIN) {
						recv(sock_fd, &icmp, sizeof(icmp_result), 1024);
						ev.events = EPOLLOUT | EPOLLET;
						ev.data.fd = events[i].data.fd;
						epoll_ctl(epfd, EPOLL_CTL_MOD, sock_fd, &ev);
					}
					if(events[i].events & EPOLLOUT){
						memset(buffer, 0, sizeof(buffer));
						if (strcmp(buffer, "q") == 0) {
							shutdown(sock_fd, 0);
							fputs("EIXT\n", stdout);
							epoll_ctl(epfd, EPOLL_CTL_DEL, sock_fd, &ev);
							close(sock_fd);
							exit(EXIT_SUCCESS);
						}else{
							send(sock_fd, buffer, sizeof(buffer), 0);
							ev.events = EPOLLIN | EPOLLET;
							ev.data.fd = events[i].data.fd;
							epoll_ctl(epfd, EPOLL_CTL_MOD, sock_fd, &ev);
						}
					}
			}
		}
		close(sock_fd);
    return 0;
}
