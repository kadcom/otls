#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "config.h"
#include "platform.h"

int main(int argc, char **argv) {
  // Winsock data 
  struct hostent *entry;
  struct in_addr **addr_list, **addr_iter, addr_item;
  struct sockaddr_in addr;
  static const char httpbin[] = "httpbin.org";
  static const short port = 80;
  static const char request [] = 
    "GET /get HTTP/1.1\r\n" /* Request Line */
    "Host: httpbin.org\r\n"
    "Connection: close\r\n"
    "User-Agent: Retrocoder/1.0\r\n"
    "Accept: application/json\r\n"
    "Content-Length: 0\r\n"
    "\r\n";
  SOCKET client = INVALID_SOCKET;
  size_t i = 0;
  int res; 
  uint8_t buf[MTU];
  char response[BUF_MAX_SIZE]; // 4K buffer

  printf("Starting Up...\n");

  // Result
  res = init_socket();   
  // host entries (this is allocated by gethostbyname) 
  entry = gethostbyname(httpbin);
  
  if ( entry == NULL ) {
    res = get_last_socket_error();
    goto error;
  }

  printf("Address resolved for %s\n", httpbin);

  addr_list = (struct in_addr **) entry->h_addr_list; // (1)
  addr_iter = addr_list; // (2) 
  
  i = 0;
  while (*addr_iter != NULL) { 
    memcpy(&addr_item, *addr_iter, entry->h_length); // (3)
    printf("%s\n", inet_ntoa(addr_item)); // (4) 
    ++addr_iter;  // (5)
    ++i;
  }

  printf("%zu addresses resolved.\n\n", i);

  memset(&addr, 0, sizeof(struct sockaddr_in));

  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);

  memcpy(&addr.sin_addr, addr_list[0], entry->h_length);

  client = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  
  if (INVALID_SOCKET == client) {
    goto error;
  }
 
  printf("Socket opened 0x%X\n", client);

  res = connect(client, (struct sockaddr *) &addr, sizeof(struct sockaddr_in));
  
  if (SOCKET_ERROR == res) {
    goto error;
  }

  printf("Connected to %s (%s)\n", inet_ntoa(addr.sin_addr), httpbin);
  
  res = send(client, request, sizeof(request) - 1, 0);
  
  if ( SOCKET_ERROR == res ) {
    goto error;
  }

  i = 0;
  do {
    res = recv(client, (char *) buf, MTU, 0);
    
    if ( SOCKET_ERROR == res || i + res > BUF_MAX_SIZE ) {
      break;
    }

    memcpy(response + i, buf, res);

    i += res;
  } while (res != 0); 

  if (res != 0) {
    goto error;
  }
  
  printf("Response:\n\n");
  
  fwrite(response, sizeof(char), i, stdout);

  res = closesocket(client); 

  if ( SOCKET_ERROR == res ) {
    goto error;
  }

  printf("Socket 0x%X closed\n", client);
  printf("Cleaning Up...\n");
  cleanup_socket();
  return res;

error:
  printf("Get Socket error 0x%X!", res);
  cleanup_socket();

  return res;
}
