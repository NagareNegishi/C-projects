/**
 * system_wrapper.h
 * Wrapper header for system calls to facilitate mocking in tests.
 */
#ifndef SYSTEM_WRAPPER_H
#define SYSTEM_WRAPPER_H
int socket(int domain, int type, int protocol);
int close(int fd);
int ioctl(int fd, unsigned long request, ...);
#endif

