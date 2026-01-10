#include "unity.h"
#include "sys2.h"

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

typedef unsigned long ioctl_request_t;
FAKE_VALUE_FUNC3_VARARG(int, ioctl, int, ioctl_request_t, ...);


void setUp(void) {
    // This is run before EACH TEST
    // Reset all fakes before each test to ensure clean state
    RESET_FAKE(socket);
    RESET_FAKE(ioctl);
    RESET_FAKE(close);
    FFF_RESET_HISTORY();
}
void tearDown(void) {
    // This is run after EACH TEST
}

#include <stdbool.h>

TEST_CASE(1, 1, true)
void test_sys_io(int socket_return, int ioctl_return, bool expected) {
    socket_fake.return_val = socket_return; // mock socket to return valid fd
    close_fake.return_val = 0; // close should succeed
    ioctl_fake.return_val = ioctl_return;

    bool result = sys_io();
    printf("sys_io() returned: %d, expected: %d\n", result, expected);
    TEST_ASSERT_EQUAL(expected, result);
}