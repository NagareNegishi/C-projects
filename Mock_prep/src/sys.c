#include "sys.h"
#include <stdio.h>

#include <string.h>
#include <unistd.h>        // for close
#include <sys/ioctl.h>    // General ioctl stuff
#include <net/if.h>        // Network interface commands (SIOCGIFADDR, etc.)
#include <linux/fs.h>      // Filesystem commands
#include <termios.h>       // Terminal commands
// add some logging later

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
    // Example ioctl call (not functional, just illustrative)
    strcpy(ifr.ifr_name, "eth0");
    if (ioctl(sock, SIOCGIFADDR, &ifr) < 0) {
        perror("ioctl SIOCGIFADDR failed");
        close(sock);
        return -1;
    }

    // if we reach here, everything is fine, print for now
    printf("ioctl SIOCGIFADDR succeeded.\n");
    close(sock);


    return 0;
}