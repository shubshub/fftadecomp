#include "ffta.h"

typedef struct {
    u8 selection;
    u8 enabled;
    u8 row;
    u8 unknown_03;
} Slot;

typedef struct {
    u16 count;
    u16 width;
    u16 text_ids[8];
} TextRow;

typedef void (*ClearBuffer)(void *destination, s32 size);

u8 func_080C9540(u16 bit_index);
void func_08013528(void *state, void *buffer);
void func_08013728(void *state, s16 amount);
u16 func_08015110(void *state, void *buffer, const u8 *text, u8 mode, u8 reset);
void func_0814186C(const void *source, void *destination, u32 control);

/* Target: 0x08009030, 272 bytes including seven required literal words. */
u8 func_08009030(u8 index, u8 *destination)
{
    u8 **active = (u8 **)0x02009188;
    Slot *slot = (Slot *)(*active + 0x338) + index;
    const TextRow *rows = (const TextRow *)0x0836D4D4;
    const u8 *const *texts = (const u8 *const *)0x085567F0;
    u8 selection;
    u16 text_id;
    const u8 *text;
    u16 length;
    u8 *buffer;

    if (!slot->enabled)
        return 0;

    selection = slot->selection;
    text_id = rows[index].text_ids[selection];
    text = texts[text_id];
    if (!func_080C9540(0x207) && text_id == 3) {
        text = texts[rows[index].text_ids[7]];
        selection = 7;
    }

    length = (22 - slot->row) * 64;
    buffer = *active + 0x6C8;
    (*(ClearBuffer const *)0x0836D4B8)(buffer, length);
    if (index == 8) {
        func_08013528(*active + 0x24, buffer);
        func_08013728(*active + 0x24, ((const u8 *)0x0836D59C)[selection]);
    }
    func_08015110(*active + 0x24, buffer, text, 0, index != 8);
    destination += slot->row * 64;
    func_0814186C(*active + 0x6C8, destination, length / 2);
    return 1;
}
