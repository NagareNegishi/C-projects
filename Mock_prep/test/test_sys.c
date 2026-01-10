/**
 * Attempt to test sys_io function in sys.c using Unity and FFF
 * Apparently the version of FFF which ceedling uses as plugin does not support
 * FAKE_VALUE_FUNC_VARARG
 * there is several mismatches between official documentation and the actual implementation
 * - FAKE_VALUE_FUNC_VARARG does not exist -> only FAKE_VALUE_FUNC?_VARARG exists, where ? is number of fixed arguments
 * - when using FAKE_VALUE_FUNC?_VARARG, the custom fake function must take va_list as last argument, not ...
 * - However, return type of custom fake function does not include va_list, only fixed arguments
 *
 * So unless we modify FFF plugin itself, we cannot test ioctl with FFF properly.
 * 1. ioctl requires FAKE_VALUE_FUNC_VARARG, it's not going to work with FAKE_VALUE_FUNC as there is variable arguments
 * 2. FAKE_VALUE_FUNC?_VARARG requires custom fake to take va_list
 */


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
FAKE_VALUE_FUNC(int, close, int);
FAKE_VALUE_FUNC3_VARARG(int, ioctl, int, unsigned long, ...);


#include <stdarg.h> // need to handle ...
// custom fake which always populates ifreq structure with valid data
// static int ioctl_fake_impl(int fd, unsigned long request, ...) {
//     if (request == SIOCGIFADDR){ // match this with src
//         printf("SIOCGIFADDR matched!\n");

//         va_list args; // handle variable arguments
//         va_start(args, request); // request is last fixed argument

//         // function pass &ifr as 3rd argument -> since ifr is struct, it is passed as pointer
//         struct ifreq* ifr = va_arg(args, struct ifreq*);
//         printf("ifr pointer: %p\n", (void*)ifr);

//         if (ifr == NULL) {
//             printf("ioctl_fake_impl: ifr is NULL\n");
//             va_end(args);
//             return -1; // error
//         }

//         // we want ifr to always have valid IP address
//         struct sockaddr_in* ipaddr = (struct sockaddr_in*)&ifr->ifr_addr; // ifr_addr is sockaddr type, so need to cast
//         ipaddr->sin_family = AF_INET;
//         ipaddr->sin_addr.s_addr = inet_addr("127.0.0.1"); // assign some valid IP address (localhost in this case)
        
//         // clean up
//         va_end(args);
//     }
//     return 0;
// }


static int ioctl_fake_impl(int fd, unsigned long request, va_list args) {
    if (request == SIOCGIFADDR) {
        struct ifreq* ifr = va_arg(args, struct ifreq*);
        
        struct sockaddr_in* ipaddr = (struct sockaddr_in*)&ifr->ifr_addr;
        ipaddr->sin_family = AF_INET;
        ipaddr->sin_addr.s_addr = inet_addr("127.0.0.1");
    }
    return 0;
}


void setUp(void) {
    // This is run before EACH TEST
    // Reset all fakes before each test to ensure clean state
    RESET_FAKE(socket);
    RESET_FAKE(ioctl);
    FFF_RESET_HISTORY();
}
void tearDown(void) {
    // This is run after EACH TEST
}

#include <stdbool.h>

TEST_CASE(1, true)
// TEST_CASE(0, true) // 0 is valid socket fd
TEST_CASE(-1, false)
void test_sys_io(int socket_return, bool expected) {
    socket_fake.return_val = socket_return; // mock socket to return valid fd
    close_fake.return_val = 0; // close should succeed
    ioctl_fake.custom_fake = ioctl_fake_impl; // use custom fake implementation

    bool result = sys_io();
    TEST_ASSERT_EQUAL(expected, result);
}