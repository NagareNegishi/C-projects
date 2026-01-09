#include "unity.h"
#include "sys.h"

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


#include "fff.h"
// DEFINE_FFF_GLOBALS; // fff plugin is used

// Declare fakes for the functions we need to control
FAKE_VALUE_FUNC(int, socket, int, int, int);
FAKE_VALUE_FUNC3_VARARG(int, ioctl, int, unsigned long, ...);


#include <stdarg.h> // need to mandle ...
// custom fake which always populates ifreq structure with valid data
static int ioctl_fake_impl(int fd, unsigned long request, ...) {
    if (request == SIOCGIFADDR){ // match this with src
        printf("SIOCGIFADDR matched!\n");

        va_list args; // handle variable arguments
        va_start(args, request); // request is last fixed argument

        // function pass &ifr as 3rd argument -> since ifr is struct, it is passed as pointer
        struct ifreq* ifr = va_arg(args, struct ifreq*);
        printf("ifr pointer: %p\n", (void*)ifr);

        if (ifr == NULL) {
            printf("ioctl_fake_impl: ifr is NULL\n");
            va_end(args);
            return -1; // error
        }

        // we want ifr to always have valid IP address
        struct sockaddr_in* ipaddr = (struct sockaddr_in*)&ifr->ifr_addr; // ifr_addr is sockaddr type, so need to cast
        ipaddr->sin_family = AF_INET;
        ipaddr->sin_addr.s_addr = inet_addr("127.0.0.1"); // assign some valid IP address (localhost in this case)
        
        // clean up
        va_end(args);
    }
    return 0;
}

void setUp(void) {
    // This is run before EACH TEST
}
void tearDown(void) {
    // This is run after EACH TEST
}

#include <stdbool.h>

// TEST_CASE(1, true)
TEST_CASE(0, true) // 0 is valid socket fd
TEST_CASE(-1, false)
void test_sys_io(int socket_return, bool expected) {
    socket_fake.return_val = socket_return; // mock socket to return valid fd
    ioctl_fake.custom_fake = ioctl_fake_impl; // use custom fake implementation

    bool result = sys_io();
    TEST_ASSERT_EQUAL(expected, result);
}