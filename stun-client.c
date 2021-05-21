#include <stun/usages/bind.h>
// stun-client 2021 Mario Gasparoni Junior 
// 
// Freely distributed under the MIT license
// 
// Simple STUN client to retrieve external ip address
//  
#include <stdlib.h>
#include <stdio.h>

// google's stun server:
#define DEFAULT_STUN_SERVER "64.233.186.127"
#define DEFAULT_STUN_PORT 19302

int main (int argc, char ** argv) {

  struct sockaddr_in server_address;
  union {
    struct sockaddr_storage storage;
    struct sockaddr addr;
  } public_ip_address;

  socklen_t public_ip_address_len = sizeof (public_ip_address);

  stun_debug_disable();

  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = inet_addr(DEFAULT_STUN_SERVER);
  server_address.sin_port = htons(DEFAULT_STUN_PORT);

  StunUsageBindReturn ret;

  ret = stun_usage_bind_run ((struct sockaddr*)&server_address,
                     sizeof(struct sockaddr_in),
                     &public_ip_address.storage,
                     &public_ip_address_len);

  if (ret) {
    printf("Error %d\n", ret);
  } else {
    struct sockaddr_in *public_address = (struct sockaddr_in*) &public_ip_address.addr;
    printf("%s\n", inet_ntoa(public_address->sin_addr));
  }
}
