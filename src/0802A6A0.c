#include "ffta.h"

/* Complete [0x0802A6A0, 0x0802AB4C): 1196 bytes, 524 instructions, with the
 * nine-word jump table at 0x0802A6C8 and seven literal pools.
 *
 * The two-digit number picker whose window sibling 0802A5CC opens: up/down
 * step the value by 1 (or by 10 while the tens digit is selected) between 1
 * and the maximum, left/right toggle the selected digit, the two digits are
 * redrawn every frame and a bobbing cursor sprite sits under the selected one.
 *
 * f0b557464e464546e0b489b0071c80300078082800d93ee28000024940180068
 * 87460000c8a60208eca602086ca702089ca90208a8aa0208e0aa020812ab0208
 * f0aa020822ab020836ab0208381cecf747fd0006002800d11de23e1c4b360020
 * 80460c203070bb6b3c1c7e342088b0221202111c08435880ba7c5200d2182088
 * 0130114b191c08435080381c2c30391c48310a88bb7c02210091317801910124
 * 0294022100f00efab96b3a7c7b7cf87c0090381c00f05efa381c783041460170
 * 08300470e7e1000000b0ffff391c79310c780a4b9a88402010400e1c00281dd0
 * 181cd7f725fe3a1c7c321178012008400892002804d030780a3003e000000003
 * 307801303070381c7a300278002141560020305681421dda32701be080201040
 * 3a1c7c320892002814d0181cd7f700fe089b197801200840002802d030780a38
 * 01e030780138307000203056002801dc01203070b04600203056844202d06d20
 * 16f19efe244a918830200840002809d0101cd7f7ddfd089c2078013020706d20
 * 16f18efe1d49381c483000884001096909188946089908780122924653460340
 * 9a46002b2cd007a800260b21018041807c6f4146002008560a2117f12dff021c
 * 120612160096201c49460123fef796ff7c6f4e4640364246002010560a2118f1
 * 67f8021c1206121605200090201c311c0123fef783ff2ae000000003b0080003
 * 07a80b21418001807c6f002030560a2117f102ff021c1206121605200090201c
 * 49460123fef76aff7c6f40234b449846002030560a2118f13bf8021c12061216
 * 50460090201c41460123fef757ffbd6ba888284b191c014007a8008800030143
 * a980ba7c520052199088191c014007a80088000301439180e888191c014007a8
 * 408800030143e980b97c49004919c888034007a8408800030343cb803a7c7b7c
 * f87c0090381c291c00f064f9381c783004780a340021884604700f48397c089b
 * 1a78d2430126324003328918c9007a7c0332d2007f231c402409121b44460094
 * 0194029603940494059406940023d7f7aff9d0e0ff0f0000b81639083f49381c
 * 483000884001096909188946bd6b07a8002188460b21018041807c6f7922d219
 * 9246002010560a2117f176fe021c1206121605260096201c49460123fef7defe
 * 7c6f402399445146002008560a2117f1afff021c120612160096201c49460123
 * fef7ccfea888264b191c014007a8008800030143a980ba7c520052199088191c
 * 014007a80088000301439180e888191c014007a8408800030143e980b97c4900
 * 4919c888034007a8408800030343cb80b96b3a7c7b7cf87c0090381c00f0daf8
 * 1048397c3a1c7c321278d24301231a4003328918c9007a7c0232d20044460094
 * 0194029303940494059406940023d7f72ff9391c803103204ce00000b0080003
 * ff0f0000b81639080c48397c3a1c7c321278d2430124224003328918c9007a7c
 * 0232d20000230093019302940393049305930693d7f70cf92de00000b8163908
 * 381c1021ecf710fd391c8031062021e0381cecf745fb000600281cd0391c8031
 * 082008700020002100220023fff730fc11e0381c1021ecf7f7fc391c80310720
 * 08e0381cecf72cfb0006002803d0391c803108200870381c8030007809b038bc
 * 9846a146aa46f0bc02bc0847
 */

typedef struct {
    u8 unknown_00[0x10];
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u8 unknown_14[0x18];
} Window0802A6A0;

/* The tile panel the digits are drawn into: func_0802AB64 reads its buffer
 * at +0x0C and its palette byte at +0x1F. */
typedef struct {
    u8 unknown_00[0x0C];
    u16 *buffer;
    u8 unknown_10[0x0C];
    u16 tile;
    u8 unknown_1E;
    u8 palette;
    u8 unknown_20[0x0C];
} Panel0802A6A0;

typedef struct {
    Window0802A6A0 window;
    Panel0802A6A0 panel;
    u8 unknown_58[0x1C];
    void *text;
    u8 timer;
    s8 value;
    s8 max;
    u8 unknown_7B;
    u8 digit;
    u8 unknown_7D;
    u16 base_tile;
    u8 phase;
} Picker0802A6A0;

typedef struct {
    u16 unknown_00;
    u16 pressed;
    u16 repeat;
} Input0802A6A0;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} TileState0802A6A0;

extern Input0802A6A0 data_03000000;
extern TileState0802A6A0 data_030008B0;
extern const u8 data_083916B8[];
extern u8 func_08017180(void *window);
extern void func_08017508(void *window, u8 appearance);
extern void func_080023D0(void *input);
extern void func_08141540(u32 sound);
extern void func_0802979C(void *context, void *tiles, u32 number,
                          u32 digits, u32 style);
extern void func_0802AB64(Panel0802A6A0 *panel, u16 index, u16 value,
                          u8 offset, u8 count, u16 tag, u8 flag);
extern void func_0802AC14(void *window, u16 *source, u8 x, u8 y, u8 height);
extern void func_08001CF0(const void *source, s32 x, s32 y, u8 mode,
                          u8 first_flag, u8 second_flag, u8 third_flag,
                          u8 fourth_flag, u32 value, u8 count, u32 extra);
extern void func_0802A370(u8 x, u8 y, u8 width, u8 height);

u8 func_0802A6A0(Picker0802A6A0 *state)
{
    u16 palette[2];
    u8 *tiles;
    u16 *buffer;

    switch (state->phase) {
    case 0:
        if (!func_08017180(&state->window))
            break;
        state->panel.palette = 12;
        state->panel.buffer[1] = state->base_tile | 0xB000;
        state->panel.buffer[state->window.width + 1] =
            (state->base_tile + 1) | 0xB000;
        func_0802AB64(&state->panel, 2, state->panel.tile, state->window.width,
                      2, state->panel.palette, 1);
        func_0802AC14(&state->window, state->panel.buffer, state->window.x,
                      state->window.y, state->window.height);
        state->timer = 0;
        state->phase = 1;
        break;
    case 1: {
        /* Read with ldrb at 0x0802A770, unlike the ldrsb reads of the
           field itself. */
        u8 old = state->value;

        if (data_03000000.repeat & 0x40) {
            func_080023D0(&data_03000000);
            if (state->digit & 1)
                state->value += 10;
            else
                state->value += 1;
            if (state->max < state->value)
                state->value = state->max;
        } else if (data_03000000.repeat & 0x80) {
            func_080023D0(&data_03000000);
            if (state->digit & 1)
                state->value -= 10;
            else
                state->value -= 1;
            if (state->value < 1)
                state->value = 1;
        }
        if (old != state->value)
            func_08141540(0x6D);
        if (data_03000000.repeat & 0x30) {
            func_080023D0(&data_03000000);
            state->digit++;
            func_08141540(0x6D);
        }
        /* Both digits keep palette 11; each arm stores its own digit's
           entry first (0x0802A84C and 0x0802A8A4). */
        /* value is s8, so each quotient and remainder is narrowed back to s8
           (lsls/asrs #24 after the runtime calls, 0x0802A860 onwards). */
        tiles = data_030008B0.tiles + state->panel.tile * 32;
        if (state->digit & 1) {
            palette[0] = 11;
            palette[1] = 11;
            func_0802979C(state->text, tiles, state->value / 10, 1, 0);
            func_0802979C(state->text, tiles + 0x40, state->value % 10, 1, 5);
        } else {
            palette[1] = 11;
            palette[0] = 11;
            func_0802979C(state->text, tiles, state->value / 10, 1, 5);
            func_0802979C(state->text, tiles + 0x40, state->value % 10, 1, 0);
        }
        buffer = state->panel.buffer;
        buffer[2] = (buffer[2] & 0xFFF) | (palette[0] << 12);
        buffer[state->window.width + 2] =
            (buffer[state->window.width + 2] & 0xFFF) | (palette[0] << 12);
        buffer[3] = (buffer[3] & 0xFFF) | (palette[1] << 12);
        buffer[state->window.width + 3] =
            (buffer[state->window.width + 3] & 0xFFF) | (palette[1] << 12);
        func_0802AC14(&state->window, buffer, state->window.x,
                      state->window.y, state->window.height);
        state->timer += 10;
        /* The cursor sits under the selected digit: column 3 for the tens,
           4 for the ones (mvns/ands #1 at 0x0802A962). */
        func_08001CF0(data_083916B8,
                      (state->window.x + 3 + (~state->digit & 1)) * 8,
                      (state->window.y + 3) * 8 - ((state->timer & 0x7F) >> 4),
                      0, 0, 0, 1, 0, 0, 0, 0);
        break;
    }
    case 2:
        tiles = data_030008B0.tiles + state->panel.tile * 32;
        buffer = state->panel.buffer;
        palette[0] = 11;
        palette[1] = 11;
        func_0802979C(state->text, tiles, state->value / 10, 1, 5);
        func_0802979C(state->text, tiles + 0x40, state->value % 10, 1, 5);
        buffer[2] = (buffer[2] & 0xFFF) | (palette[0] << 12);
        buffer[state->window.width + 2] =
            (buffer[state->window.width + 2] & 0xFFF) | (palette[0] << 12);
        buffer[3] = (buffer[3] & 0xFFF) | (palette[1] << 12);
        buffer[state->window.width + 3] =
            (buffer[state->window.width + 3] & 0xFFF) | (palette[1] << 12);
        func_0802AC14(&state->window, state->panel.buffer, state->window.x,
                      state->window.y, state->window.height);
        func_08001CF0(data_083916B8,
                      (state->window.x + 3 + (~state->digit & 1)) * 8,
                      (state->window.y + 2) * 8, 0, 0, 0, 1, 0, 0, 0, 0);
        state->phase = 3;
        break;
    case 3:
        func_08001CF0(data_083916B8,
                      (state->window.x + 3 + (~state->digit & 1)) * 8,
                      (state->window.y + 2) * 8, 0, 0, 0, 1, 0, 0, 0, 0);
        break;
    /* The bodies run 4, 6, 5, 7 in the ROM (0x0802AAE0, 0x0802AAF0,
       0x0802AB12, 0x0802AB22). */
    case 4:
        func_08017508(&state->window, 0x10);
        state->phase = 6;
        break;
    case 6:
        if (func_08017180(&state->window)) {
            state->phase = 8;
            func_0802A370(0, 0, 0, 0);
        }
        break;
    case 5:
        func_08017508(&state->window, 0x10);
        state->phase = 7;
        break;
    case 7:
        if (func_08017180(&state->window))
            state->phase = 8;
        break;
    case 8:
        /* The table has nine entries, bounded by cmp #8 at 0x0802A6B2. */
        break;
    }
    return state->phase;
}
