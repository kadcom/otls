#ifndef OTLS_PLATFORM_H
#define OTLS_PLATFORM_H 1 

#if defined (WIN32) || defined (__WIN32) || defined (__NT__)
#define PLATFORM_WINDOWS 1
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#elif defined(__linux__) || defined (__unix__) || defined (__APPLE__) oeuaoeuoaeu;
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
#ifdef PLATFORM_WINDOWS
  WSADATA wsa;
  return WSAStartup(MAKEWORD(2, 0), &wsa);
#else 
  return 0;
#endif
}

static inline int cleanup_socket() {
#ifdef PLATFORM_WINDOWS
  WSADATA wsa;
  return WSAStartup(MAKEWORD(2, 0), &wsa);
#else 
  return 0;
#endif

}

static inline int get_last_socket_error() {
#ifdef PLATFORM_WINDOWS
  return WSAGetLastError(); 
#else
  return errno;
#endif
}


#endif
