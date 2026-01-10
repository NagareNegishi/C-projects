/**
 * Same as test_sys.c but with mock_system_wrapper.h
 */

#include "unity.h"
#include "sys.h"

#include <string.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// generated mock header in build/test/mocks
// my current setup use fff, if I comment out fff plugin in ceedling.yml, it uses cmock instead
// FFF is preferred here as I already patched it to support FAKE_VALUE_FUNC3_VARARG
#include "mock_system_wrapper.h"