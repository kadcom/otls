#ifndef OTLS_PLATFORM_H
#define OTLS_PLATFORM_H 1 

// Handle WATCOM's 
#if defined(__NT__) && !defined(WIN32)
#define WIN32 1
#endif

#if defined (WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#elif defined(__linux__) || defined (__unix__) || defined (__APPLE__) 
#define closesocket close 
#define SOCKET int
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#else 
#error "Unsupported platform"
#endif

static inline int init_socket() {
#ifdef WIN32
  WSADATA wsa;
  return WSAStartup(MAKEWORD(2, 0), &wsa);
#else 
  return 0;
#endif
}

static inline int cleanup_socket() {
#ifdef WIN32
  WSADATA wsa;
  return WSAStartup(MAKEWORD(2, 0), &wsa);
#else 
  return 0;
#endif

}

static inline int get_last_socket_error() {
#ifdef WIN32
  return WSAGetLastError(); 
#else
  return errno;
#endif
}


#endif
