#include "ffta.h"

// Target: complete [0x0800CC8C, 0x0800CE08), 380 bytes / 166 instructions.

typedef void (*LineCallback)(void *state, u16 *destination);

typedef struct {
    LineCallback callbacks[2][3];
} Callbacks0800CC8C;

typedef struct {
    u32 value : 16;
    u32 unknown_02 : 8;
    u32 unknown_03 : 8;
    u32 unknown_04 : 8;
    u32 unknown_05 : 8;
} Entry0800CC8C;

typedef struct {
    u16 value;
    u8 first_line;
    u8 last_line;
    u8 unknown_04;
    u8 unknown_05;
    u8 unknown_06;
    u8 unknown_07;
    u8 unknown_08[0x14];
} Line0800CC8C;

extern const Callbacks0800CC8C data_081497E8;
extern const u16 data_08149800[3];
extern const u16 data_08149806[3];
extern void *func_081443FC(void *destination, const void *source, u32 size);
extern void *func_0800C3CC(LineCallback callback, u16 payload_bytes,
                           u16 element_size, u16 *destination);
extern Line0800CC8C *func_0800C614(void *object);
extern void func_0800C628(void *object, u8 enabled);

static inline void set_line(Line0800CC8C *line, const Entry0800CC8C *entry,
                            u8 first, u8 last)
{
    line->value = entry->value;
    line->unknown_04 = entry->unknown_02;
    line->unknown_05 = entry->unknown_03;
    line->unknown_06 = entry->unknown_04;
    line->unknown_07 = entry->unknown_05;
    line->first_line = first;
    line->last_line = last;
}

void *func_0800CC8C(u8 mode, u8 a, u8 b, u8 c, u16 value, u8 d,
                    u16 *destination)
{
    Line0800CC8C *lines[4];
    s32 count = 0;
    Callbacks0800CC8C callbacks = data_081497E8;
    u16 payload_bytes[3];
    u16 element_sizes[3];
    Entry0800CC8C entry;
    void *object;
    u8 bank;
    u8 kind;
    s32 i;

    func_081443FC(payload_bytes, data_08149800, sizeof(payload_bytes));
    func_081443FC(element_sizes, data_08149806, sizeof(element_sizes));
    bank = mode >> 7;
    kind = mode & 0x7F;
    object = func_0800C3CC(callbacks.callbacks[bank][kind],
                           payload_bytes[kind], element_sizes[kind],
                           destination);
    switch (kind) {
    case 0:
        lines[0] = func_0800C614(object);
        count = 1;
        break;
    case 1:
        lines[0] = func_0800C614(object);
        lines[1] = lines[0] + 1;
        count = 2;
        break;
    case 2:
        lines[0] = func_0800C614(object);
        lines[1] = lines[0] + 1;
        lines[2] = lines[1] + 1;
        lines[3] = lines[0] + 3;
        count = 4;
        break;
    }
    entry.value = value;
    entry.unknown_02 = d;
    entry.unknown_03 = c;
    entry.unknown_04 = a;
    entry.unknown_05 = b;
    for (i = 0; i < count; i++)
        set_line(lines[i], &entry, 0, 159);
    func_0800C628(object, 1);
    return object;
}
