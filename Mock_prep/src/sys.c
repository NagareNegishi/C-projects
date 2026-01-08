#include "sys.h"
#include <stdio.h>
#include <sys/ioctl.h>    // General ioctl stuff
#include <net/if.h>        // Network interface commands (SIOCGIFADDR, etc.)
#include <linux/fs.h>      // Filesystem commands
#include <termios.h>       // Terminal commands

int sys_io() {
    // Placeholder implementation
    printf("sys_io function called.\n");

    // prepare to use ifreq structure and socket
    struct ifreq ifr;
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return -1;
    }


    return 0;
}