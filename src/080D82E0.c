#include "ffta.h"

/* 0x080D82E0..0x080D8382: 162 bytes. */
typedef struct {
    u16 state;
    u16 unknown_02;
    const s16 *position;
    u8 unknown_08[0x0C];
    u16 delay;
    u16 flags;
} EffectEvent;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u16 unknown_06;
    u16 remaining;
    u16 flags;
} EffectWork;

extern void func_080A92E4(int type, s16 x, s16 y, s16 z, int effect);
extern void func_08141570(int mode, int sound);
extern void func_08141520(int sound);

int func_080D82E0(void *unused, EffectEvent *event, EffectWork *work)
{
    const s16 *position;
    int sound_mode;
    u32 flags;

    switch (event->state) {
    case 0:
        position = event->position;
        work->x = position[0];
        work->y = position[1];
        work->z = position[2];
        work->remaining = event->delay + 1;
        work->flags = event->flags;
        break;
    case 1:
        break;
    case 0x100:
        if (--work->remaining == 0) {
            func_080A92E4(0, work->x, work->y, work->z, 0x15);
            flags = work->flags;
            sound_mode = 0;
            if (!(flags & 1)) {
                if (flags & 2)
                    sound_mode = 1;
                else if (flags & 4)
                    sound_mode = 2;

                if (sound_mode)
                    func_08141570(sound_mode, 0x8D);
                else
                    func_08141520(0x8D);
            }
            event->state = 3;
        }
        break;
    }
    return 0;
}
