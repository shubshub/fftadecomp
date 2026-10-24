#include "ffta.h"

typedef struct {
    u8 flags;
    u8 unknown_01[0x0E];
    u8 field_0f;
    u8 unknown_10[3];
    u8 field_13;
    u8 unknown_14[5];
    u8 field_19;
    u8 unknown_1a[0x0A];
    u8 field_24;
    u8 unknown_25[0x2B];
} Track081453B0;

typedef struct {
    u8 unknown_00[8];
    u8 track_count;
    u8 unknown_09[0x23];
    Track081453B0 *tracks;
} State081453B0;

extern void func_08145528(void *object);

/* 0x081453B0 - 72 bytes.
 * Target: f0b5057ac46a002d1bdd80272178381c0840002811d04026301c084000280cd0201c
 * 00f0a9f827700220e073e67416206076211c243101200870013d5034002de4dcf0bc01bc0047
 */
void func_081453B0(State081453B0 *state)
{
    int remaining = state->track_count;
    Track081453B0 *track = state->tracks;

    while (remaining > 0) {
        if ((track->flags & 0x80) && (track->flags & 0x40)) {
            func_08145528(track);
            track->flags = 0x80;
            track->field_0f = 2;
            track->field_13 = 0x40;
            track->field_19 = 0x16;
            track->field_24 = 1;
        }
        remaining--;
        track++;
    }
}
