#include "icmp.h"
#include <sys/time.h>
void set_pkg(Icmp* icmp,char* src_ip,char* dest_ip)
{
	icmp->type = 8;
	icmp->code = 0;
	icmp->cksum = 0;
	struct timeval tv;
	gettimeofday(&tv,NULL);
	icmp->ttl = TTL;
	icmp->start_time = tv.tv_usec;
	strcpy(icmp->src_ip, src_ip);
	strcpy(icmp->dest_ip, dest_ip);
}
