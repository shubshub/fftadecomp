#include "ffta.h"

typedef struct Context0809966C Context0809966C;
typedef struct FlaggedObject0809966C FlaggedObject0809966C;

typedef struct {
    FlaggedObject0809966C *object;
} Entry0809966C;

typedef void (*BufferInitializer0809966C)(void *destination, u32 size);

extern void *func_08022840(u32 size);
extern void func_08022854(u8 *object);
extern s32 func_08099D34(Context0809966C *context, Entry0809966C **entries);
extern u8 func_080C82B8(const FlaggedObject0809966C *object);
extern BufferInitializer0809966C const g_callbacks_0836D4B8[];

/* Complete [0x0809966C, 0x080996CA): 94 bytes, 39 instructions. */
Entry0809966C *func_0809966C(Context0809966C *context)
{
    Entry0809966C **entries = func_08022840(13 * sizeof(*entries));
    Entry0809966C *selected;
    s32 count;
    s32 index;

    g_callbacks_0836D4B8[0](entries, 13 * sizeof(*entries));
    count = func_08099D34(context, entries);
    selected = entries[0];
    for (index = 0; index < count; index++) {
        if (func_080C82B8(entries[index]->object)) {
            selected = entries[index];
            break;
        }
    }
    func_08022854((u8 *)entries);
    return selected;
}
