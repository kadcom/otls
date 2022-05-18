#ifndef OTLS_TLS_DEBUG_H 
#define OTLS_TLS_DEBUG_H 

#include "mbedtls/x509.h"

extern void my_debug(void *ctx, int level, const char *file, int line, const char *str);
extern int my_verify(void *data, mbedtls_x509_crt *crt, int depth, uint32_t *flags);


#endif /* OTLS_TLS_DEBUG_H */
