#include "ffta.h"

typedef struct Object Object;

extern u32 func_080C92F0(Object *object, u32 selector);
extern u8 func_0812C960(Object *object);
extern s32 func_0812D2F0(const Object *source, const Object *target, s32 kind);

/* Target: [0x0812D358, 0x0812D388), 48 bytes, 21 instructions. */
s32 func_0812D358(const Object *source, Object *target, s32 kind)
{
    func_080C92F0(target, 0x16);
    if (func_0812C960(target))
        return 0;
    return func_0812D2F0(source, target, kind);
}
