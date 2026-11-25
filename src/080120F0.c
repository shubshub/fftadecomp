#include "ffta.h"

/* Complete [0x080120F0, 0x08012910), 2080 bytes: 774 reached instructions,
 * the 89-entry jump table for the '@' text commands 0x21..0x79 at
 * 0x08012120, and the literal pools.  Called by func_08012950 for each "@x"
 * command in the message text; a nonzero result stops the text for this
 * frame. */

typedef struct {
    u8 *base;
    u8 unknown_04[0x28c];
} Renderer080120F0;

typedef struct {
    void *window;
    u8 unknown_04[4];
    u8 status;
    u8 next_state;
    u8 type;
    u8 unknown_0b;
    u16 flags;
    s8 left;
    s8 top;
    u8 width;
    u8 height;
    u16 tile;
    u16 pending_offset;
    u16 scale;
    u16 limit;
    u8 stride;
    u8 timer;
    u8 auto_advance;
    u8 unknown_1d[3];
    u16 confirm_keys;
    u8 unknown_22[4];
    u8 busy;
    u8 handle;
    u8 sound_played;
    u8 unknown_29;
    u8 count;
    u8 unknown_2b[9];
    u16 x;
    u16 y;
    s8 phase;
    u8 unknown_39;
    u16 options;
    u8 unknown_3c[4];
    u8 line;
    u8 choice;
    u8 locked;
    u8 choice_width;
    u8 unknown_44[0x2c];
    Renderer080120F0 renderer;
    u8 *buffer;
    u8 *selected;
    const u8 *active;
    u8 text[0x400];
    u8 insert[0x40];
} Context080120F0;

typedef struct {
    u8 unknown_0000[0x2174];
    u16 auto_wait;
    u8 unknown_2176[0x2fc0 - 0x2176];
    u8 sound_flags;
} Global080120F0;

typedef struct {
    u8 unknown_00[0xb6];
    u8 confirm_sound;
} Sound080120F0;

typedef void (*BufferInitializer080120F0)(void *destination, u32 size);

extern Context080120F0 *data_0200918C;
extern Global080120F0 g_state_02000000;
extern Sound080120F0 g_state_020020D0;
extern const s8 data_0836D630[];
extern BufferInitializer080120F0 const g_callbacks_0836D4B8[];
extern u8 func_0801843C(u8 type);
extern u8 func_08018470(u8 type);
extern u8 func_08018484(u8 type);
extern u8 func_080184D0(u8 type);
extern void func_08013528(void *renderer, const void *source);
extern void func_08013570(void *renderer, const void *source, u8 width,
                          u8 mode);
extern void func_080135B8(void *renderer, s8 value);
extern void func_08013728(void *renderer, s16 amount);
extern void func_080137C0(void *renderer, u8 palette);
extern void func_08013A88(void *row, u32 width);
extern u8 func_08013AAC(u8 width, u16 flags);
extern u16 func_08014778(const u8 *text);
extern u8 *func_08014F10(const u8 *text, u8 code);
extern u16 func_080153FC(void *renderer, u8 *base, const u8 *text,
                         u8 palette, u8 stride);
extern void func_08016070(u8 code, void *renderer, void *window, u8 stride,
                          u8 left, u8 top, u16 tile, u16 flags);
extern u16 func_0801624C(u8 *destination, u8 index);
extern u8 func_08018CEC(u8 *destination, u8 code);
extern void func_08141540(u32 sound);

u8 func_080120F0(void)
{
    s32 i;
    u8 width;
    s16 text_width;
    u8 palette;
    u16 length;
    u8 layout;
    u8 skip;
    s16 amount;

    switch (data_0200918C->active[1]) {
    case 'n':
        data_0200918C->selected += data_0200918C->stride << 6;
        data_0200918C->line++;
        if (func_0801843C(data_0200918C->type))
            func_080135B8(&data_0200918C->renderer,
                          data_0836D630[data_0200918C->line]);
        else
            func_08013528(&data_0200918C->renderer, data_0200918C->selected);
        if (func_08018484(data_0200918C->type))
            func_080137C0(&data_0200918C->renderer, 5);
        data_0200918C->limit += 0x100;
        data_0200918C->active += 2;
        break;
    case 's':
        func_08013728(&data_0200918C->renderer, 6);
        data_0200918C->active += 2;
        break;
    case 'c':
        data_0200918C->count++;
        if (!func_08018470(data_0200918C->type)) {
            for (i = 0; i < data_0200918C->height >> 1; i++)
                func_08013A88(data_0200918C->buffer +
                              ((i * data_0200918C->stride) << 6),
                              data_0200918C->stride << 1);
        }
        data_0200918C->selected = data_0200918C->buffer;
        data_0200918C->line = 0;
        if (func_0801843C(data_0200918C->type))
            func_08013570(&data_0200918C->renderer, data_0200918C->selected,
                          data_0200918C->stride, 1);
        else
            func_08013528(&data_0200918C->renderer, data_0200918C->selected);
        if (func_08018484(data_0200918C->type))
            func_080137C0(&data_0200918C->renderer, 5);
        data_0200918C->active += 2;
        /* func_08014F10 returns NULL when no '@n' follows before the next
         * '@c' or the end.  Every type-9 message (bank 0x084C3798) ends at
         * its only '@c', so this search never runs on the game's data. */
        if (*data_0200918C->active != 0 &&
            func_08018470(data_0200918C->type)) {
            data_0200918C->selected += data_0200918C->stride << 6;
            data_0200918C->line++;
            func_08013528(&data_0200918C->renderer, data_0200918C->selected);
            data_0200918C->active =
                func_08014F10(data_0200918C->active, 'n') + 2;
        }
        break;
    case 'x':
        data_0200918C->sound_played = 1;
        data_0200918C->scale = 0x1000;
        data_0200918C->limit += 0x1000;
        data_0200918C->active += 2;
        break;
    case 'u':
        data_0200918C->scale = 0x80;
        data_0200918C->limit = 0x100;
        data_0200918C->active += 2;
        break;
    case 'a':
    case 'p':
        data_0200918C->limit = 0x80;
        if ((g_state_02000000.sound_flags & 0x18) == 8)
            data_0200918C->limit = 0x1000;
        data_0200918C->next_state = 5;
        if (data_0200918C->auto_advance) {
            data_0200918C->timer = g_state_02000000.auto_wait;
            data_0200918C->confirm_keys = 0;
            data_0200918C->status = 7;
        } else {
            if (func_080184D0(data_0200918C->type))
                data_0200918C->timer = 10;
            if (data_0200918C->active[1] == 'a')
                data_0200918C->options &= 0xfffe;
            else
                data_0200918C->options |= 1;
            if (data_0200918C->options & 1) {
                width = func_08013AAC(data_0200918C->width,
                                      data_0200918C->flags);
                data_0200918C->x = (width << 2) + (data_0200918C->left << 3);
                data_0200918C->y = ((data_0200918C->height - 1) << 3) +
                                   (data_0200918C->top << 3);
                data_0200918C->phase = 0;
            }
            g_state_020020D0.confirm_sound = 0;
            data_0200918C->status = 6;
        }
        data_0200918C->active += 2;
        return 1;
    case 'w':
        data_0200918C->busy = 1;
        data_0200918C->next_state = 5;
        data_0200918C->status = 8;
        data_0200918C->active += 2;
        return 1;
    case 'k':
        data_0200918C->auto_advance = 1;
        data_0200918C->confirm_keys = 0;
        data_0200918C->limit += 0x100;
        data_0200918C->active += 2;
        break;
    case 'y':
        text_width = func_08014778(data_0200918C->active + 2);
        func_08013728(&data_0200918C->renderer,
                      data_0200918C->stride * 8 - text_width);
        data_0200918C->limit += 0x100;
        data_0200918C->active += 2;
        break;
    case 'S':
        data_0200918C->timer = 10;
        if (func_08018484(data_0200918C->type))
            palette = 5;
        else
            palette = 0;
        length = func_080153FC(&data_0200918C->renderer,
                               data_0200918C->renderer.base,
                               data_0200918C->active, palette,
                               data_0200918C->stride);
        data_0200918C->locked = 0;
        layout = data_0200918C->active[2];
        if (!(layout & 0xf0))
            data_0200918C->locked = 1;
        data_0200918C->choice = (layout & 0xf) != 0;
        if (!data_0200918C->locked)
            data_0200918C->choice_width =
                func_08014778(data_0200918C->active + 3);
        data_0200918C->options |= 1;
        data_0200918C->phase = 0;
        data_0200918C->x = (data_0200918C->left + 1) * 8 + 3;
        data_0200918C->y = (data_0200918C->top + 1 +
                            data_0200918C->line * 2) * 8 + 4;
        if (func_0801843C(data_0200918C->type)) {
            data_0200918C->x += 0x10;
            if ((data_0200918C->options & 0x100) &&
                !(data_0200918C->flags & 0x10))
                data_0200918C->x += 0x28;
            data_0200918C->y += data_0836D630[data_0200918C->line];
        }
        if (!(data_0200918C->flags & 0xc20))
            data_0200918C->y += 8;
        data_0200918C->next_state = 5;
        data_0200918C->status = 9;
        data_0200918C->active += length;
        return 1;
    case 'l':
        palette = data_0200918C->active[2];
        if (func_0801843C(data_0200918C->type)) {
            if (palette == 0)
                palette = 5;
            else
                palette = 0;
        }
        func_080137C0(&data_0200918C->renderer, palette);
        data_0200918C->limit += 0x100;
        data_0200918C->active += 3;
        break;
    case '%':
        g_callbacks_0836D4B8[0](data_0200918C->insert, 0x40);
        skip = func_08018CEC(data_0200918C->insert, data_0200918C->active[2]);
        data_0200918C->active += 3;
        data_0200918C->pending_offset =
            data_0200918C->active - data_0200918C->text + skip;
        data_0200918C->active = data_0200918C->insert;
        data_0200918C->limit += 0x100;
        break;
    case 'g':
        func_08016070(data_0200918C->active[2], &data_0200918C->renderer,
                      data_0200918C->window, data_0200918C->stride,
                      data_0200918C->left, data_0200918C->top,
                      data_0200918C->tile, data_0200918C->flags);
        data_0200918C->limit += 0x100;
        data_0200918C->active += 3;
        break;
    case 't':
        data_0200918C->limit = 0x80;
        if ((g_state_02000000.sound_flags & 0x18) == 8)
            data_0200918C->limit = 0x1000;
        data_0200918C->timer = data_0200918C->active[2];
        data_0200918C->next_state = 5;
        data_0200918C->status = 7;
        data_0200918C->active += 3;
        return 1;
    case 'r':
        g_callbacks_0836D4B8[0](data_0200918C->insert, 0x40);
        func_0801624C(data_0200918C->insert, data_0200918C->active[2]);
        data_0200918C->active += 3;
        data_0200918C->pending_offset =
            data_0200918C->active - data_0200918C->text;
        data_0200918C->active = data_0200918C->insert;
        data_0200918C->limit += 0x100;
        break;
    case '<':
    case '>':
        amount = data_0200918C->active[2];
        if (data_0200918C->active[1] == '<')
            amount = -amount;
        data_0200918C->limit += 0x100;
        func_08013728(&data_0200918C->renderer, amount);
        data_0200918C->active += 3;
        break;
    case '!':
        if (data_0200918C->active[2] != 0)
            func_08141540(data_0200918C->active[2] + 0x93);
        data_0200918C->sound_played = 1;
        data_0200918C->active += 3;
        break;
    }
    return 0;
}
