/**
 * MINIMAL DIAGNOSTIC - FFF FAKE ONLY
 * Test different scenarios to identify exact crash point
 */

#include "unity.h"
#include "sys.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include <stdbool.h>

#include "fff.h"

typedef unsigned long ioctl_request_t;

FAKE_VALUE_FUNC(int, socket, int, int, int);
FAKE_VALUE_FUNC(int, close, int);
FAKE_VALUE_FUNC3_VARARG(int, ioctl, int, ioctl_request_t, ...);

static int ioctl_fake_impl(int fd, ioctl_request_t request, va_list args) {
    printf("CUSTOM_FAKE: fd=%d, request=%lu\n", fd, request);
    fflush(stdout);
    
    // Don't touch va_list at all - just return
    return 0;
}

void setUp(void) {
    RESET_FAKE(socket);
    RESET_FAKE(ioctl);
    RESET_FAKE(close);
    FFF_RESET_HISTORY();
}

void tearDown(void) {
}

// Test 1: No custom_fake - just use return_val
void test_without_custom_fake(void) {
    printf("\n=== Test WITHOUT custom_fake ===\n");
    fflush(stdout);
    
    socket_fake.return_val = 1;
    close_fake.return_val = 0;
    ioctl_fake.return_val = 0;  // Just use return value, NO custom_fake
    
    printf("Calling sys_io()...\n");
    fflush(stdout);
    
    bool result = sys_io();
    
    printf("sys_io() returned: %d\n", result);
    fflush(stdout);
    
    // This might fail because IP isn't set, but should NOT crash
    printf("Test completed without crash\n");
    fflush(stdout);
}

// Test 2: Set custom_fake but don't call sys_io
void test_just_set_custom_fake(void) {
    printf("\n=== Test SETTING custom_fake (no call) ===\n");
    fflush(stdout);
    
    socket_fake.return_val = 1;
    close_fake.return_val = 0;
    
    printf("Setting custom_fake...\n");
    fflush(stdout);
    
    ioctl_fake.custom_fake = ioctl_fake_impl;
    
    printf("custom_fake set successfully\n");
    fflush(stdout);
    
    // Don't call sys_io() - just test if setting custom_fake crashes
}

// Test 3: Use custom_fake
void test_with_custom_fake(void) {
    printf("\n=== Test WITH custom_fake ===\n");
    fflush(stdout);
    
    socket_fake.return_val = 1;
    close_fake.return_val = 0;
    ioctl_fake.custom_fake = ioctl_fake_impl;
    
    printf("Calling sys_io()...\n");
    fflush(stdout);
    
    bool result = sys_io();
    
    printf("sys_io() returned: %d\n", result);
    fflush(stdout);
}