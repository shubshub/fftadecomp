#include "ffta.h"

/* 0x0809AB7C..0x0809ABB0: 52 bytes / 25 instructions. */
typedef struct {
    void *value;
} ValueObject;

typedef struct {
    u8 unknown_00[8];
    s16 x;
    u8 unknown_0A[2];
    s16 z;
} PositionedObject;

typedef struct {
    u8 unknown_00[4];
    s8 x;
    s8 z;
    u8 unknown_06[2];
    PositionedObject *match;
} SearchContext;

extern void *func_080C7B74(const ValueObject *object);

s32 func_0809AB7C(const ValueObject *object, SearchContext *context)
{
    PositionedObject *value = func_080C7B74(object);

    if (context->x == (value->x >> 5) &&
        context->z == (value->z >> 5)) {
        context->match = value;
        return 0;
    }
    return 1;
}
