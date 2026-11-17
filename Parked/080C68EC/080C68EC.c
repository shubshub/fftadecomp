#include "ffta.h"

// Complete target [0x080C68EC,0x080C69C8): 220 bytes, 110 instructions.
typedef void (*BufferInitializer)(void *destination, u32 size);

typedef struct {
    u8 unknown_00[0x60];
    u32 source;
    u32 slots[5];
    u8 unknown_78;
    u8 slot_count;
    u8 unknown_7A[2];
    u16 current;
    u16 queue_count;
    u16 queue[1];
} Owner080C68EC;

extern BufferInitializer const g_callbacks_0836D4B8[];
extern void func_0814224C(void *destination, u32 size, BufferInitializer callback);
extern s32 func_08099CDC(u32 source, u32 **out);
extern u8 func_08133BC4(void *value);

void func_080C68EC(Owner080C68EC *owner, u32 source)
{
    u32 *found[13];
    s32 count;
    s32 i;
    u32 **cursor;

    func_0814224C(owner, 0xC4, g_callbacks_0836D4B8[0]);
    owner->source = source;
    count = func_08099CDC(source, found);
    for (i = 0; i < count; i++) {
        cursor = &found[i];
        if (func_08133BC4((void *)**cursor)) {
            owner->slots[owner->slot_count] = **cursor;
            owner->slot_count++;
            if (owner->slot_count > 1)
                break;
        }
    }
    owner->current = 0x12;
    owner->queue[owner->queue_count++] = owner->current;
    owner->current = 5;
    owner->queue[owner->queue_count++] = owner->current;
    owner->current = 8;
    owner->queue[owner->queue_count++] = owner->current;
    owner->current = 2;
    owner->queue[owner->queue_count++] = owner->current;
    owner->current = 0;
}
