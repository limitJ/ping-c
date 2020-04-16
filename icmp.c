#include "icmp.h"
#include <sys/time.h>
void set_pkg(Icmp* icmp){
	icmp->type = 8;
	icmp->code = 0;
	icmp->cksum = 0;
	struct timeval tv;
	gettimeofday(&tv,NULL);
	icmp->ttl = TTL;
	icmp->start_time = tv.tv_usec;
}
