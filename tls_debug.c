#include <stdio.h>
#include "mbedtls/platform.h"
#include "mbedtls/x509.h"
#include "mbedtls/ssl.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/debug.h"

#include "tls_debug.h"


/**
 * Debug callback for mbed TLS
 * Just prints on the USB serial port
 */
void my_debug(void *ctx, int level, const char *file, int line,
    const char *str)
{
  const char *p, *basename;
  (void) ctx;

  /* Extract basename from file */
  for(p = basename = file; *p != '\0'; p++) {
    if(*p == '/' || *p == '\\') {
      basename = p + 1;
    }
  }

  printf("%s:%04d: |%d| %s", basename, line, level, str);
}

/**
 * Certificate verification callback for mbed TLS
 * Here we only use it to display information on each cert in the chain
 */
int my_verify(void *data, mbedtls_x509_crt *crt, int depth, uint32_t *flags)
{
  char buf[1024];
  (void) data;

  mbedtls_printf("\nVerifying certificate at depth %d:\n", depth);
  mbedtls_x509_crt_info(buf, sizeof (buf) - 1, "  ", crt);
  printf("%s", buf);

  if (*flags == 0)
    mbedtls_printf("No verification issue for this certificate\n");
  else
  {
    mbedtls_x509_crt_verify_info(buf, sizeof (buf), "  ! ", *flags);
    printf("%s\n", buf);
  }

  return 0;
}
