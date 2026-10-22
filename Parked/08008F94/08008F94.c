/* 0x08008F94 - 156 bytes including three trailing literal words. */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 field_18;
    u16 field_1A;
} ClampState08017B68;

typedef struct {
    u8 unknown_00[0x15];
    u8 field_15;
    u8 unknown_16;
    u8 field_17;
    u16 field_18;
    u16 field_1A;
    u16 field_1C;
} ClampState08017B9C;

typedef struct {
    u8 unknown_00[0x10];
    u8 *buffer;
} Display08008F94;

typedef struct {
    u8 unknown_00[3];
    u8 enabled;
} Entry08008F94;

typedef struct {
    u8 unknown_00[0x18];
    Display08008F94 *display;
    u8 unknown_1C[8];
    u8 renderer[0x2cc];
    ClampState08017B9C control;
    u8 unknown_310[0x28];
    Entry08008F94 entries[0];
} State08008F94;

extern const u8 *const g_table_085567F0[];
u16 func_08017B9C(ClampState08017B9C *state, u32 index);
u16 func_08017B68(ClampState08017B68 *state, u32 index);
void func_08013A88(void *destination, u16 count);
u16 func_08015110(void *renderer, void *destination, const u8 *text,
                u8 unavailable, u8 reset);
u8 func_08009030(u8 index, u8 *destination);

void func_08008F94(s8 index)
{
    State08008F94 **state = (State08008F94 **)0x02009188;
    ClampState08017B9C *control = &(*state)->control;
    u8 unavailable = 0;
    u16 position = func_08017B9C(control, index);
    u8 *destination = (*state)->display->buffer + position * 32;
    u16 entry;
    const u8 *text;

    func_08013A88(destination, control->field_15 * 2);
    entry = func_08017B68((ClampState08017B68 *)control, index);
    text = g_table_085567F0[entry + 0x2e9];
    if ((*state)->entries[entry].enabled == 0)
        unavailable = 1;
    func_08015110((*state)->renderer, destination, text, unavailable, 1);
    func_08009030(entry, destination);
}
