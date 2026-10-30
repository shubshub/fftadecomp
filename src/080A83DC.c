/* Target bytes (16):
 * 00 b5 02 48 f7 f7 ee fc 02 bc 08 47 98 f8 00 02
 */
#include "ffta.h"

typedef struct {
    u32 first;
    u32 second;
} WordPair;

typedef struct {
    WordPair pair;
    u16 value_08;
    u16 value_0A;
    u16 value_0C;
    u16 value_0E;
} RequestState;

extern RequestState data_0200F898;
extern u32 func_0809FDC0(RequestState *state);

u32 func_080A83DC(void)
{
    return func_0809FDC0(&data_0200F898);
}
