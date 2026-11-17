#include "ffta.h"

/* Complete [0x080BE7AC, 0x080BE8E0): 308 bytes, 154 instructions.
 * f0b557464e464546e0b48bb080461d1c09060f0e1206140e0020824641460868006802a9
 * 70f082fc03a842461168096803911189018102a909884181077144718771c471002101222b1c
 * f6f711f9011c002902dc0120404262e08a4525da200600160990139e3f06b946880028180a90
 * 0c1c002169560122aa56099f00970a98019040464f463b16fff7defe011c002907dd28783070
 * 6878707071600836012082440435013c002ce3d15146012936dd5246013a08920024944230da
 * 671cb846d04528dae00013994618194a914606af4146c800139a84185046451a71686068814214
 * da49460b68381c311c082283f0d9fc4a461368301c211c082283f0d2fc48460368201c391c0822
 * 83f0cbfc0834013d002de2d1444608998c42cedb50460bb038bc9846a146aa46f0bc02bc0847
 * bcd43608 */

typedef void (*BufferCopier)(void *destination, const void *source, u32 size);

typedef struct {
    void *unit;
} Owner080BE7AC;

typedef struct {
    Owner080BE7AC *owner;
    u8 unknown_04[4];
    u16 identifier;
} Actor080BE7AC;

typedef struct {
    void *unit;
    s8 x;
    s8 y;
    s8 end_x;
    s8 end_y;
    u16 first;
    u16 second;
} RangeRequest;

typedef struct {
    s8 x;
    s8 y;
    u8 unknown_02[2];
} Tile080BE7AC;

typedef struct {
    s8 x;
    s8 y;
    u8 unknown_02[2];
    s32 score;
} Result080BE7AC;

extern BufferCopier data_0836D4BC[];
extern s32 func_0812F0D8(const void *object, u16 *entries);
extern int func_080B4A1C(RangeRequest *request, u8 direction, u8 mode,
                         Tile080BE7AC *output);
extern s32 func_080BE5F4(Actor080BE7AC *actor, s8 x, s8 y, s8 target_x,
                         s8 target_y, Tile080BE7AC *tiles);

s32 func_080BE7AC(Actor080BE7AC *actor, u8 x, u8 y, Tile080BE7AC *tiles,
                  Result080BE7AC *results)
{
    u16 entries[2];
    RangeRequest request;
    Result080BE7AC swap;
    s32 found;
    s32 total;
    s32 score;
    s32 i;
    s32 j;
    s32 last;

    found = 0;
    func_0812F0D8(actor->owner->unit, entries);
    request.unit = actor->owner->unit;
    request.first = actor->identifier;
    request.second = entries[0];
    request.x = x;
    request.y = y;
    request.end_x = x;
    request.end_y = y;
    total = func_080B4A1C(&request, 0, 1, tiles);
    if (total <= 0)
        return -1;

    for (i = 0; i < total; i++) {
        score = func_080BE5F4(actor, tiles[i].x, tiles[i].y, x, y,
                              tiles + total);
        if (score > 0) {
            results[found].x = tiles[i].x;
            results[found].y = tiles[i].y;
            results[found].score = score;
            found++;
        }
    }

    /* The ROM keeps this test (cmp #1; ble at 0x080BE858) ahead of the
     * sort's own entry test (0x080BE864); both exits return found. */
    if (found <= 1)
        return found;

    last = found - 1;
    for (i = 0; i < last; i++) {
        for (j = i + 1; j < found; j++) {
            if (results[i].score < results[j].score) {
                data_0836D4BC[0](&swap, &results[i], sizeof(swap));
                data_0836D4BC[0](&results[i], &results[j], sizeof(swap));
                data_0836D4BC[0](&results[j], &swap, sizeof(swap));
            }
        }
    }
    return found;
}
