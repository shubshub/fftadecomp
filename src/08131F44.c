#include "ffta.h"

typedef struct {
    u8 unknown_00[0x104];
    u8 value;
} NestedState;

typedef struct {
    void *target;
    u8 unknown_04[4];
    NestedState *nested;
    u8 unknown_0C[0x1A];
    u16 flags;
} FlaggedState;

void func_080CE1B0(void *object, u8 enabled);
void func_080CE488(void *object, u8 value);

void func_08131F44(FlaggedState *object)
{
    if ((object->flags & 0x10) == 0) {
        func_080CE1B0(object->target, 1);
        func_080CE488(object->target, object->nested->value);
    }
}
