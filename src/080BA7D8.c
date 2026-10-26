#include "ffta.h"

/* 0x080BA7D8..0x080BA7FA: 34 bytes, 15 Thumb instructions. */
typedef struct {
    void *resource;
    u8 unknown_04[8];
} TileEntry;

typedef struct {
    TileEntry *head;
    TileEntry entries[13];
} TileList;

extern void func_0808F7CC(void *resource);
extern void func_08022854(void *allocation);

void func_080BA7D8(TileList *list)
{
    s32 i;
    for (i = 0; i < 13; i++) {
        func_0808F7CC(list->entries[i].resource);
    }
    func_08022854(list);
}
