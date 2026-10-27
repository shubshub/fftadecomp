#include "ffta.h"

/* 0x0809ABB0..0x0809ABE6: 54 bytes / 26 instructions. */
typedef struct {
    void *value;
} ValueObject;

typedef struct {
    u8 unknown_00[0xF6];
    u8 x;
    u8 z;
} PositionRecord;

typedef struct {
    PositionRecord *position;
} PositionedObject;

typedef struct {
    u8 unknown_00[4];
    s8 x;
    s8 z;
    u8 unknown_06[2];
    PositionedObject *match;
} SearchContext;

extern void *func_080C7B74(const ValueObject *object);

s32 func_0809ABB0(const ValueObject *object, SearchContext *context)
{
    PositionedObject *value = func_080C7B74(object);

    if (context->x == value->position->x &&
        context->z == value->position->z) {
        context->match = value;
        return 0;
    }
    return 1;
}
