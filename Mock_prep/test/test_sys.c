#include "unity.h"
#include "sys.h"

#include <sys/ioctl.h>    // General ioctl stuff
#include <net/if.h>        // Network interface commands (SIOCGIFADDR, etc.)
#include <linux/fs.h>      // Filesystem commands
#include <termios.h>       // Terminal commands

void setUp(void) {
    // This is run before EACH TEST
}
void tearDown(void) {
    // This is run after EACH TEST
}

void test_sys_io(void) {
    int result = sys_io();
    TEST_ASSERT_EQUAL(0, result);
}