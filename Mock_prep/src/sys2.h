#ifndef SYS2_H
#define SYS2_H
#include <stdbool.h>
#include <netinet/in.h>


/**
 * Function to wrap system calls.
 * use ifreq structure and socket to get some information about network interfaces.
 * use some logging mechanism to log errors.
 */
bool sys_io(void);

bool is_valid_ip(struct sockaddr_in* ipaddr, struct sockaddr* addr);
#endif