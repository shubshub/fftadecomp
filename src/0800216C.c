#include "ffta.h"

typedef struct {
    u8 code_0;
    u8 code_1;
    u8 unknown_02[3];
    u8 enabled;
} ResetControl;

extern ResetControl data_03000ED0;
extern u16 data_03000E50;
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08145798(void);
extern void func_081452F4(void);

/* plausible: LCD display control enters forced blank. */
#define REG_DISPCNT (*(volatile u16 *)0x04000000)
/* plausible: Hardware interrupt-enable mask. */
#define REG_IE (*(volatile u16 *)0x04000200)
/* plausible: Hardware interrupt-master enable. */
#define REG_IME (*(volatile u16 *)0x04000208)
/* plausible: LCD status and interrupt settings. */
#define REG_DISPSTAT (*(volatile u16 *)0x04000004)
/* plausible: DMA channel 0 count and control. */
#define REG_DMA0CNT (*(volatile u32 *)0x040000B8)
/* plausible: DMA channel 1 count and control. */
#define REG_DMA1CNT (*(volatile u32 *)0x040000C4)
/* plausible: DMA channel 2 count and control. */
#define REG_DMA2CNT (*(volatile u32 *)0x040000D0)
/* plausible: DMA channel 3 count and control. */
#define REG_DMA3CNT (*(volatile u32 *)0x040000DC)

/* Consume the reset request set by the key handler or the explicit reset API. */
void func_0800216C(void)
{
    int i;
    u8 low = data_03000ED0.code_0;
    u8 high = data_03000ED0.code_1;

    if (((high << 8) | low) == 0x5DA3) {
        u16 zero;

        data_03000ED0.code_0 = 0;
        data_03000ED0.code_1 = 0;
        zero = 0;
        func_0814186C(&zero, (void *)0x05000000, 0x01000200);
        REG_DISPCNT = 0x80;
        func_08145798();
        func_081452F4();
        for (i = 0; i < 1000; i++) {
            data_03000E50 = 0;
            REG_IE = 0;
            REG_IME = 0;
            REG_DISPSTAT = 0;
            REG_DMA0CNT = 0;
            REG_DMA1CNT = 0;
            REG_DMA2CNT = 0;
            REG_DMA3CNT = 0;
        }
        ((void (*)(void))0x08000000)();
    }
}
