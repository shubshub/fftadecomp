#include "ffta.h"

typedef struct {
    u16 shown : 1;
    u16 unknown_01 : 6;
    u16 mode : 2;
    u16 unknown_09 : 7;
    u8 unknown_02[0xA];
    u16 scroll;
} MarkerCursor;

typedef struct {
    u8 unknown_00;
    u8 flags;
    u8 count;
    u8 record;
    u8 unknown_04[8];
} MarkerEntry;

typedef struct {
    u8 unknown_00[0xB0];
    MarkerEntry entries[30];
} MarkerMap;

typedef struct {
    u8 x;
    u8 y;
    u8 unknown_02[18];
} MarkerRecord;

typedef struct {
    MarkerMap *map;
    MarkerCursor *cursor;
    u8 unknown_08[0x674];
    MarkerRecord *records;
    u8 unknown_680[5];
    u8 effect;
    u8 target;
    u8 repeat;
    u8 timer;
} MarkerState;

typedef struct {
    u32 unknown_00;
    Entry *sprites;
} MarkerRender;

typedef struct {
    u8 base;
    u8 unknown_01[3];
} MarkerFrame;

extern MarkerState *g_state_03002810;
extern MarkerRender data_03000E30;
extern const MarkerFrame data_08391CA4[];
extern const s8 data_08391878[];
extern const u8 data_08950000[];
extern const u8 data_08950F4C[];
extern void func_0803687C(u32 mode);
extern void func_08036B18(u32 mode);
extern void func_08141520(u16 value);
extern u32 func_08002804(void);
extern void func_0804C4D4(Entry *, u16, u16, u8, u8, u8, u8,
                         const u8 *, const u8 *, u16);

// Complete target: [0x0803701C, 0x080372FC), 736 bytes.
void func_0803701C(u32 animate)
{
    s32 i;

    if (g_state_03002810->cursor->shown)
        func_0803687C(0);
    else if (g_state_03002810->cursor->mode)
        func_08036B18(g_state_03002810->cursor->mode);

    for (i = 0; i < 30; i++) {
        MarkerEntry *entry = &g_state_03002810->map->entries[i];
        u8 flags = entry->flags;
        u8 base;
        u8 frame;
        s32 y;
        u32 px;
        u32 py;

        if (!(flags & 1))
            continue;

        base = data_08391CA4[i].base - 1;
        if (animate) {
            u8 count = entry->count;
            if (flags & 2) {
                /* The ROM keeps the count < 10 test (cmp r2, #9; bhi at
                 * 0x080370A4) and both arms (0x080370A8, 0x080370B8). */
                if (count == 0)
                    frame = base + 2;
                else if (count < 10)
                    frame = base + 18;
                else
                    frame = base + 18;
            } else {
                frame = base + 10;
            }
        } else {
            frame = base + 2;
        }

        y = g_state_03002810->records[entry->record - 1].y * 8 - g_state_03002810->cursor->scroll;
        py = y + 17;
        if ((u32)(y + 16) <= 188) {
            px = g_state_03002810->records[entry->record - 1].x * 8;
        } else {
            py = 240;
            px = 240;
        }

        if (g_state_03002810->effect && i == g_state_03002810->target) {
            u8 delay = 0;

            switch (g_state_03002810->effect) {
            case 1:
                /* Stored again here: 0x0803715C. */
                delay = 0;
                if (g_state_03002810->timer == 28)
                    func_08141520(222);
                if (g_state_03002810->timer < 48)
                    py += data_08391878[g_state_03002810->timer++];
                break;
            case 5:
                delay = 2;
                if (g_state_03002810->timer > 20)
                    py = 240;
                if (g_state_03002810->timer < 28)
                    g_state_03002810->timer++;
                else
                    g_state_03002810->timer = 0;
                break;
            case 2:
                delay = 2;
                px += (s16)func_08002804() % 6 - 3;
                py += (s16)func_08002804() % 6 - 3;
                break;
            case 3: {
                s32 step;
                s32 phase;

                /* delay is stored between the timer update and the
                 * remainder (0x0803720E). */
                step = g_state_03002810->timer++ >> 3;
                delay = 2;
                phase = step % 3;
                if (phase == 0)
                    frame = base + 2;
                else if (phase == 1)
                    frame = base + 10;
                else
                    frame = base + 18;
                break;
            }
            case 4:
                break;
            }
            func_0804C4D4(data_03000E30.sprites, (u16)(i + 19), frame, px, py, 0, delay,
                          data_08950000, data_08950F4C, 0x52);
            if (g_state_03002810->effect != 5) {
                if (g_state_03002810->repeat == 0)
                    g_state_03002810->effect = 0;
                else
                    g_state_03002810->repeat--;
            }
        } else {
            func_0804C4D4(data_03000E30.sprites, (u16)(i + 19), frame, px, py, 0, 2,
                          data_08950000, data_08950F4C, 0x52);
        }
    }
}
