#include "ffta.h"
#include "control_flags.h"

// Target 0x08025688: complete 152-byte Thumb function, including literals.
typedef struct {
    u16 status;
    u8 unknown_02;
    u8 enabled;
    u8 mode;
    u8 unknown_05[7];
    u16 cursor;
    u8 unknown_0E[0x12];
    void *manager;
} MenuState08025688;

typedef struct {
    u8 unknown_00[8];
    u32 arg;
    u16 value;
} Request08025688;

typedef struct {
    u8 unknown_00[0x14];
    u16 delay;
    u8 unknown_16[6];
} TaskDescriptor08025688;

typedef u32 (*TaskCallback08025688)(void *, TaskDescriptor08025688 *, void *);
extern MenuState08025688 *data_0200F438;
extern Request08025688 g_state_020020D0;
extern u32 func_08029188(void *, TaskDescriptor08025688 *, void *);
extern void *func_08005954(void *, TaskCallback08025688, u16,
                         TaskDescriptor08025688 *, void *);

void func_08025688(u16 cursor, u16 value, u32 arg)
{
    TaskDescriptor08025688 descriptor;

    data_0200F438->enabled = 0;
    data_0200F438->mode = 12;
    data_0200F438->status = 0;
    g_control_flags_03000940.display |= 0xC00;
    if (cursor == 0)
        data_0200F438->cursor = value;
    else if (!(cursor & 0x4000))
        data_0200F438->cursor = cursor | 0x8000;
    else
        data_0200F438->cursor = cursor;
    g_state_020020D0.value = value;
    g_state_020020D0.arg = arg;
    descriptor.delay = 11;
    func_08005954(data_0200F438->manager, func_08029188, 0xA4, &descriptor, 0);
}
