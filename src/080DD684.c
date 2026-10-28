#include "ffta.h"

extern u8 func_080A8858(const void *object, u8 selector);

/* 0x080DD684 - 18 bytes.
 * Target: 00b50906090ecbf7e5f80006000e02bc0847
 */
u8 func_080DD684(const void *object, u8 selector)
{
    return func_080A8858(object, selector);
}
