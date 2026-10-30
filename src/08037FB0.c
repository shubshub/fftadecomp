#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1F];
    u8 value;
} Window08037FB0;

typedef struct {
    u8 unknown_00[0x3A];
    u8 field_3a;
    u8 unknown_3b[0x11];
    Window08037FB0 window;
    u8 unknown_6c[0x60];
} Record08037FB0;

typedef struct {
    u8 unknown_000[0x954];
    Record08037FB0 records[0];
} State08037FB0;

extern State08037FB0 *g_state_03002810;
extern void func_08017508(Window08037FB0 *window, u8 value);
extern u8 func_080356A0(s32 index, u8 requested);

/* Complete target: [0x08037FB0, 0x08037FF0), 64 bytes. */
void func_08037FB0(s32 index)
{
    func_08017508(&g_state_03002810->records[index].window, 0x10);
    func_080356A0(index, 0);
    g_state_03002810->records[index].field_3a = 0;
}
