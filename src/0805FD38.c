#include "ffta.h"

/* 0x0805FD38..0x0805FEA6: 366 bytes.
 * 00b509040b0c00780138062800d9abe080000249401800688746000058fd050874fd050884fd
 * 0508a0fd0508f0fd050808fe050868fe0508c8fd0508024819048913a43188e00000f0675508
 * 04480168180480132031091808680249007859e04cf40002987e550807480168180480132031
 * 09180868054b02784078032108400002104380004ee04cf400024ca655080748016818048013
 * 203109180868054b02784078032108400002104380003ae04cf400024ca65508044801681804
 * 801320310918086800684fe000004cf4000218040314012b23dc09480168981ecb7ec0188000
 * 203109180968002902d00878002809d1012010700248802149000ae04cf40002f0675508f922
 * 5200101c09784018024980004018006826e080665208024886235b00c01800681ee0f0675508
 * 0b48016818048013203109180968f9235b00181c0b78c018031c4888002801d0012010700348
 * 99000918086805e000004cf4000280665208002002bc0847
 */

typedef struct {
    u8 low;
    u8 high;
    u16 flag;
} Entry0805FD38;

typedef struct {
    const u8 *text;
} Text0805FD38;

typedef union {
    const Entry0805FD38 *entry;
    const Text0805FD38 *text;
} MenuEntry0805FD38;

typedef struct Context0805FD38 {
    u8 unknown_00[0x1B];
    u8 base;
    u8 unknown_1c[4];
    MenuEntry0805FD38 entries[1];
} Context0805FD38;

extern Context0805FD38 *data_0200F44C;
extern const u8 *const g_table_08526680[];
extern const u8 *const g_table_085567F0[];
extern const u8 *const g_table_0855A64C[];
extern const u8 *const data_08557E98[];

/* Complete [0x0805FD38, 0x0805FEA6): 366 bytes, 135 instructions. */
const u8 *func_0805FD38(u8 *kind, u16 index, u8 *flag)
{
    switch (*kind) {
    case 1:
        return g_table_085567F0[(s16)index + 41];
    case 2: {
        const Entry0805FD38 *entry = data_0200F44C->entries[(s16)index].entry;
        return data_08557E98[entry->low];
    }
    /* A packed u16 identifier : 10 bitfield (as in src/0805064C.c) changes the load order. */
    case 3: {
        const Entry0805FD38 *entry = data_0200F44C->entries[(s16)index].entry;
        const u8 *const *table = g_table_0855A64C;
        u32 low = entry->low;
        u32 high = entry->high;

        return table[((high & 3) << 8) | low];
    }
    case 7: {
        const Entry0805FD38 *entry = data_0200F44C->entries[(s16)index].entry;
        const u8 *const *table = g_table_0855A64C;
        u32 low = entry->low;
        u32 high = entry->high;

        return table[((high & 3) << 8) | low];
    }
    case 4:
        return data_0200F44C->entries[(s16)index].text->text;
    case 5:
        if ((s16)index < 2) {
            s32 slot = (s16)index - 2;
            const Entry0805FD38 *entry = data_0200F44C->entries[slot + data_0200F44C->base].entry;
            if (entry == 0 || entry->low == 0) {
                *flag = 1;
                return g_table_085567F0[0x40];
            } else {
                u16 id = 0x1F2 + entry->low;
                return g_table_08526680[id];
            }
        } else {
            return g_table_085567F0[0x43];
        }
    case 6: {
        const Entry0805FD38 *entry = data_0200F44C->entries[(s16)index].entry;
        u16 id = 0x1F2 + entry->low;
        if (entry->flag != 0)
            *flag = 1;
        return g_table_08526680[id];
    }
    }
    return 0;
}
