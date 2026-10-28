#include "ffta.h"

typedef struct {
    u8 unknown_00;
    u8 event;
    u16 value;
    u16 parameter;
} EventCommand08009C18;

typedef struct {
    u16 unknown_00;
    u16 value;
    u8 unknown_04[8];
} EventResource08009C18;

typedef struct {
    u8 unknown_0000[0x2191];
    u8 timer;
    u8 unknown_2192[2];
    u16 events[4];
    u8 count;
} EventState08009C18;

extern const EventResource08009C18 g_table_085644FC[];
extern EventState08009C18 g_state_02000000;
extern void func_08009C04(u16 first, u16 second);
extern const u8 *func_08009A14(u16 event);
extern void func_08009AFC(u16 event);

/* 08009C18..08009C94: 124 bytes, 46 instructions. */
void func_08009C18(const EventCommand08009C18 *command, u8 index)
{
    u16 event;
    u16 first;
    u16 second;

    if (command->parameter != 0) {
        u32 offset = index * sizeof(EventResource08009C18);
        const EventResource08009C18 *resource =
            (const EventResource08009C18 *)((const u8 *)g_table_085644FC + offset);

        first = resource->value;
        second = command->parameter;
    } else {
        first = command->value;
        second = 0;
    }
    func_08009C04(first, second);

    if (command->event == 0x4A)
        event = g_state_02000000.events[g_state_02000000.count];
    else
        event = command->event;

    if (event != 0)
        g_state_02000000.timer = func_08009A14(event)[0];
    func_08009AFC(event);
}
