#include "control_flags.h"
#include "ffta.h"

// Complete [0x0808BAD0,0x0808BE0C): 828 bytes including the literal pool.
// 313 instructions; a state machine on *state (0, 2..7, 10, 0xfe, 0xff).

typedef struct {
    u32 unknown_00[2];
    u16 first;
    u16 second;
    u16 third;
    u16 fourth;
} Block16;

typedef struct {
    u8 unknown_000[0x436];
    u16 first;
    u16 second;
    u8 unknown_43a[0x44d - 0x43a];
    u8 flag_44d;
    u8 unknown_44e[0x450 - 0x44e];
    u8 mode_450;
    u8 unknown_451;
    u8 mode_452;
    u8 unknown_453[0x458 - 0x453];
    u16 value_458;
    u16 value_45a;
    u8 unknown_45c[0x95e - 0x45c];
    u8 bits_95e_0 : 2;
    u8 bits_95e_2 : 2;
    u8 bits_95e_4 : 4;
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
    u8 byte_00;
    u8 unknown_01[0x34];
    s8 byte_35;
    u8 unknown_36[0x16];
} Slot0808BAD0;

typedef struct {
    u8 unknown_00[4];
    u8 *entries;
} Entries0808BAD0;

typedef struct {
    u8 unknown_00[0xc];
    u8 width;
    u8 height;
    u8 unknown_0e[6];
    u32 destination;
} Layout0808BAD0;

extern State0808BAD0 *data_03002818;
extern Slot0808BAD0 data_030009E0[];
extern Entries0808BAD0 data_03000E30;
extern Layout0808BAD0 data_03000E80;
extern Table data_03002730;
extern u8 data_0200F294;
extern u8 data_0200F295;
extern u8 data_0200F296;
extern u8 data_0200F297;
extern u8 data_02003CB0[];
extern const u8 data_083BB7F0[];
extern const u8 data_08393FC0[];
extern u16 data_06000020[];

extern void func_08141540(s32 sound);
extern void func_0808B984(u32);
extern void func_0808BA08(void);
extern void func_08089570(void);
extern void func_080CB9E0(void *object, u32 value);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_0808A604(u32 index, u16 mode);
extern void func_0808D624(void);
extern void func_080876F4(u32 first, u16 second, u32 third);
extern void func_0804C7A0(void *entries, u16 index);
extern void func_0800543C(void *destination, const void *source);

// CpuSet from the scratch buffer at 0x02003CB0 to video memory.
static inline void upload_buffer(const void *source, void *destination,
                                 u32 control)
{
    func_0814186C(source, destination, control);
}

void func_0808BAD0(u32 unused, u8 *state)
{
    int i;
    int count;
    u16 *tiles;
    u8 *buffer;
    u8 *decoded;
    State0808BAD0 *state_block;

    switch (*state) {
    case 0:
        func_08141540(0x65);
        data_03002818->flag_44d = 2;
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
        buffer = data_02003CB0;
        tiles = data_06000020;
        count = 42;
        for (i = 0; i < count; i++) {
            func_080CB9E0(buffer, data_08393FC0[i]);
            upload_buffer(buffer, tiles, 0x80);
            tiles += 0x80;
        }
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
        if (data_030009E0[2].byte_00 == 0) {
            func_080876F4(2, 0, 3);
            func_0808A604(2, 2);
            *state = data_0200F294;
        }
        break;
    case 5:
        if (data_03002818->counter_1256++ <= 9) {
            if (data_030009E0[2].byte_35 > -9) {
                data_030009E0[2].byte_35--;
                func_0808A604(2, 2);
            }
            data_0200F296 = data_03002818->x_be8 / 8;
            data_0200F297 = data_03002818->y_bea / 8;
            data_03002818->first = data_0200F296;
            data_03002818->second = data_0200F297;
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
            // CpuFill16(0, destination, width * height): the SDK's vu16
            // temporary, spelled through a pointer until fftadecomp-kit#164.
            fill = &clear;
            *fill = 0;
            func_0814186C(fill, (void *)data_03000E80.destination,
                (data_03000E80.width * data_03000E80.height) | 0x01000000);
            *state = data_0200F294;
        }
        break;
    case 7:
        *state = 6;
        break;
    case 10:
        if (data_030009E0[data_0200F295].byte_00 == 0)
            *state = data_0200F294;
        break;
    case 0xfe:
        decoded = data_02003CB0;
        g_control_flags_03000940.bg1cnt = 0xAC0A;
        func_0800543C(decoded, data_083BB7F0);
        // Tile 0x15b of the 0x06008000 character block, which the 0xAC0A
        // written to BG1CNT above selects.
        upload_buffer(decoded, (void *)0x0600AB60, 0xe0 << 1);
        data_03002818->flag_44d = 0;
        *state = 0xff;
        break;
    case 0xff:
        data_03002818->flag_44d = 0;
        break;
    }
}
