all:server client
server:server.c csocket.h csocket.c result.h tools.h tools.c
	gcc -std=c11 -pthread server.c csocket.h csocket.c result.h tools.h tools.c -o server
client:client.c csocket.h csocket.c result.h
	gcc -std=c11 -pthread client.c csocket.h csocket.c result.h tools.h tools.c -o client
test:test.c tools.h tools.c
	gcc -std=c11 -pthread test.c tools.h tools.c -o test
clean:
	rm -rf server client test
