#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u16 x;
    u16 y;
    u16 unknown_0c;
    u16 extra_height;
    u8 flags;
    u8 unknown_11[3];
} Panel08060828;

typedef struct {
    u8 mode;
    u8 unknown_01[0x5b];
    Panel08060828 first;
    Panel08060828 second;
} State08060828;

typedef struct {
    u8 unknown_000[0x1d];
    u8 panel_flags;
    u16 id;
    u8 unknown_020[0x594];
    u8 object[1];
} Global08060828;

extern Global08060828 *data_0200F44C;
extern u8 data_030008B0[];
extern u8 data_03000990[];
extern void func_08013390(void *);
extern void func_08019A8C(void *, u16, void *, void *);
extern void func_08013434(void);
extern void func_080615B0(void);
extern void func_08017D18(Panel08060828 *, u32);

/* Complete [0x08060828, 0x080608DE): 182 bytes, 73 instructions. */
void func_08060828(State08060828 *state)
{
    Panel08060828 *first = &state->first;
    Panel08060828 *second = &state->second;

    func_08013390(data_0200F44C->object);
    func_08019A8C(data_0200F44C->object, data_0200F44C->id,
                  data_030008B0, data_03000990);
    switch (state->mode) {
    case 1:
    case 5:
        func_08013434();
        break;
    case 6:
        func_080615B0();
        break;
    }
    data_0200F44C->panel_flags = first->flags;
    if (first->y + first->extra_height <= 0x40)
        func_08017D18(first, 0);
    else
        func_08017D18(first, 1);

    if (second) {
        if (second->x <= 0xe0 && second->y <= 0x40)
            second->flags &= ~4;
        second->flags |= 0x40;
    }
}
