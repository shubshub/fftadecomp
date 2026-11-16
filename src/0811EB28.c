/* 0x0811EB28: complete 264-byte function, including the literal pool.
 * f0b585b0051c0f1c141c398801296fd0012902dc002908d06ae080204000814214d00130
 * 814223d062e0b88a20700006010e01295cd104480091062100220023b5f732fd54e00000
 * a4b48e08217848420843c00f044a054b00950621b9f768ff60603888013042e000500006
 * 005800066068b9f7a7ff6060002839d16d460e3503a8291cb9f774ff04ae6c461134301c
 * 211cfff631fd227803a80021435e0021685e0090c024e40401941448029002200021b8f7
 * 81fc327803a80021435e0021685e009001940e48029003200021b8f773fc0220e4f6d4fc
 * 0a4c2188014321800320e4f6cdfc21880143218002203880002005b0f0bc02bc08470000
 * 005800060050000640090003
 */
#include "control_flags.h"

typedef struct {
    u16 phase;
    u8 unknown_02[0x12];
    u16 first;
} Descriptor0811EB28;

/* 8 bytes: func_0811ECD0 registers this callback with payload size 8. */
typedef struct {
    u8 enabled;
    u8 unknown_01[3];
    void *transition;
} Payload0811EB28;

extern const u8 data_088EB4A4[];
extern u8 data_06005000[];
extern u8 data_06005800[];
extern void func_080D45D0(const void *rows, u8 index, u8 bank, u8 first_row, u8 count);
extern void *func_080D8A58(u8 mode, u8 palette, void *first_destination,
                           void *second_destination, void *parent);
extern void *func_080D8AEC(void *task);
extern void func_080D8A98(u16 *first_output, u16 *second_output);
extern void func_0801E620(u8 *first, u8 *second);
extern void func_080D74E0(u8 first, u8 second, u8 third, s16 x, s16 y,
                          void *first_buffer, void *second_buffer);
extern u16 func_080035A8(u8 index);

u32 func_0811EB28(void *task, Descriptor0811EB28 *descriptor,
                  Payload0811EB28 *payload)
{
    u16 x, y;
    u8 first, second;

    switch (descriptor->phase) {
    case 0:
        payload->enabled = descriptor->first;
        if (payload->enabled == 1)
            func_080D45D0(data_088EB4A4, 6, 0, 0, 1);
        break;
    case 1:
        /* The ROM tests phase 1 on its own (0x0811EB34) and does nothing. */
        break;
    case 0x100:
        payload->transition = func_080D8A58(payload->enabled != 0, 6,
                                            data_06005000, data_06005800, task);
        descriptor->phase++;
        break;
    case 0x101:
        payload->transition = func_080D8AEC(payload->transition);
        if (payload->transition == 0) {
            func_080D8A98(&x, &y);
            func_0801E620(&first, &second);
            func_080D74E0(2, 0, second, x, y, (void *)0x06000000, data_06005800);
            func_080D74E0(3, 0, first, x, y, (void *)0x06000000, data_06005000);
            g_control_flags_03000940.display |= func_080035A8(2);
            g_control_flags_03000940.display |= func_080035A8(3);
            descriptor->phase = 2;
        }
        break;
    }
    return 0;
}
