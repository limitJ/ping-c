#ifndef _ICMP_H_
#define _ICMP_H_ 1
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#define ICMP_HEAD_LEN 8
#define ICMP_DATA_LEN 56
#define ICMP_LEN 64
#define TTL 64
typedef struct Icmp{
	uint8_t type;
	uint8_t code;
	uint16_t cksum;
	uint32_t other;

	char src_ip[15];
	char dest_ip[15];
	uint16_t ttl;
	uint64_t start_time;
	uint64_t end_time;
	char data[8];
}Icmp;
void set_pkg(Icmp* icmp);
#endif
