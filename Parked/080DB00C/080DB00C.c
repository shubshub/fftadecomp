#include "ffta.h"

/* Complete target [0x080DB00C, 0x080DB540): 1332 bytes. A background task
 * callback (func_080DB540 starts it with a 0x1118-byte state): it reads a
 * sprite's 4bpp tiles back from OBJ VRAM, converts them to background tiles
 * (4bpp, or 8bpp for an affine layer), builds the screen map from the
 * sprite's OAM cells, uploads tiles and map, and copies the sprite palette
 * into the background palette bank. */

typedef struct {
    void *object;
    u8 affine;
    u8 fill;
    u8 palette;
    u8 apply_mode;
    s8 mode_value;
    u8 mode_selector;
    u8 unknown_0A[2];
    u8 *tiles;
    u16 *map;
} BackgroundParameters;

typedef struct {
    u16 state;
    u16 unknown_02;
    const BackgroundParameters *parameters;
} BackgroundTask;

typedef struct {
    BackgroundParameters parameters;
    u8 source[0x300];
    u8 tiles[0x600];
    u8 map[0x800];
    u8 column;
    u8 row;
} BackgroundState;

typedef struct {
    u8 width;
    u8 height;
} SpriteSize;

/* The three OAM attribute halfwords of one sprite cell, laid out as GBATEK
 * gives them; the cells are packed six bytes apart behind a halfword count,
 * and every field is read a byte at a time. */
typedef struct {
    u16 y : 8;
    u16 affine_mode : 2;
    u16 blend_mode : 2;
    u16 mosaic : 1;
    u16 colors : 1;
    u16 shape : 2;
    u16 x : 9;
    u16 unknown_2 : 3;
    u16 hflip : 1;
    u16 vflip : 1;
    u16 size : 2;
    u16 tile : 10;
    u16 priority : 2;
    u16 palette : 4;
} __attribute__((packed)) SpriteCell;

typedef struct {
    u16 count;
    SpriteCell cells[1];
} __attribute__((packed)) SpriteFrame;

typedef struct TransferRecord TransferRecord;

typedef struct {
    u16 bg[16][16];
    u16 obj[16][16];
} PaletteBuffer;

extern PaletteBuffer data_03003860;

extern void func_080DE33C(void *object, s8 value, u8 selector);
extern u8 func_080DE488(void *object);
extern u16 func_080DBD48(void *object);
extern const SpriteFrame *func_080DBD30(void *object, u8 *hflip, u8 *vflip);
extern TransferRecord *func_080D3AF8(void);
extern void func_08000ADC(TransferRecord *entry, const void *source,
                          void *destination, u16 words);
extern void func_08000A98(TransferRecord *record, const void *source,
                          void *destination, u16 count);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern u8 func_08099C10(const void *object);

/* CpuFill16(value, destination, size): the SDK's vu16 temporary, spelled
 * through a pointer until fftadecomp-kit#164, as src/0802C034.c does. Both
 * fills store the halfword through the pointer passed in R0 (0x080DB25E..
 * 0x080DB26C and 0x080DB290..0x080DB29E). */
#define CPU_FILL16(value, destination, size) do { \
    u16 fill; \
    u16 *fill_source = &fill; \
    *fill_source = (value); \
    func_0814186C(fill_source, (destination), \
                  0x01000000 | ((size) / 2 & 0x1FFFFF)); \
} while (0)

u32 func_080DB00C(void *task, BackgroundTask *control, BackgroundState *state)
{
    switch (control->state) {
    case 0: {
        const BackgroundParameters *parameters = control->parameters;

        state->parameters.object = parameters->object;
        state->parameters.affine = parameters->affine;
        state->parameters.fill = parameters->fill;
        state->parameters.palette = parameters->palette;
        state->parameters.apply_mode = parameters->apply_mode;
        state->parameters.mode_value = parameters->mode_value;
        state->parameters.mode_selector = parameters->mode_selector;
        state->parameters.tiles = parameters->tiles;
        state->parameters.map = parameters->map;
        state->column = 2;
        state->row = 7;
        if (state->parameters.apply_mode)
            func_080DE33C(state->parameters.object,
                          state->parameters.mode_value,
                          state->parameters.mode_selector);
        break;
    }
    case 1:
        break;
    case 0x100: {
        u16 tile;

        if (state->parameters.apply_mode &&
            !func_080DE488(state->parameters.object))
            break;
        tile = func_080DBD48(state->parameters.object);
        /* OBJ character VRAM, 0x06010000, as a plain address: the literal at
         * 0x080DB104 is reloaded at its use (0x080DB0EA). */
        func_08000ADC(func_080D3AF8(), (u8 *)0x06010000 + tile * 32,
                      state->source, 0xC0);
        control->state++;
        break;
    }
    case 0x101: {
        u8 hflip;
        u8 vflip;
        u8 *source;
        u8 *destination;
        u8 pixel;
        s16 i;

        func_080DBD30(state->parameters.object, &hflip, &vflip);
        source = state->source;
        destination = state->tiles;
        if (!state->parameters.affine) {
            /* 4bpp: a transparent nibble takes the fill colour. */
            for (i = 0; i < sizeof(state->source); i++) {
                pixel = *source;
                if ((*source & 0x0F) == 0)
                    pixel = (pixel & 0xF0) | state->parameters.fill;
                if ((*source & 0xF0) == 0)
                    pixel = (pixel & 0x0F) | (state->parameters.fill << 4);
                *destination = pixel;
                destination++;
                source++;
            }
        } else {
            /* 8bpp: each nibble becomes one byte in the palette bank, the
             * row mirrored when the sprite is flipped. */
            s16 x = 0;

            if (hflip)
                x = 7;
            for (i = 0; i < sizeof(state->source); i++) {
                /* The transparent arms' assignments are dead; the arm is in
                 * the ROM as its own block at 0x080DB1CE..0x080DB1D0 (high
                 * nibble), which a plain `if (pixel)` does not give. */
                pixel = *source & 0x0F;
                if (pixel == 0)
                    pixel = state->parameters.fill;
                else
                    destination[x] = pixel | (state->parameters.palette << 4);
                if (hflip)
                    x--;
                else
                    x++;
                pixel = *source >> 4;
                if (pixel == 0)
                    pixel = state->parameters.fill;
                else
                    destination[x] = pixel | (state->parameters.palette << 4);
                if (hflip) {
                    if (--x < 0) {
                        destination += 8;
                        x = 7;
                    }
                } else {
                    if (++x == 8) {
                        destination += 8;
                        x = 0;
                    }
                }
                source++;
            }
        }
        control->state++;
        break;
    }
    case 0x102: {
        const SpriteFrame *frame;
        /* Initialised for the affine path, which never reads it: the ROM
         * stores the 0 at 0x080DB226..0x080DB228. */
        u16 *map = 0;
        SpriteSize sizes[3][4] = {
            {{1, 1}, {2, 2}, {4, 4}, {8, 8}},
            {{2, 1}, {4, 1}, {4, 2}, {8, 4}},
            {{1, 2}, {1, 4}, {2, 4}, {4, 8}},
        };
        u8 hflip;
        u8 vflip;
        u16 base;
        s16 i;

        frame = func_080DBD30(state->parameters.object, &hflip, &vflip);
        if (!state->parameters.affine) {
            map = (u16 *)state->map;
            CPU_FILL16(0x3FF, map, sizeof(state->map));
            base = ((u32)state->parameters.tiles - 0x06008000) >> 5;
        } else {
            CPU_FILL16(0xFFFF, state->map, sizeof(state->map));
            base = ((u32)state->parameters.tiles - 0x0600C000) >> 6;
        }
        for (i = 0; i < frame->count; i++) {
            const SpriteCell *cell = &frame->cells[i];
            s16 width = sizes[cell->shape][cell->size].width;
            s16 height = sizes[cell->shape][cell->size].height;
            u16 tile = cell->tile;
            s16 y;

            for (y = 0; y < height; y++) {
                s16 x;

                for (x = 0; x < width; x++) {
                    u16 column;
                    u16 row;
                    s16 left;
                    s16 top;

                    column = state->column;
                    left = cell->x;
                    if (left & 0xFF00)
                        left |= 0xFF00;
                    if (hflip) {
                        left = -left;
                        left -= 8;
                    }
                    column += left >> 3;
                    column += hflip ? -x : x;

                    row = state->row;
                    top = cell->y;
                    if (top & 0xFF80)
                        top |= 0xFF80;
                    if (vflip) {
                        top = -top;
                        top -= 8;
                    }
                    row += top >> 3;
                    row += vflip ? -y : y;

                    if (!state->parameters.affine) {
                        u16 entry = tile + base;

                        entry |= state->parameters.palette << 12;
                        if (cell->hflip != hflip)
                            entry |= 0x400;
                        if (cell->vflip != vflip)
                            entry |= 0x800;
                        map[row * 32 + column] = entry;
                    } else {
                        state->map[row * 32 + column] = tile + base;
                    }
                    tile++;
                }
            }
        }
        control->state++;
        break;
    }
    case 0x103:
        func_08000ADC(func_080D3AF8(), state->tiles, state->parameters.tiles,
                      0x180);
        control->state++;
        break;
    case 0x104:
        func_08000A98(func_080D3AF8(), state->map, state->parameters.map,
                      0x400);
        control->state++;
        break;
    case 0x105:
        func_0814186C(data_03003860.obj[func_08099C10(state->parameters.object)],
                      data_03003860.bg[state->parameters.palette], 16);
        control->state = 2;
        break;
    }
    return 0;
}
