#include "ffta.h"

// Complete [0x0814553C, 0x08145608), 204 bytes including the literal pool.
// Initialises the sound state: clears the signature, resets DMA and sound
// registers, points the FIFO at the state's buffer, fills the handler table
// and stamps the signature last.

typedef void (*SoundHandler)(void);

typedef struct {
    u32 signature;
    u8 unknown_04[2];
    u8 unknown_06;
    u8 unknown_07;
    u8 unknown_08[0x20];
    SoundHandler unknown_28;
    SoundHandler unknown_2c;
    SoundHandler unknown_30;
    void *unknown_34;
    SoundHandler unknown_38;
    SoundHandler unknown_3c;
} SoundState;

extern SoundState *data_03007FF0;
extern u8 data_02008E60[];
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08144E08(void);
extern void func_081465E4(void);
extern void func_0814492C(void *);
extern void func_08145608(u32);

void func_0814553C(SoundState *state)
{
    u32 zero;

    state->signature = 0;
    /* plausible: mapped DMA control is a physical word register. */
    if (*(volatile u32 *)0x040000C4 & 0x2000000)
        *(volatile u32 *)0x040000C4 = 0x84400004;
    /* plausible: mapped DMA control is a physical halfword register. */
    *(volatile u16 *)0x040000C6 = 0x400;
    /* plausible: mapped sound register is a physical halfword register. */
    *(volatile u16 *)0x04000084 = 0x8F;
    /* plausible: mapped sound register is a physical halfword register. */
    *(volatile u16 *)0x04000082 = 0xB0E;
    /* plausible: mapped sound register is a physical byte register. */
    *(volatile u8 *)0x04000089 = (*(volatile u8 *)0x04000089 & 0x3F) | 0x40;
    /* plausible: mapped DMA destination is a physical word register. */
    *(volatile u32 *)0x040000BC = (u32)state + 0x350;
    /* plausible: mapped DMA destination is a physical word register. */
    *(volatile u32 *)0x040000C0 = 0x040000A0;
    data_03007FF0 = state;
    zero = 0;
    func_0814186C(&zero, state, 0x05000260);
    state->unknown_06 = 8;
    state->unknown_07 = 15;
    state->unknown_38 = func_08144E08;
    state->unknown_28 = func_081465E4;
    state->unknown_2c = func_081465E4;
    state->unknown_30 = func_081465E4;
    state->unknown_3c = func_081465E4;
    func_0814492C(data_02008E60);
    state->unknown_34 = data_02008E60;
    func_08145608(0x40000);
    state->signature = 0x68736D53;
}
