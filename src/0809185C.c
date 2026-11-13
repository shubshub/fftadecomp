#include "control_flags.h"

typedef void (*BufferInitializer)(void *, u32);
typedef void (*BufferCopier)(void *, const void *, u32);

typedef struct {
    u32 mode;
    u8 unknown_004[0x478];
    u16 display;
    u8 blend_control_low;
    u8 blend_control_high;
    u8 first_weight;
    u8 second_weight;
    u8 unknown_482[0x252];
} DisplayObject0809185C;

extern BufferInitializer const g_callbacks_0836D4B8[];
extern BufferCopier data_0836D4BC[];
extern u8 data_03003860[];

extern void *func_08022840(u32 size);
extern void func_0814224C(void *destination, u32 size,
                          BufferInitializer callback);
extern void func_08142250(void *destination, const void *source, u32 size,
                          BufferCopier callback);
extern void func_08090A80(void *state);
extern void func_08090BBC(void *state);
extern void func_08090CF8(void *state);
extern void func_08090E34(void *state);

// Complete [0x0809185C, 0x08091930): 212 bytes, including the literal pool.
DisplayObject0809185C *func_0809185C(u8 flags)
{
    DisplayObject0809185C *object = func_08022840(sizeof(DisplayObject0809185C));
    BufferCopier *copy;

    func_0814224C(object, sizeof(DisplayObject0809185C), g_callbacks_0836D4B8[0]);
    object->display = g_control_flags_03000940.display;
    object->blend_control_low = g_control_flags_03000940.bldcnt_lo;
    object->blend_control_high = g_control_flags_03000940.bldcnt_hi;
    object->first_weight = g_control_flags_03000940.bldalpha_lo;
    object->second_weight = g_control_flags_03000940.bldalpha_hi;
    g_control_flags_03000940.bg2hofs = 0;
    g_control_flags_03000940.bg2vofs = 0;
    object->mode = flags & ~0x80;
    if (object->mode == 0) {
        if (flags & 0x80)
            func_08090E34(&object->unknown_004);
        else
            func_08090CF8(&object->unknown_004);
    } else if (flags & 0x80)
        func_08090BBC(&object->unknown_004);
    else
        func_08090A80(&object->unknown_004);
    // The copier is read from the callback table right before the copy, as in 0813F604.
    copy = data_0836D4BC;
    func_08142250(&object->unknown_482, data_03003860, 0x200, copy[0]);
    return object;
}
