#include "ffta.h"

// Complete [0x08091930, 0x08091AC6): 406 bytes, including a five-entry
// jump table and literal pools.

typedef struct PaletteTransition PaletteTransition;
typedef void (*BufferCopier08091930)(void *, const void *, u32);

typedef struct {
    u32 mode;
    u8 fade[0x47E];
    u16 palette[0x100];
    PaletteTransition *first;
    PaletteTransition *second;
    u16 phase;
} Fader08091930;

extern u16 data_03003860[];
extern BufferCopier08091930 data_0836D4BC[];
extern u8 func_080902CC(void *fade);
extern u8 func_08090F70(void *fade);
extern PaletteTransition *func_081473E4(u16 start, u16 count, u16 duration,
                                        u16 red, u16 green, u16 blue);
extern PaletteTransition *func_08147D2C(u16 start, u16 count, u16 duration,
                                        const u16 *source);
extern u32 func_081485D4(void *handle);
extern void *func_081484CC(void *handle);

u8 func_08091930(Fader08091930 *fader)
{
    u8 done;

    if (fader->mode != 0)
        return func_080902CC(fader->fade);

    switch (fader->phase) {
    case 0:
        fader->first = func_081473E4(0, 0x60, 0x10, 0xD9, 0xD9, 0xD9);
        fader->second = func_081473E4(0x70, 0x90, 0x10, 0xD9, 0xD9, 0xD9);
        fader->phase = 1;
        break;
    case 1:
        if (func_081485D4(fader->first) && func_081485D4(fader->second)) {
            func_081484CC(fader->first);
            func_081484CC(fader->second);
            fader->phase = 2;
        }
        break;
    case 2:
        if (fader->mode == 0)
            done = func_08090F70(fader->fade);
        else
            done = func_080902CC(fader->fade);
        if (done == 0) {
            fader->first = func_08147D2C(0, 0x60, 0x10, &fader->palette[0]);
            fader->second = func_08147D2C(0x70, 0x90, 0x10,
                                          &fader->palette[0x70]);
            fader->phase = 3;
        }
        break;
    case 3:
        if (func_081485D4(fader->first) && func_081485D4(fader->second)) {
            func_081484CC(fader->first);
            func_081484CC(fader->second);
            data_0836D4BC[0](data_03003860, fader->palette, 0x200);
            fader->phase = 4;
        }
        break;
    case 4:
        return 0;
    }
    return 1;
}
