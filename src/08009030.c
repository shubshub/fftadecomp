#include "ffta.h"

/* Complete [0x08009030, 0x08009140): 272 bytes, 116 instructions,
   seven literal words. */

typedef void (*BufferInitializer)(void *destination, u32 size);

typedef struct {
    u8 value;
    u8 count;
    u8 width;
    u8 enabled;
} OptionEntry08009030;

typedef struct {
    u8 unknown_00[0x24];
    u8 renderer[0x314];
    OptionEntry08009030 entries[10];
    u8 unknown_360[0x368];
    u8 work[0xB00];
} State08009030;

extern State08009030 *data_02009188;
extern BufferInitializer const g_callbacks_0836D4B8[];
/* Rows of {count, width, eight text ids}: OptionDefinition in src/080088D8.c. */
extern const u16 g_table_0836D4D4[][10];
extern const u8 data_0836D59C[];
extern const u8 *const g_table_085567F0[];

extern u8 func_080C9540(u16 bit_index);
extern void func_08013528(void *renderer, const void *source);
extern void func_08013728(void *renderer, s16 amount);
extern void func_08015110(void *, void *, const void *, u32, u32);
extern void func_0814186C(const void *source, void *destination, u32 control);

u8 func_08009030(u8 index, u8 *destination)
{
    OptionEntry08009030 *entry = &data_02009188->entries[index];
    u8 *buffer; /* the work buffer, then the copy's destination */
    const u8 *text;
    u16 text_id;
    u16 length;
    u8 value;

    if (entry->count == 0)
        return 0;

    value = entry->value;
    text_id = g_table_0836D4D4[index][value + 2];
    text = g_table_085567F0[text_id];
    if (!func_080C9540(0x207) && text_id == 3) {
        text = g_table_085567F0[g_table_0836D4D4[index][9]];
        value = 7;
    }

    length = (22 - entry->width) * 64;
    buffer = data_02009188->work;
    g_callbacks_0836D4B8[0](buffer, length);
    if (index == 8) {
        func_08013528(data_02009188->renderer, buffer);
        func_08013728(data_02009188->renderer, data_0836D59C[value]);
    }
    func_08015110(data_02009188->renderer, buffer, text, 0, index != 8);
    buffer = destination + entry->width * 64;
    func_0814186C(data_02009188->work, buffer, length / 2);
    return 1;
}
