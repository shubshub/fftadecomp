#include "ffta.h"

typedef struct {
    u8 unknown_0000[0xCD4];
    u8 phase;
    u8 unknown_0CD5[3];
    Table runner;
    u32 handlers[2];
    u8 handler_flags[2];
    u8 unknown_0CF2[0x722];
    u8 window[1];
} MenuContext0805873C;

typedef void (*BufferInitializer0805873C)(void *destination, u32 size);

extern MenuContext0805873C *data_0200F428;
extern u8 g_state_0200F390[];
extern BufferInitializer0805873C const g_callbacks_0836D4B8[];
extern void *func_08022840(u32 size);
extern void func_08022854(u8 *object);
extern void func_08006A7C(Table *runner, u32 *words, u8 *flags, u8 count);
extern void func_080069F4(Table *runner, u8 count);
extern void func_0805C594(u8 index, u8 *flag);
extern void func_08058D40(u8 index, u8 *flag);
extern void func_0802B53C(u8 *window, u8 value);
extern void func_0802AD54(void *window);
extern void func_08009AFC(u16 event);
extern void func_08009FD0(void);

/* Complete 0x0805873C..0x08058890: 340 bytes, 118 instructions.
 * Target bytes:
 * 70b50e1c3078022864d0022804dc00280ad0012838d08ae0fe286dd0fe2800dc85e0
 * ff2870d082e0104d114c201ccaf769f828600f490a68211ce9f069fd2a680d4c1019
 * 0d4bd1180833d2180223aef777f9286800190a4a0121aef7a1f92868084940180121
 * 0170317060e028f4000204340000b8d43608d80c0000e80c000095c50508d40c0000
 * 0c48007800284ed10b4c20680b4bc018022101703170206809494018094a0021aef7
 * 7af92068084bc0180021d2f7a4fe39e0000090f3000228f40002d40c0000d80c0000
 * 418d050814140000054c206805494018d2f79cfa2068044bc0180078307020e028f4
 * 000214140000d40c0000a720b1f761f9b1f7c9fbfd20307012e00f4c2168002917d0
 * 0e480918ff20087020680d4940180221aef7caf82068c9f7f7ff0020206006480068
 * 002804d0064bc0180221aef7bcf870bc01bc0047000028f40002f10c0000d80c0000
 */
void func_0805873C(u8 index, u8 *flag)
{
    switch (*flag) {
    case 0:
        data_0200F428 = func_08022840(0x3404);
        g_callbacks_0836D4B8[0](data_0200F428, 0x3404);
        func_08006A7C(&data_0200F428->runner, data_0200F428->handlers,
                      data_0200F428->handler_flags, 2);
        func_08006ADC(&data_0200F428->runner, 1, (u32)func_0805C594);
        data_0200F428->phase = 1;
        *flag = 1;
        break;
    case 1:
        if (g_state_0200F390[0] == 0) {
            data_0200F428->phase = 2;
            *flag = 2;
            func_08006ADC(&data_0200F428->runner, 0, (u32)func_08058D40);
            func_0802B53C(data_0200F428->window, 0);
        }
        break;
    case 2:
        func_0802AD54(data_0200F428->window);
        *flag = data_0200F428->phase;
        break;
    case 0xFE:
        func_08009AFC(0xA7);
        func_08009FD0();
        *flag = 0xFD;
        break;
    case 0xFF:
        if (data_0200F428 != 0) {
            data_0200F428->handler_flags[1] = 0xFF;
            func_080069F4(&data_0200F428->runner, 2);
            func_08022854((u8 *)data_0200F428);
            data_0200F428 = 0;
        }
        break;
    }

    if (data_0200F428 != 0)
        func_080069F4(&data_0200F428->runner, 2);
}
