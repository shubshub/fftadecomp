#include "ffta.h"

/* Target: complete [0x0812E4A8, 0x0812E4F2), 74 bytes, 32 instructions. */
extern u8 func_0812E470(const void *);
extern u8 func_080CD92C(const void *);
extern u8 func_080CDADC(const void *);
extern u8 func_080CDB24(const void *);
extern u8 func_080CDA04(const void *);

u8 func_0812E4A8(const void *object)
{
    if (func_0812E470(object) && !func_080CD92C(object) &&
        !func_080CDADC(object) && !func_080CDB24(object) &&
        !func_080CDA04(object))
        return 1;
    return 0;
}
