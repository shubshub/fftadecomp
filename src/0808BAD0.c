#include "control_flags.h"
#include "ffta.h"

/* Complete [0x0808BAD0, 0x0808BE0C): 828 bytes including the literal pool,
 * 313 instructions; a state machine on *state (0, 2..7, 10, 0xFE, 0xFF). */

typedef struct {
    u32 unknown_00[2];
    u16 first;
    u16 second;
    u16 third;
    u16 fourth;
} Block16;

typedef struct {
    u8 unknown_000[0x436];
    s16 x;
    s16 y;
    u8 unknown_43a[0x44d - 0x43a];
    u8 field_44d;
    u8 unknown_44e[0x450 - 0x44e];
    u8 mode_450;
    u8 unknown_451;
    u8 mode_452;
    u8 unknown_453[0x458 - 0x453];
    u16 value_458;
    u16 value_45a;
    u8 unknown_45c[0x95e - 0x45c];
    u8 active : 1;
    u8 unknown_95e_1 : 1;
    u8 bits_95e_2 : 2;
    u8 unknown_95e_4 : 4;
    u8 unknown_95f[0x98c - 0x95f];
    Block16 source_98c;
    u8 unknown_99c[0xbe8 - 0x99c];
    s16 x_be8;
    s16 y_bea;
    u8 unknown_bec[0x1242 - 0xbec];
    u8 byte_1242;
    u8 unknown_1243;
    Block16 copy_1244;
    u8 unknown_1254[2];
    u16 counter_1256;
} State0808BAD0;

typedef struct {
    u8 busy;
    u8 unknown_01[0x33];
    s8 x;
    s8 y;
    u8 unknown_36[0x16];
} Window0808BAD0;

typedef struct {
    u8 unknown_00[4];
    u8 *entries;
} Entries0808BAD0;

typedef struct {
    u8 unknown_00[0x0C];
    u8 width;
    u8 height;
    u8 unknown_0E[0x06];
    u16 *map;
} Layer0808BAD0;

extern State0808BAD0 *data_03002818;
extern Window0808BAD0 data_030009E0[];
extern Entries0808BAD0 data_03000E30;
extern Layer0808BAD0 data_03000E80;
extern Table data_03002730;
extern u8 data_0200F294;
extern u8 data_0200F295;
extern u8 data_0200F296;
extern u8 data_0200F297;
extern u8 data_02003CB0[];
extern u8 data_06000020[];
extern const u8 data_083BB7F0[];
extern const u8 data_08393FC0[];

extern void func_08141540(u16 song_id);
extern void func_0808B984(u32 mode);
extern void func_0808BA08(void);
extern void func_08089570(void);
extern void func_080CB9E0(void *object, u32 value);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_0808A604(u32 index, u16 mode);
extern void func_0808D624(void);
extern u32 func_080876F4(u32 index, u16 entry, s32 mode);
extern void func_0804C7A0(void *entries, u16 index);
extern u32 func_0800543C(void *destination, const void *source);

/* An inlined copy of func_0808EE74 (src/0808EE74.c): 0x0808BB96..0x0808BBC0
 * repeats its 0x0808EE76..0x0808EE9E instruction for instruction, with the
 * count 42 in r8 instead of r7. */
static inline void inlined_0808EE74(void)
{
    u8 *buffer = data_02003CB0;
    u8 *destination = data_06000020;
    s32 count = 42;
    s32 index = 0;

    do {
        func_080CB9E0(buffer, data_08393FC0[index]);
        func_0814186C(buffer, destination, 0x80);
        destination += 0x100;
        index++;
    } while (index < count);
}

/* Decodes data_083BB7F0 into the buffer and copies its 0x380 bytes to tile
 * 0x15B of the 0x06008000 character block, the two calls src/08087300.c
 * makes for the same graphic.  Here the source register is set first
 * (0x0808BDB4), before the destination and count; where the calls stand in
 * line, in 08087300 (0x080873C0..0x080873C6) and 0808BF24
 * (0x0808C01A..0x0808C020), it is set last.  0x0600AB60 is a plain number:
 * its pool word (0x0808BDE0) has no relocation, and data_0600AB60 changes
 * the code (824/828 bytes). */
static inline void load_tiles_083BB7F0(u8 *buffer)
{
    func_0800543C(buffer, data_083BB7F0);
    func_0814186C(buffer, (void *)0x0600AB60, 0x1C0);
}

void func_0808BAD0(u32 unused, u8 *state)
{
    u8 *buffer;
    State0808BAD0 *state_block;

    switch (*state) {
    case 0:
        func_08141540(0x65);
        data_03002818->field_44d = 2;
        data_03002818->copy_1244 = data_03002818->source_98c;
        state_block = data_03002818;
        state_block->copy_1244.first = 0;
        state_block->copy_1244.second = 0;
        state_block->copy_1244.third = 0;
        state_block->copy_1244.fourth = 0;
        state_block->byte_1242 = 0;
        state_block->counter_1256 = 0;
        data_03002818->bits_95e_2 = 1;
        func_0808B984(0);
        func_0808BA08();
        func_08089570();
        inlined_0808EE74();
        data_0200F294 = 2;
        *state = 4;
        break;
    case 6:
        func_0808A604(2, 2);
        *state = 2;
        break;
    case 2:
        func_08006ADC(&data_03002730, 2, (u32)func_0808D624);
        *state = 3;
        break;
    case 3:
        if (data_03002730.flags[2] == 0xff)
            *state = 0xfe;
        break;
    case 4:
        if (data_030009E0[2].busy == 0) {
            func_080876F4(2, 0, 3);
            func_0808A604(2, 2);
            *state = data_0200F294;
        }
        break;
    case 5:
        if (data_03002818->counter_1256++ <= 9) {
            if (data_030009E0[2].y > -9) {
                data_030009E0[2].y--;
                func_0808A604(2, 2);
            }
            data_0200F296 = data_03002818->x_be8 / 8;
            data_0200F297 = data_03002818->y_bea / 8;
            data_03002818->x = data_0200F296;
            data_03002818->y = data_0200F297;
            func_0804C788(data_03000E30.entries, 0x19, data_0200F296,
                data_0200F297);
            if (data_03002818->mode_450 == 8) {
                data_03002818->mode_452 = 3;
                data_03002818->value_458 -= 8;
                data_03002818->value_45a = 0x38;
            }
            data_03002818->y_bea -= 0x40;
        } else {
            u16 clear;
            u16 *fill;

            func_0804C7A0(data_03000E30.entries, 0x1a);
            /* CpuFill16 of width * height halfwords: the SDK's vu16
             * temporary, spelled through a pointer until fftadecomp-kit#164. */
            fill = &clear;
            *fill = 0;
            func_0814186C(fill, data_03000E80.map,
                (data_03000E80.width * data_03000E80.height) | 0x01000000);
            *state = data_0200F294;
        }
        break;
    case 7:
        *state = 6;
        break;
    case 10:
        if (data_030009E0[data_0200F295].busy == 0)
            *state = data_0200F294;
        break;
    case 0xfe:
        buffer = data_02003CB0;
        g_control_flags_03000940.bg1cnt = 0xAC0A;
        load_tiles_083BB7F0(buffer);
        data_03002818->field_44d = 0;
        *state = 0xff;
        break;
    case 0xff:
        data_03002818->field_44d = 0;
        break;
    }
}
