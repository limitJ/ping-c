all:server client
server:server.c csocket.h csocket.c tools.h tools.c
	gcc -std=c11 -pthread $^ -o $@
client:client.c csocket.h csocket.c tools.h tools.c
	gcc -std=c11 -pthread $^ -o $@
test:test.c tools.h tools.c
	gcc -std=c11 -pthread test.c tools.h tools.c -o test
clean:
	rm -rf server client test
