#include "csocket.h"
#include "clientSocket.h"
#include "tools.h"
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/epoll.h>
#define MAX_EVENTS 255
int sendCount = 10;
void* run(void* client);
ClientSocket** ips;
int assignment(int client_fd);
int main(void)
{
	ips = (ClientSocket**)malloc(sizeof(ClientSocket*)*255);
	memset(ips, 0, 255);
	//对socket进行一次封装
	Socket sock = init(AF_INET,SOCK_STREAM,IPPROTO_TCP,"127.0.0.1",8888);
	int sock_fd = sock.sock_fd;
	struct sockaddr_in addr_in = sock.addr_in;
	//绑定套接字
	int bind_rs = bind(sock_fd,(struct sockaddr*)&addr_in,sizeof(addr_in));
	if (!sock_check(sock_fd,bind_rs)){
		return -1;
	}
	//监听套接字
	listen(sock_fd,256);
	puts("Server端正在监听端口...:8888");
	int ep_fd = epoll_create(MAX_EVENTS);
	struct epoll_event ev,events[MAX_EVENTS];
	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = sock_fd;
	epoll_ctl(ep_fd, EPOLL_CTL_ADD, sock_fd, &ev);
	while (1)
	{
		int fds = epoll_wait(ep_fd, events, MAX_EVENTS, 0);
		for (int i = 0; i <fds; ++i)
		{
			if (events[i].data.fd == sock_fd)
			{
				int client_fd = accept(sock_fd, NULL,NULL);
				int ip_no = assignment(client_fd);
				if (ip_no == -1) {
					break;
				}
				ev.events = EPOLLIN | EPOLLOUT | EPOLLET;
				ev.data.fd = client_fd;
				epoll_ctl(ep_fd, EPOLL_CTL_ADD, client_fd, &ev);
			}
			else
			{
				if(events[i].events & EPOLLIN)
				{
					char buffer[1024];
					memset(buffer, 0, sizeof(buffer));
					int status = recv(events[i].data.fd, buffer,sizeof(buffer), 0);
					puts(buffer);
					if(status == 0)
					{
						for (int j = 2; j < 255; ++j) {
							if(ips[j]!=NULL && events[i].data.fd == ips[j]->client_fd){
								printf("与客户端:%s断开连接\n",ips[j]->ip);
								free(ips[j]);
								ips[j] = NULL;
								epoll_ctl(ep_fd, EPOLL_CTL_DEL, events[i].data.fd, &ev);
							}
						}
					}
					else
					{
						fputs(buffer, stdout);
						ev.events = EPOLLOUT | EPOLLET;
						ev.data.fd = events[i].data.fd;
						epoll_ctl(ep_fd, EPOLL_CTL_MOD, events[i].data.fd, &ev);
					}
				}
				if (events[i].events & EPOLLOUT){
					send(events[i].data.fd, "out", 32, 0);
					ev.events = EPOLLIN | EPOLLET;
					ev.data.fd = events[i].data.fd;
					epoll_ctl(ep_fd, EPOLL_CTL_MOD, events[i].data.fd, &ev);
				}
      }
    }
  }
	close(sock_fd);
	return 0;
}
int assignment(int client_fd)
{
	for(int i = 2;i<255;i++)
	{
		if(ips[i]==NULL)
		{
			ips[i] = (ClientSocket*)malloc(sizeof(ClientSocket));
			ips[i]->client_fd = client_fd;
			memset(ips[i]->ip,0,sizeof(ips[i]->ip));
			strcat(ips[i]->ip,"192.168.2.");
			strcat(ips[i]->ip, itc(i));
			printf("接入客户端:%s\n",ips[i]->ip);
			send(client_fd, ips[i]->ip, 32, 0);
			return i;
		}
	}
	fputs("没有ip可分配ip\n", stdout);
	send(client_fd, "没有可分配ip", 32, 0);
	return -1;
}
