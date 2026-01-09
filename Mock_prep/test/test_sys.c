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

    }
    return 0;
}

void setUp(void) {
    // This is run before EACH TEST
}
void tearDown(void) {
    // This is run after EACH TEST
}

void test_sys_io(void) {
    socket_fake.return_val = 3; // mock socket to return valid fd
    ioctl_fake.custom_fake = ioctl_fake_impl; // use custom fake implementation

    bool result = sys_io();
    TEST_ASSERT_EQUAL(true, result);
}