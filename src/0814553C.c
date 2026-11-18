#include "ffta.h"

// MusicPlayer2000 SoundInit, the mono GBA variant of SAT-R/sa2 src/lib/m4a/m4a.c.
// Complete [0x0814553C, 0x08145608), 204 bytes including the literal pool.
// Initialises the sound state: clears the mixer lock, resets DMA and sound
// registers, points the FIFO at the state's buffer, fills the handler table
// and restores the mixer signature last.

typedef void (*SoundHandler)(void);

typedef struct {
    u32 lockStatus;
    u8 unknown_04[2];
    u8 numChans;
    u8 masterVol;
    u8 unknown_08[0x20];
    SoundHandler CgbSound;
    SoundHandler CgbOscOff;
    SoundHandler MidiKeyToCgbFreq;
    void *MPlayJumpTable;
    SoundHandler plynote;
    SoundHandler ExtVolPit;
} SoundMixerState;

extern SoundMixerState *data_03007FF0;
extern u8 data_02008E60[];
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08144E08(void);
extern void func_081465E4(void);
extern void func_0814492C(void *);
extern void func_08145608(u32);

void func_0814553C(SoundMixerState *state)
{
    u32 zero;

    state->lockStatus = 0;
    /* plausible: mapped DMA control is a physical word register. */
    if ((*(volatile u32 *)0x040000C4) & 0x2000000)
        /* plausible: resetting DMA1 clears its repeat transfer. */
        *(volatile u32 *)0x040000C4 = 0x84400004;
    /* plausible: mapped DMA control is a physical halfword register. */
    *(volatile u16 *)0x040000C6 = 0x400;
    /* plausible: mapped sound register is a physical halfword register. */
    *(volatile u16 *)0x04000084 = 0x8F;
    /* plausible: mapped sound register is a physical halfword register. */
    *(volatile u16 *)0x04000082 = 0xB0E;
    /* plausible: mapped sound register is a physical byte register. */
    *(volatile u8 *)0x04000089 = ((*(volatile u8 *)0x04000089) & 0x3F) | 0x40;
    /* plausible: DMA1 source address selects the PCM buffer. */
    *(volatile u32 *)0x040000BC = (u32)state + 0x350;
    /* plausible: mapped DMA destination is a physical word register. */
    *(volatile u32 *)0x040000C0 = 0x040000A0;
    data_03007FF0 = state;
    zero = 0;
    func_0814186C(&zero, state, 0x05000260);
    state->numChans = 8;
    state->masterVol = 15;
    state->plynote = func_08144E08;
    state->CgbSound = func_081465E4;
    state->CgbOscOff = func_081465E4;
    state->MidiKeyToCgbFreq = func_081465E4;
    state->ExtVolPit = func_081465E4;
    func_0814492C(data_02008E60);
    state->MPlayJumpTable = data_02008E60;
    func_08145608(0x40000);
    state->lockStatus = 0x68736D53;
}
