#include "sys2.h"
#include <stdio.h>

#include <string.h>
#include <unistd.h>        // for close
#include <sys/ioctl.h>    // General ioctl stuff https://linux.die.net/man/7/netdevice
#include <net/if.h>        // Network interface commands (SIOCGIFADDR, etc.)
#include <linux/fs.h>      // Filesystem commands
#include <termios.h>       // Terminal commands

// for in_addr printing https://linux.die.net/man/3/inet_ntoa
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
// add some logging later



bool sys_io(void) {
    struct ifreq ifr;
    int sock;
    struct sockaddr_in* ipaddr;
    
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Socket creation failed"); // replace with logging
        return false;
    }
    
    strcpy(ifr.ifr_name, "eth0");
    

    // the original code had (void) cast here, but it's real problem!
    // because of it, test need to fake ioctl which always succeed
    int ioctl_result = ioctl(sock, SIOCGIFADDR, &ifr);

    if (ioctl_result < 0) {
        perror("ioctl failed"); // replace with logging
        close(sock);
        return false;
    }

    ipaddr = (struct sockaddr_in*)&ifr.ifr_addr;
    if (!is_valid_ip(ipaddr, &ifr.ifr_addr)) {
        perror("Invalid IP address"); // replace with logging
        close(sock);
        return false;
    }

    close(sock);
    return true;
}


bool is_valid_ip(struct sockaddr_in* ipaddr, struct sockaddr* addr) {
    return ipaddr->sin_addr.s_addr != 0 && addr->sa_family == AF_INET;
}