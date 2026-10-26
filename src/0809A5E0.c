#include "ffta.h"

typedef s32 (*ObjectCallback)(void *object, void *context);

typedef struct {
    u8 unknown_00[0x1c];
    void *object;
} ObjectOwner;

extern s32 func_08097814(void *object, void *context);
extern void func_08148860(void *object, s32 priority,
                          ObjectCallback callback, void *context);
extern void func_08148914(u8 value);

/* 0x0809A5E0..0x0809A604: 36 bytes. */
void func_0809A5E0(const ObjectOwner *owner, u8 value, void *context)
{
    func_08148860(owner->object, 0xff, func_08097814, context);
    func_08148914(value);
}
