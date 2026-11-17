#include "ffta.h"

// Target: complete [0x0800CE08, 0x0800CF06), 254 bytes.

typedef void (*LineCallback)(void *state, u16 *destination);

typedef struct {
    u16 lines[160];
} LineTable0800CE08;

typedef struct {
    LineCallback callbacks[3];
} Callbacks0800CE08;

extern const Callbacks0800CE08 data_0814980C;
extern const u16 data_08149818[3];
extern const u16 data_08149806[3];
extern void *func_081443FC(void *destination, const void *source, u32 size);
extern void *func_0800C3CC(LineCallback callback, u16 payload_bytes,
                           u16 element_size, u16 *destination);
extern LineTable0800CE08 *func_0800C614(void *object);

void *func_0800CE08(u8 mode, u16 value, u16 *destination)
{
    LineTable0800CE08 *tables[4];
    s32 count = 0;
    Callbacks0800CE08 callbacks = data_0814980C;
    u16 payload_bytes[3];
    u16 element_sizes[3];
    void *object;
    s32 i;
    s32 j;

    func_081443FC(payload_bytes, data_08149818, sizeof(payload_bytes));
    func_081443FC(element_sizes, data_08149806, sizeof(element_sizes));
    object = func_0800C3CC(callbacks.callbacks[mode], payload_bytes[mode],
                           element_sizes[mode], destination);
    switch (mode) {
    case 0:
        tables[0] = func_0800C614(object);
        count = 1;
        break;
    case 1:
        tables[0] = func_0800C614(object);
        tables[1] = tables[0] + 1;
        count = 2;
        break;
    case 2:
        tables[0] = func_0800C614(object);
        tables[1] = tables[0] + 1;
        tables[2] = tables[0] + 2;
        tables[3] = tables[0] + 3;
        count = 4;
        break;
    }
    for (i = 0; i < count; i++)
        for (j = 0; j < 160; j++)
            tables[i]->lines[j] = value;
    return object;
}
