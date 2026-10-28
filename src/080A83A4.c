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

/* 0x080A83A4..0x080A83DC: 56 bytes, including the literal pool. */
u32 func_080A83A4(const WordPair *source, u32 value_08, u32 value_0E,
                    u32 value_0A, u32 value_0C)
{
    if (source != 0)
        data_0200F898.pair = *source;
    data_0200F898.value_0A = value_0A;
    data_0200F898.value_0C = value_0C;
    if (value_08 != 0)
        data_0200F898.value_08 = value_08;
    if (value_0E != 0)
        data_0200F898.value_0E = value_0E;
    return func_0809FDC0(&data_0200F898);
}
