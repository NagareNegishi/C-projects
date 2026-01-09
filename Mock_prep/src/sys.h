#ifndef SYS_H
#define SYS_H
#include <stdbool.h>
/**
 * Function to wrap system calls.
 * use ifreq structure and socket to get some information about network interfaces.
 * use some logging mechanism to log errors.
 */
bool sys_io(void);
#endif