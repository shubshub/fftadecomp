#include "ffta.h"

/* func_08020A68 - complete [0x08020A68, 0x08020B9E): 310 bytes, 152 instructions.
 * Target:
 *   f0b557464e464546e0b400260027002084461d498a46012291462c2061464143
 *   081c0430524611680a181078002873d0d1890220084000286ed1108980465478
 *   002c01d0012c01d11669b77850880138002550800004002859d10b1c04201840
 *   002816d01079011cff2909d000290dd14846184000281fd05179081cff2819d1
 *   781e10711ae00000d4f100020138107114e01079013010710006000eb8420dd1
 *   48460840002807d05179081cff2801d1157103e0117101e015702de0002c01d0
 *   012c07d110798000301801794079000208435080002090815069d061002c02d0
 *   012c09d013e01079800030188179c07900020843400107e01079800030188179
 *   c0790002084340009169091811629089404501d049469171604601300006000e
 *   8446032800d878e738bc9846a146aa46f0bc01bc0047
 *
 * Steps the four animation slots.  Kind 0 slots are made by func_08020DA0 and
 * their frame offsets count 32-byte units; kind 1 slots are made by
 * func_08020E3C and their frame offsets count 2-byte units.  The ROM tests the
 * two kinds one at a time in all three dispatches (cmp #0, cmp #1), as it does
 * for the repeated cases of func_0800D7B4.
 */
typedef struct {
    u8 duration_low;
    u8 duration_high;
    u8 offset_low;
    u8 offset_high;
} AnimationFrame08020A68;

typedef struct {
    u8 unknown_00[2];
    u8 frame_count;
    u8 unknown_03;
    AnimationFrame08020A68 frames[1];
} AnimationResource08020A68;

typedef struct {
    u8 active;
    u8 kind;
    u16 duration;
    u8 frame;
    u8 restart_frame;
    u8 unknown_06;
    u8 unknown_07;
    u16 size;
    u16 start_tick;
    u16 elapsed;
    u16 flags;
    const AnimationResource08020A68 *resource;
    void *destination;
    const u8 *source;
    void *current_destination;
    const u8 *current_source;
    u8 unknown_24[8];
} AnimationSlot08020A68;

typedef struct {
    u16 tick;
    u16 unknown_02;
    AnimationSlot08020A68 slots[4];
} AnimationState08020A68;

extern AnimationState08020A68 *g_state_0200F1D4;

void func_08020A68(void)
{
    const AnimationResource08020A68 *resource = 0;
    u8 frame_count = 0;
    u8 index;

    for (index = 0; index < 4; index++) {
        AnimationSlot08020A68 *slot = &g_state_0200F1D4->slots[index];
        u16 size;
        u8 kind;

        if (!slot->active)
            continue;
        if (slot->flags & 2)
            continue;
        size = slot->size;
        kind = slot->kind;
        switch (kind) {
        case 0:
            resource = slot->resource;
            frame_count = resource->frame_count;
            break;
        case 1:
            resource = slot->resource;
            frame_count = resource->frame_count;
            break;
        }

        if (--slot->duration == 0) {
            if (slot->flags & 4) {
                if (slot->frame == 0xff) {
                    slot->frame = frame_count - 1;
                } else if (slot->frame == 0) {
                    if (slot->flags & 1) {
                        if (slot->restart_frame == 0xff)
                            slot->frame = frame_count - 1;
                        else
                            slot->frame = slot->restart_frame;
                    } else {
                        slot->active = 0;
                        continue;
                    }
                } else {
                    slot->frame--;
                }
            } else {
                if (++slot->frame == frame_count) {
                    if (slot->flags & 1) {
                        if (slot->restart_frame == 0xff)
                            slot->frame = 0;
                        else
                            slot->frame = slot->restart_frame;
                    } else {
                        slot->active = 0;
                        continue;
                    }
                }
            }

            switch (kind) {
            case 0:
                {
                    u32 low = resource->frames[slot->frame].duration_low;
                    u32 high = resource->frames[slot->frame].duration_high;
                    slot->duration = (high << 8) | low;
                }
                break;
            case 1:
                {
                    u32 low = resource->frames[slot->frame].duration_low;
                    u32 high = resource->frames[slot->frame].duration_high;
                    slot->duration = (high << 8) | low;
                }
                break;
            }
            slot->elapsed = 0;
            slot->current_destination = slot->destination;
            switch (kind) {
            case 0:
                {
                    u32 low = resource->frames[slot->frame].offset_low;
                    u32 high = resource->frames[slot->frame].offset_high;
                    slot->current_source = slot->source + (((high << 8) | low) << 5);
                }
                break;
            case 1:
                {
                    u32 low = resource->frames[slot->frame].offset_low;
                    u32 high = resource->frames[slot->frame].offset_high;
                    slot->current_source = slot->source + (((high << 8) | low) << 1);
                }
                break;
            }
        }
        if (slot->elapsed != size)
            slot->unknown_06 = 1;
    }
}
