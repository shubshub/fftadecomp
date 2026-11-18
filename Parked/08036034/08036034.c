#include "ffta.h"

typedef struct {
    u16 id : 10;
    u16 unknown_0A : 6;
} __attribute__((packed)) SlotItem;

typedef struct {
    u8 unknown_00[0x24];
    SlotItem *items[16];
    u8 unknown_64[0x48];
    u8 count;
} ItemPanel;

typedef struct {
    void *unknown_00;
    ItemPanel *panel;
} MenuState;

extern MenuState *g_state_03002810;
extern s32 func_08035FC4(void);
extern void func_08035F8C(void);
extern u32 func_080D1C94(SlotItem **items, u32 limit, u8 advance);
extern s32 func_080301B0(SlotItem *item);

/* Native callers also pass a menu selection in r1. This routine ignores it. */
u32 func_08036034(s32 update, s32 selection)
{
    if (update) {
        SlotItem *items[16];
        u32 count;
        s32 i;

        for (i = 0; i < 16; i++)
            items[i] = 0;
        if (func_08035FC4()) {
            func_08035F8C();
            count = func_080D1C94(g_state_03002810->panel->items, 16, 1);
        } else {
            count = func_080D1C94(items, 16, 0);
        }
        if (count) {
            for (i = 0; i < 16; i++) {
                SlotItem *item = items[i];
                /* The original reads the ID before checking the slot. */
                if (item->id && item)
                    func_080301B0(item);
            }
        }
        g_state_03002810->panel->count = count;
        return count;
    }
    /* Both queries run when the first reports no change. */
    if (!func_08035FC4() && !func_08035FC4())
        return func_080D1C94(g_state_03002810->panel->items, 16, 0);
    func_08035F8C();
    return func_080D1C94(g_state_03002810->panel->items, 16, 1);
}
