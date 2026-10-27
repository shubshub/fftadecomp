#include "ffta.h"

/* Complete [0x08131278, 0x08131290): 24 bytes, 11 instructions. */
typedef struct Object Object;

typedef struct {
    u8 unknown_00;
    u8 kind;
} ActionParameters;

typedef struct {
    const Object *source;
    const Object *target;
    u8 unknown_08[0x28];
    const ActionParameters *parameters;
} ActionRecord;

extern s32 func_0812D2F0(const Object *source, const Object *target, s32 kind);

u8 func_08131278(const ActionRecord *record)
{
    return func_0812D2F0(record->source, record->target, record->parameters->kind);
}
