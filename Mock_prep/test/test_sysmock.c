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

// CMock generated mock header
#include "mock_system_wrapper.h"