#include "ffta.h"

typedef struct {
    u32 first;
    u32 second;
} Pair;

typedef struct {
    u32 second;
    const Pair *source;
} Selection;

extern void func_080C7B78(const Pair *source, u32 *second, u32 *first);

/* Complete target: [0x080C7E38, 0x080C7E68), 48 bytes. */
s32 func_080C7E38(const Pair *source, Selection *selection)
{
    u32 second = (u32)-1;
    u32 first;

    func_080C7B78(source, &second, &first);
    if (selection->second != second)
        return 1;
    selection->source = source;
    return 0;
}
