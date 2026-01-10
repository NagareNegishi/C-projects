/**
 * TEST va_arg usage - Find exact crash point
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

// Test 1: Just call va_arg, don't use result
static int ioctl_fake_test1(int fd, ioctl_request_t request, va_list args) {
    printf("TEST1: Entered custom_fake\n");
    fflush(stdout);
    
    printf("TEST1: About to call va_arg\n");
    fflush(stdout);
    
    struct ifreq* ifr = va_arg(args, struct ifreq*);
    
    printf("TEST1: va_arg returned: %p\n", (void*)ifr);
    fflush(stdout);
    
    // Don't touch ifr - just return
    return 0;
}

// Test 2: Check if pointer is valid
static int ioctl_fake_test2(int fd, ioctl_request_t request, va_list args) {
    printf("TEST2: Extracting pointer\n");
    fflush(stdout);
    
    struct ifreq* ifr = va_arg(args, struct ifreq*);
    printf("TEST2: Got pointer: %p\n", (void*)ifr);
    fflush(stdout);
    
    if (ifr == NULL) {
        printf("TEST2: Pointer is NULL!\n");
        fflush(stdout);
        return -1;
    }
    
    printf("TEST2: Pointer is valid, checking ifr_name\n");
    fflush(stdout);
    
    printf("TEST2: ifr_name = '%s'\n", ifr->ifr_name);
    fflush(stdout);
    
    return 0;
}

// Test 3: Actually modify the structure
static int ioctl_fake_test3(int fd, ioctl_request_t request, va_list args) {
    printf("TEST3: Extracting pointer\n");
    fflush(stdout);
    
    struct ifreq* ifr = va_arg(args, struct ifreq*);
    printf("TEST3: Got pointer: %p\n", (void*)ifr);
    fflush(stdout);
    
    if (ifr == NULL) {
        printf("TEST3: Pointer is NULL!\n");
        fflush(stdout);
        return -1;
    }
    
    printf("TEST3: About to modify ifr_addr\n");
    fflush(stdout);
    
    struct sockaddr_in* ipaddr = (struct sockaddr_in*)&ifr->ifr_addr;
    
    printf("TEST3: Setting sin_family\n");
    fflush(stdout);
    ipaddr->sin_family = AF_INET;
    
    printf("TEST3: Setting sin_addr\n");
    fflush(stdout);
    ipaddr->sin_addr.s_addr = inet_addr("127.0.0.1");
    
    printf("TEST3: Done modifying structure\n");
    fflush(stdout);
    
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

void test_va_arg_only(void) {
    printf("\n=== Test 1: va_arg only ===\n");
    fflush(stdout);
    
    socket_fake.return_val = 1;
    close_fake.return_val = 0;
    ioctl_fake.custom_fake = ioctl_fake_test1;
    
    bool result = sys_io();
    printf("Result: %d\n", result);
    fflush(stdout);
}

void test_check_pointer_validity(void) {
    printf("\n=== Test 2: Check pointer validity ===\n");
    fflush(stdout);
    
    socket_fake.return_val = 1;
    close_fake.return_val = 0;
    ioctl_fake.custom_fake = ioctl_fake_test2;
    
    bool result = sys_io();
    printf("Result: %d\n", result);
    fflush(stdout);
}

void test_modify_structure(void) {
    printf("\n=== Test 3: Modify structure ===\n");
    fflush(stdout);
    
    socket_fake.return_val = 1;
    close_fake.return_val = 0;
    ioctl_fake.custom_fake = ioctl_fake_test3;
    
    bool result = sys_io();
    printf("Result: %d (expected: 1)\n", result);
    fflush(stdout);
    
    TEST_ASSERT_EQUAL(true, result);
}