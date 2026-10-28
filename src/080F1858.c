#include "ffta.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    u32 input;
} Descriptor080F1858;

typedef struct {
    s16 x;
    s16 y;
    u32 unknown_04;
    void *timeline;
    void *children[4];
    u32 input;
    void *result;
} Payload080F1858;

extern u16 g_control_flags_03000940;
extern u32 func_080035A8(u8 index);
extern void func_080D7220(const void *resource, u8 bank, u8 channel,
                         s32 x, s32 y, u16 extra);
extern void *func_080D3E9C(const void *resource, void *parent);
extern void *func_080D4704(const void *resource, void *parent);
extern void *func_080DFD8C(const void *data, u8 mode, u16 flags,
                         u16 value, void *parent);
extern void *func_080D3F08(void *task);
extern u8 func_080D48DC(void **tasks, u16 count);

/* 0x080F1858 - 238 target bytes, including literals and internal alignment.
 * children[1] is polled with the other slots but is never assigned here. */
u32 func_080F1858(void *task, Descriptor080F1858 *descriptor,
                  Payload080F1858 *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->input = descriptor->input;
        payload->x = 120;
        payload->y = 48;
        break;
    case 0x100:
        func_080D7220((const void *)0x088F4E9C, 0, 2,
                      payload->x, payload->y, 0);
        payload->timeline = func_080D3E9C((const void *)0x0894DBE8, task);
        payload->children[0] = func_080D4704((const void *)0x0894B8E8, task);
        payload->children[2] = func_080D4704((const void *)0x0894B268, task);
        payload->children[3] = func_080D4704((const void *)0x08949DD8, task);
        payload->result = func_080DFD8C((const void *)0x0839A57C, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        payload->timeline = func_080D3F08(payload->timeline);
        if (payload->timeline)
            break;
        if (func_080D48DC(payload->children, 4)) {
            u32 mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
            descriptor->phase++;
        }
        break;
    case 0x102:
        descriptor->phase = 2;
        break;
    }
    return 0;
}
