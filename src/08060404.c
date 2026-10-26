#include "ffta.h"

typedef struct {
    u8 type;
    u8 unknown_01[6];
    u8 resource;
    u32 unknown_08;
    void *child;
} Object08060404;

typedef struct {
    u8 unknown_00[0x20];
    void *records[70];
    u16 indices[2];
} MenuState08060404;

extern MenuState08060404 *data_0200F44C;
extern u8 func_080099A4(u32);
extern void func_0806025C(Object08060404 *);
extern void *func_0805F670(void *, u32);

/* 0x08060404..0x08060450: 76 bytes, 33 instructions. */
u8 func_08060404(Object08060404 *object)
{
    if (func_080099A4(object->resource)) {
        func_0806025C(object);
        if (object->type == 4) {
            MenuState08060404 *state = data_0200F44C;
            u16 *indices = state->indices;
            object->child = func_0805F670(state->records[indices[0] + indices[1]], 4);
        }
        return 1;
    }
    return 0;
}
