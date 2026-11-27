#include "ffta.h"

/* Target: [0x080094BC, 0x080096B0), 500 bytes: 187 instructions, two
 * 40-byte jump tables (0x080094F0, 0x080095B8), eight literal words and
 * alignment halfwords.  Reads (read != 0) or sets (read == 0) one row of the
 * options menu; rows 0-9 are the entries func_080088D8 builds, row 9 being
 * "restore defaults".
 *
 * The four option bytes at state +0x1BCC (copied from the game's options at
 * 0x02002FC0 by func_08008818, back by func_08008954, and compared with them
 * by func_08009140) are a packed struct of halfword bit-fields:
 *  - every field is read and written with ldrb/strb (0x08009518-0x0800955C,
 *    0x080095E4-0x0800967E), where agbcc reads a 4-aligned 4-byte struct as
 *    a word; and the defaults at 0x0851BA4E sit on a halfword, not a word;
 *  - the boolean stores at 0x08009620-0x0800965C are rsbs; lsrs #31 with no
 *    orrs, the form agbcc gives value != 0 stored to a u16 field (a u8 field
 *    gives rsbs; orrs; lsrs #31).
 * Field names are the menu rows; unknown fields are named by hex bit number. */
typedef struct {
    u16 option_1 : 1;
    u16 speed : 2;          /* row 2, passed to func_08009920 */
    u16 option_3 : 2;
    u16 unknown_05 : 1;
    u16 option_4 : 1;
    u16 option_6 : 1;
    u16 option_5 : 1;
    u16 option_7 : 1;
    u16 option_8 : 3;
    u16 unknown_0D : 3;
    u16 option_0 : 2;
    u16 unknown_12 : 14;
} __attribute__((packed)) Settings;

typedef struct {
    u8 unknown_00[0x18];
    u16 field_18;
    u16 field_1A;
} ClampState08017B68;

typedef struct {
    u8 unknown_00[0x11];
    s8 selection;
} Panel080094BC;

typedef struct {
    u8 value;
    u8 count;
    u8 width;
    u8 enabled;
} OptionEntry;

typedef struct {
    u8 unknown_0000[0x2F0];
    ClampState08017B68 control;     /* +0x2F0 */
    u8 unknown_030C[4];
    Panel080094BC panel;            /* +0x310 */
    u8 unknown_0324[0x14];
    OptionEntry entries[10];        /* +0x338 */
    u8 unknown_0360[0x186C];
    Settings settings;              /* +0x1BCC */
} State080094BC;

extern State080094BC *data_02009188;
extern const u8 g_table_0851BA4E[];

u16 func_08017B68(ClampState08017B68 *state, u32 index);
int func_080096B0(const void *first, const void *second, int size);
void func_08009920(u8 mode);
void *func_081443FC(void *destination, const void *source, u32 bytes);

u8 func_080094BC(u8 option, u8 read)
{
    Settings *settings = &data_02009188->settings;
    s16 index;
    u8 value;

    if (read) {
        switch (option) {
        case 0:
            return settings->option_0;
        case 1:
            return settings->option_1;
        case 2:
            return settings->speed;
        case 3:
            return settings->option_3 != 0;
        case 4:
            return settings->option_4 != 0;
        case 5:
            return settings->option_5 != 0;
        case 6:
            return settings->option_6 != 0;
        case 7:
            return settings->option_7 != 0;
        case 8:
            return settings->option_8;
        case 9:
            return func_080096B0(settings, g_table_0851BA4E, 4) == 0;
        }
    } else {
        ClampState08017B68 *control = &data_02009188->control;
        Panel080094BC *panel = &data_02009188->panel;

        index = func_08017B68(control, panel->selection);
        value = data_02009188->entries[index].value;
        switch (option) {
        case 0:
            settings->option_0 = value;
            break;
        case 1:
            settings->option_1 = value;
            break;
        case 2:
            settings->speed = value;
            func_08009920(settings->speed);
            break;
        case 3:
            settings->option_3 = value != 0;
            break;
        case 4:
            settings->option_4 = value != 0;
            break;
        case 5:
            settings->option_5 = value != 0;
            break;
        case 6:
            settings->option_6 = value != 0;
            break;
        case 7:
            settings->option_7 = value != 0;
            break;
        case 8:
            settings->option_8 = value;
            break;
        case 9:
            if (value == 0)
                return 1;
            func_081443FC(&data_02009188->settings, g_table_0851BA4E, 4);
            break;
        }
    }
    return 0;
}
