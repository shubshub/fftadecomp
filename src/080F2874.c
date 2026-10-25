#include "ffta.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    u32 input;
} Descriptor080F2874;

typedef struct {
    u16 x;
    u16 y;
    u8 counter;
    u8 unknown_05[3];
    u8 unknown_08[4];
    void *effect;
    void *timeline;
    void *child_14;
    void *child_18;
    u32 input;
    void *result;
} Payload080F2874;

extern u16 g_control_flags_03000940;
extern u32 func_080035A8(u8 index);
extern void *func_080D6098(s16 x, s16 y, u16 value, u8 flags,
                         u16 mode, void *field, const void *resource,
                         void *parent);
extern void func_080D7220(const void *resource, u8 bank, u8 channel,
                        s16 x, s16 y, u16 extra);
extern void *func_080D3E9C(const void *resource, void *parent);
extern void func_080D3F84(void *task, u8 first, u8 second);
extern void *func_080D4704(const void *resource, void *parent);
extern void *func_080D98D4(u8 channel, u16 value, u16 first, u16 second,
                         const void *resource, void *parent);
extern void *func_080DFD8C(const void *resource, u8 mode, u16 flags,
                         u16 value, void *parent);
extern void *func_080D3F08(void *task);
extern void *func_080D6134(void *task);
extern void *func_080D4774(void *task);
extern void *func_080D9B64(void *task);

/* Target: complete [0x080F2874, 0x080F29B2), 318 bytes, including
 * 280 code bytes, 32 literal bytes and six internal alignment bytes.
 * The address at +08 is passed without an inferred pointee type or extent. */
u32 func_080F2874(void *task, Descriptor080F2874 *descriptor,
                  Payload080F2874 *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->input = descriptor->input;
        payload->x = 120;
        payload->y = 96;
        break;
    case 0x100:
        payload->effect = func_080D6098((s16)payload->x, (s16)payload->y,
                                      0, 1, 1, payload->unknown_08,
                                      (const void *)0x0839A81C, task);
        func_080D7220((const void *)0x088F5BB0, 1, 3,
                     (s16)(payload->x - 48), 160, 0);
        payload->timeline = func_080D3E9C((const void *)0x0894DB38, task);
        func_080D3F84(payload->timeline, 8, 0xFF);
        payload->child_14 = func_080D4704((const void *)0x0894B658, task);
        payload->child_18 = func_080D98D4(3, 0, 1, 1,
                                        (const void *)0x0839A834, task);
        payload->result = func_080DFD8C((const void *)0x0839A8D0,
                                       1, 4, 0, task);
        payload->counter = 0;
        descriptor->phase++;
        break;
    case 0x101:
        payload->counter++;
        payload->timeline = func_080D3F08(payload->timeline);
        if (payload->timeline)
            break;
        {
            u32 mask = func_080035A8(3);
            g_control_flags_03000940 &= ~mask;
        }
        payload->effect = func_080D6134(payload->effect);
        if (payload->effect)
            break;
        payload->child_14 = func_080D4774(payload->child_14);
        if (payload->child_14)
            break;
        payload->child_18 = func_080D9B64(payload->child_18);
        if (payload->child_18)
            break;
        descriptor->phase++;
        break;
    case 0x102:
        descriptor->phase = 2;
        break;
    }
    return 0;
}
