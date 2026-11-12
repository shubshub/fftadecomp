#include "ffta.h"

/* Target 0x08025720: complete 56-byte Thumb function, including literals. */
typedef struct {
    u16 status;
    u8 unknown_02;
    u8 enabled;
    u8 mode;
    u8 unknown_05[0x1B];
    void *manager;
} MenuState08025720;

typedef struct {
    u8 unknown_00[0x14];
    u16 delay;
    u8 unknown_16[6];
} TaskDescriptor08025720;

typedef u32 (*TaskCallback08025720)(void *, TaskDescriptor08025720 *, void *);
extern MenuState08025720 *data_0200F438;
extern u32 func_080293DC(void *, TaskDescriptor08025720 *, void *);
extern void *func_08005954(void *, TaskCallback08025720, u16,
                         TaskDescriptor08025720 *, void *);

void func_08025720(void)
{
    TaskDescriptor08025720 descriptor;

    data_0200F438->enabled = 0;
    data_0200F438->mode = 11;
    data_0200F438->status = 0;
    descriptor.delay = 10;
    func_08005954(data_0200F438->manager, func_080293DC, 0xA4, &descriptor, 0);
}
