#include "csocket.h"
#include "result.h"
#include "tools.h"
#include <sys/types.h>
#include <pthread.h>
#include "clientSocket.h"
char ip[32];
int main(void){
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
      puts("建立连接成功!");
    }

    char buffer[1024];
    memset(buffer,0,sizeof(buffer));

    do{
			printf("call: ");
      fgets(buffer, sizeof(buffer),stdin);
			if (strcmp(buffer, "q\n") == 0) {
				shutdown(sock_fd,0);
				puts("与服务器断开连接...\n");
				break;
			}
			send(sock_fd,buffer, sizeof(buffer),0);
    }while(1);
		close(sock_fd);
    return 0;
}
