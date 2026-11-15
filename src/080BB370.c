#include "ffta.h"

/* Complete [0x080BB370, 0x080BB424): 180 bytes, 90 instructions, no literal
 * words.
 * 30b5021c141c0c34a168d0680b1a002b00da5b42e1686068091a002900da49428b4200db
 * 191c081c002900da0f30011180256d00a94200dc291ca161141c2834a168906a0b1a002b
 * 00da5b42e1686068091a002900da49428b4200db191c081c002900da0f300111a94200dc
 * 291ca161506aa84204dc106ca84201dc00201072507a013050720006001603280fdd0020
 * 5072106a01301062642801dd64201062d06b0130d063642801dd6420d06330bc01bc0047
 */

/* The entry and motion layouts of src/080BB424.c, which calls this function
 * for every entry with flags bit 0 set and then steps both motions with
 * func_08007AD0.  That file leaves +9 unknown; this function counts it as a
 * signed byte. */
typedef struct Motion080BB370 {
    s32 target_x;
    s32 target_y;
    s32 current_x;
    s32 current_y;
    s32 angle;
    s32 turn_percent;
    s32 speed;
} Motion080BB370;

typedef struct Entry080BB370 {
    u8 angle;
    u8 angle_step;
    s16 x;
    s16 z;
    s16 y;
    u8 flags;
    s8 timer;
    u8 unknown_0A[2];
    Motion080BB370 horizontal;
    Motion080BB370 vertical;
} Entry080BB370;

/* The ROM holds this body twice, once per motion, each copy addressing its
 * motion through r4 (set at 0x080BB374 and 0x080BB3AC); no out-of-line copy
 * was found in the ROM.  The speed is a sixteenth of the larger remaining
 * distance, never below 256. */
static inline void update_speed(Motion080BB370 *motion)
{
    s32 dx = motion->current_x - motion->target_x;
    s32 dy;
    s32 speed;

    if (dx < 0)
        dx = -dx;
    dy = motion->current_y - motion->target_y;
    if (dy < 0)
        dy = -dy;
    if (dx >= dy)
        speed = dx;
    else
        speed = dy;
    speed /= 16;
    if (speed <= 256)
        speed = 256;
    motion->speed = speed;
}

/* Recompute both speeds, clear the flags once both are at the minimum, and
 * raise both turn percentages, to at most 100, on every fourth call. */
void func_080BB370(Entry080BB370 *entry)
{
    update_speed(&entry->horizontal);
    update_speed(&entry->vertical);

    if (entry->horizontal.speed <= 256 && entry->vertical.speed <= 256)
        entry->flags = 0;

    entry->timer++;
    if (entry->timer > 3) {
        entry->timer = 0;
        entry->horizontal.turn_percent++;
        if (entry->horizontal.turn_percent > 100)
            entry->horizontal.turn_percent = 100;
        entry->vertical.turn_percent++;
        if (entry->vertical.turn_percent > 100)
            entry->vertical.turn_percent = 100;
    }
}
