#include "ffta.h"

typedef struct {
    u8 unknown_0000[0xCD4];
    u8 phase;
    u8 unknown_0CD5[3];
    Table runner;
    u32 handlers[1];
    u8 handler_flags[1];
    u8 unknown_0CED[0x5D3];
    u8 window[1];
} MenuContext;

typedef void (*BufferInitializer)(void *destination, u32 size);
extern BufferInitializer g_callbacks_0836D4B8[];
extern MenuContext *data_0200F428;
extern u8 g_state_0200F390[];
extern u8 data_030008B0[];
extern u8 data_03000990[];
extern void *func_08022840(u32 size);
extern void func_08022854(void *allocation);
extern void func_08006A7C(Table *runner, u32 *handlers, u8 *flags, u8 count);
extern void func_080069F4(Table *runner, u8 count);
extern void func_080510B0(u8 index, u8 *state);
extern void func_08029E48(void *owner, void *source, void *scratch,
                          s16 columns, s16 rows, u8 enabled);
extern void func_0802B53C(void *window, u8 enabled);
extern void func_0802AD54(void *window);
extern void func_08009AFC(u16 event);
extern void func_08009FD0(void);

/* 0x08050F1C..0x08051048: 300 bytes; initialize and advance a menu task. */
void func_08050F1C(u8 index, u8 *state)
{
    switch (*state) {
    case 0:
        data_0200F428 = func_08022840(0x1D7C);
        g_callbacks_0836D4B8[0](data_0200F428, 0x1D7C);
        func_08006A7C(&data_0200F428->runner, data_0200F428->handlers,
                      data_0200F428->handler_flags, 1);
        func_08006ADC(&data_0200F428->runner, 0, (u32)func_080510B0);
        func_08029E48(data_030008B0, data_03000990, 0, 20, 17, 1);
        data_0200F428->phase = 1;
        *state = 1;
        break;
    case 1:
        if (g_state_0200F390[0] == 0) {
            data_0200F428->phase = 2;
            *state = 2;
            func_0802B53C(data_0200F428->window, 0);
        }
        break;
    case 2:
        func_080069F4(&data_0200F428->runner, 1);
        func_0802AD54(data_0200F428->window);
        *state = data_0200F428->phase;
        break;
    case 0xFE:
        if (data_0200F428 != 0) {
            func_08022854(data_0200F428);
            data_0200F428 = 0;
        }
        func_08009AFC(0xA7);
        func_08009FD0();
        *state = 0xFF;
        break;
    case 0xFF:
        break;
    }
}
