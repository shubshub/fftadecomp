// func_0814011C - 0x0814011C .. 0x081401C0, 164 bytes (60 instructions,
// literal pool 0x081401AC .. 0x081401C0).
//
// A three-step phase driver.  Phase 0 runs func_0813FD78 and stores the
// object made by func_081413F8 in data_0200F3C0.  Phase 1 feeds the input
// halfwords at 0x03000000 to func_0814143C until it reports done.  Phase 2
// releases the object, sets g_state_0200F390 to 0xFF, clears 0xC000
// halfwords of VRAM from a zero halfword on the stack with DMA3, and sets
// the DISPCNT copy to 0x40.

#include "ffta.h"
#include "control_flags.h"

typedef struct {
    u16 held;
    u16 pressed;
} Input0814011C;

typedef struct {
    const void *source;
    void *destination;
    u32 control;
} DmaRegisters0814011C;

extern void *data_0200F3C0;
extern Input0814011C data_03000000;
extern u8 g_state_0200F390;
extern DmaRegisters0814011C data_040000D4;

extern void func_0813FD78(void);
extern void *func_081413F8(void);
struct State0814143C;
extern u8 func_0814143C(struct State0814143C *object, u16 pressed, u16 held);
extern void func_08141474(void *object);

static inline void fill_vram16(u16 value)
{
    // plausible: DMA3 MMIO requires volatile writes and control readback.
    volatile DmaRegisters0814011C *dma = &data_040000D4;

    dma->source = &value;
    dma->destination = (void *)0x06000000;
    dma->control = 0x8100C000;
    (void)dma->control;
}

void func_0814011C(void *unused, u8 *phase)
{
    switch (*phase) {
    case 0:
        func_0813FD78();
        data_0200F3C0 = func_081413F8();
        *phase = 1;
        break;
    case 1:
        if (func_0814143C(data_0200F3C0, data_03000000.pressed,
                          data_03000000.held) == 0)
            *phase = 2;
        break;
    case 2:
        func_08141474(data_0200F3C0);
        g_state_0200F390 = 0xFF;
        *phase = 3;
        fill_vram16(0);
        g_control_flags_03000940.display = 0x40;
        break;
    }
}
