/* Target bytes (84):
 * 00 b5 e8 f6 e1 fa 00 06 00 28 11 d0 07 48 00 68
 * 00 28 06 d0 80 68 00 28 03 d0 e4 f6 f5 f8 00 21
 * 81 60 ab 20 00 f0 b0 fc 07 e0 00 00 cc 59 01 02
 * ab 20 e8 f6 69 f8 e8 f6 d1 fa 05 48 94 30 02 88
 * 80 23 db 00 19 1c 11 43 01 80 01 bc 00 47 00 00
 * 90 f3 00 02
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    void *task;
} State081219F4;

typedef struct {
    u8 unknown_00[8];
    u32 field_08;
} Payload081219F4;

typedef struct {
    u8 unknown_00[0x94];
    u16 flags;
} ScriptStateFlags;

extern State081219F4 *data_020159CC;
extern ScriptStateFlags g_state_0200F390;
extern u8 func_08009FBC(void);
extern void *func_08005BFC(void *task);
extern void *func_0812237C(u16 event);
extern void func_08009AFC(u16 event);
extern void func_08009FD0(void);

void func_081219F4(void)
{
    if (func_08009FBC()) {
        if (data_020159CC != 0 && data_020159CC->task != 0) {
            Payload081219F4 *payload = func_08005BFC(data_020159CC->task);

            payload->field_08 = 0;
        }
        func_0812237C(0xAB);
    } else {
        func_08009AFC(0xAB);
        func_08009FD0();
    }

    g_state_0200F390.flags |= 0x400;
}
