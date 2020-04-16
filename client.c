#include "csocket.h"
#include "result.h"
#include "tools.h"
#include <sys/epoll.h>
#include <sys/types.h>
#include <pthread.h>
#include "clientSocket.h"
#define MAX_EVENTS 256
char ip[32];
int main(void){
    char buffer[1024];
    memset(buffer,0,sizeof(buffer));
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
			//recv(sock_fd, buffer, sizeof(buffer), 0);
      //printf("分配到ip:%s\n", buffer);
			puts("建立连接成功");
		}
		int epfd = epoll_create(MAX_EVENTS);
		ev.events = EPOLLIN | EPOLLET;
		ev.data.fd = sock_fd;
		epoll_ctl(epfd, EPOLL_CTL_ADD, sock_fd,&ev);
		while(1){
			int fds = epoll_wait(epfd, events, 256, 500);
			printf("%d\n",fds);
			sleep(1);
			for (int i = 0; i < fds; ++i) {
					if (events[i].events & EPOLLIN) {
						recv(sock_fd, buffer, sizeof(buffer), 1024);
						puts(buffer);
						ev.events = EPOLLOUT | EPOLLET;
						epoll_ctl(epfd, EPOLL_CTL_MOD, sock_fd, &ev);
					}else if(events[i].events & EPOLLOUT){
						send(epfd, buffer, sizeof(buffer), 0);
						ev.events = EPOLLIN | EPOLLET;
						epoll_ctl(epfd, EPOLL_CTL_MOD, sock_fd, &ev);
					}
			}
		}
		close(sock_fd);
    return 0;
}
