#include "history_unit.h"

extern u8 data_030028A0;
extern void (*const g_callbacks_0836D4B8[])(void *, u32);
extern void *func_08022840(u32 size);
extern void func_080C62CC(struct State080C62CC *, HistoryUnit *const *, s32 count, u8 active_only);

/* Complete target: [0x080C6858, 0x080C68EC), 148 bytes. */
struct State080C62CC *func_080C6858(HistoryUnit *records, s32 count)
{
    HistoryUnit *selected[12];
    s32 selected_count;
    s32 i;
    struct State080C62CC *context;

    if (data_030028A0 & 8) {
        selected_count = 0;
        for (i = 0; i < count; i++) {
            if (records[i].active)
                selected[selected_count++] = &records[i];
        }
    } else {
        g_callbacks_0836D4B8[0](records, count * sizeof(*records));
        for (i = 0; i < count; i++)
            selected[i] = &records[i];
        selected_count = count;
    }
    context = func_08022840(0xB4);
    func_080C62CC(context, selected, selected_count, (data_030028A0 >> 3) & 1);
    return context;
}
