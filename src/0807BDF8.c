#include "ffta.h"

// Complete [0x0807BDF8,0x0807C00C): 532 bytes including the literal pools.

typedef struct {
    u8 unknown_00[0x3a];
    u8 entries[3];
} Record0807BDF8;

typedef struct {
    u8 unknown_0000[0x68c];
    u8 text_state[0x1133 - 0x68c];
    u8 count;
    u8 list[0x1be4 - 0x1134];
    u8 unit[6];
    u8 table_index;
    u8 unknown_1beb[0x1d0c - 0x1beb];
    Record0807BDF8 *record;
} State0807BDF8;

extern State0807BDF8 *data_03002818;
extern u8 data_02003CB0[];
extern u16 data_0600C560[];
extern u8 data_0600C820[];
extern const u8 data_083C5744[];
extern const u8 data_08527244[][4];
extern const u8 *const g_table_0851BA84[];
extern const u8 *const g_table_085567F0[];

extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_08005318(const void *table, void *destination, u32 index, u32 flag);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern s32 func_080C7EA4(const void *unit, u32 field);
extern void func_08015110(void *state, void *tiles, const void *text, u32 style, u32 spacing);

void func_0807BDF8(u32 unused, u32 mode)
{
    u8 *buffer = data_02003CB0;
    void *vram;
    u16 fill;
    u16 *source = &fill;
    const u8 *row;
    const u8 *entry;
    const u8 *string;
    u32 text;
    u32 low;
    u32 palette;

    *source = 0;
    func_0814186C(source, data_0600C560, 0x010002C0);
    vram = data_0600C560;
    if (mode <= 1) {
        *func_0808B8E4(8, 1, 2, 2) = 0xd22d;
        *func_0808B8E4(8, 1, 3, 2) = 0xd22f;
        entry = data_08527244[data_03002818->list[data_03002818->count]];
        low = entry[0];
        text = (entry[1] << 8) | low;
        palette = 0;
    } else if (mode == 2) {
        row = g_table_0851BA84[data_03002818->table_index];
        *func_0808B8E4(8, 1, 2, 2) = 0xe22d;
        *func_0808B8E4(8, 1, 3, 2) = 0xe22f;
        text = *(const u16 *)(row + data_03002818->record->entries[0] * 8);
        palette = 1;
    } else if (mode == 3) {
        row = g_table_0851BA84[data_03002818->table_index];
        *func_0808B8E4(8, 1, 2, 2) = 0xd22d;
        *func_0808B8E4(8, 1, 3, 2) = 0xd22f;
        text = *(const u16 *)(row + data_03002818->record->entries[1] * 8);
        palette = 2;
    } else {
        row = g_table_0851BA84[data_03002818->table_index];
        *func_0808B8E4(8, 1, 2, 2) = 0xe22d;
        *func_0808B8E4(8, 1, 3, 2) = 0xe22f;
        text = *(const u16 *)(row + data_03002818->record->entries[2] * 8);
        palette = 3;
    }
    func_08005318(data_083C5744, buffer, palette, 1);
    func_0814186C(buffer, vram, 0xa0);
    func_080C7EA4(data_03002818->unit, 0x22);
    string = g_table_085567F0[text];
    vram = data_0600C820;
    func_08015110(data_03002818->text_state, vram, string, 0, 1);
}
