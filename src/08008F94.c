#include "ffta.h"

/* Complete [0x08008F94, 0x08009030): 156 bytes, 67 instructions,
   three literal words. */

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
    u8 (*rows)[32];
} Display08008F94;

typedef struct {
    u8 value;
    u8 count;
    u8 width;
    u8 enabled;
} OptionEntry08008F94;

typedef struct {
    u8 unknown_00[0x18];
    Display08008F94 *display;
    u8 unknown_1C[8];
    u8 renderer[0x2cc];
    ClampState08017B9C control;
    u8 unknown_310[0x28];
    OptionEntry08008F94 entries[10];
} State08008F94;

extern State08008F94 *data_02009188;
extern const u8 *const g_table_085567F0[];

u16 func_08017B68(ClampState08017B68 *state, u32 index);
u16 func_08017B9C(ClampState08017B9C *state, u32 index);
void func_08013A88(void *destination, u16 count);
extern void func_08015110(void *, void *, const void *, u32, u32);
u8 func_08009030(u8 index, u8 *destination);

void func_08008F94(s16 index)
{
    ClampState08017B9C *control = &data_02009188->control;
    OptionEntry08008F94 *entry;
    u8 *destination;
    const u8 *text;
    u16 selected;
    u8 unavailable = 0;

    destination = data_02009188->display->rows[
        func_08017B9C(control, (s8)index)];
    func_08013A88(destination, control->field_15 * 2);
    selected = func_08017B68((ClampState08017B68 *)control, (s8)index);
    text = g_table_085567F0[selected + 0x2e9];
    entry = &data_02009188->entries[selected];
    if (entry->enabled == 0)
        unavailable = 1;
    func_08015110(data_02009188->renderer, destination, text, unavailable, 1);
    func_08009030(selected, destination);
}
