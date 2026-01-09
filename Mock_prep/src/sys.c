#include "sys.h"
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
    
    (void)ioctl(sock, SIOCGIFADDR, &ifr);
    ipaddr = (struct sockaddr_in*)&ifr.ifr_addr;
    if (ipaddr->sin_addr.s_addr == 0 || ifr.ifr_addr.sa_family != AF_INET) {
        perror("Invalid IP address"); // replace with logging
        close(sock);
        return false;
    }

    close(sock);
    return true;
}




// bool sys_io() {
//     // Placeholder implementation
//     printf("sys_io function called.\n");

//     // prepare to use ifreq structure and socket
//     struct ifreq ifr;
//     int sock = socket(AF_INET, SOCK_DGRAM, 0);
//     if (sock < 0) {
//         perror("Socket creation failed");
//         return -1;
//     }
//     // Example ioctl call (not functional, just illustrative)
//     strcpy(ifr.ifr_name, "eth0");
//     if (ioctl(sock, SIOCGIFADDR, &ifr) < 0) {
//         perror("ioctl SIOCGIFADDR failed");
//         close(sock);
//         return -1;
//     }

//     // if we reach here, everything is fine, print for now
//     printf("ioctl SIOCGIFADDR succeeded.\n");
//     struct sockaddr_in* ipaddr = (struct sockaddr_in*)&ifr.ifr_addr;
//     printf("IP Address: %s\n", inet_ntoa(ipaddr->sin_addr));
//     close(sock);


//     return 0;
// }