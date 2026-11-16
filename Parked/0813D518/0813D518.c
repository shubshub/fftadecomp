#include "ffta.h"
#include "control_flags.h"

// Target: complete [0x0813D518, 0x0813D6A0), 392 bytes.
// f0b557464e464546e0b484b0002082468146002615498846154a1468154be0188019
// 0078002800d19de0134af300981b8000851817216956012040421f1c81421ed1b819
// 00010d49401820180822a95e0a23ea5e2b7d00240094ac7c0194ec7c02946c7d0394
// 00f057fd49e040090003b0f300026c8b000058903a080480000017202856002802d0
// 012809d015e044466089298b40180004000c8246a08907e04346d8892c8b00190004
// 000c8246188a6d8b40190004000c8146b91909011f4809181f4b18684018bd1bad00
// ad182989544622041214891a090409146a894c4623041b14d21a120412142b7d0024
// 0094ac7c0194ec7c02946c7d039400f00cfd0f4d2c6871000f4aa018421813889c46
// 0020115e0c4b1814814219d1b819000106494018201801f0ddfb000600281ad02868
// 064a80188019002113e004800000b0f30002448b00000000ffff6c8b000060460138
// 002110800004002803d1094be01880190170701c0006060e132e00d852e704b038bc
// 9846a146aa46f0bc01bc004700006c8b0000

typedef struct {
    u16 image_index;
    u16 duration;
} Frame0813D518;

typedef struct {
    u16 count;
    u16 unknown_02;
    const Frame0813D518 *frames;
} Track0813D518;

typedef struct {
    const u32 *resource;
    u32 unknown_04;
    Track0813D518 tracks[10];
    u16 count;
    u16 timers[10];
    u16 frame_indices[10];
    u8 finished[10];
    u8 playback_mode;
} Animation0813D518;

typedef struct {
    const void *first;
    const void *second;
    s16 x;
    s16 y;
    const void *third;
    u16 id;
    u8 palette;
    u8 draw_mode;
    u8 priority;
    u8 flags;
    u8 mode;
    s8 reference;
    u16 reference_x;
    u16 reference_y;
} Definition;

typedef struct {
    u8 unknown_00[0x8004];
    Animation0813D518 entries[20];
    u16 ids[20];
    u8 active[20];
} DisplayState;

extern DisplayState *data_0200F3B0;
extern const Definition data_083A9058[];
extern void func_0813E030(Animation0813D518 *animation, s16 x, s16 y,
                          u8 priority, u16 tile_base, u8 palette,
                          u8 draw_mode, u8 flags);
extern u32 func_0813EDFC(const Animation0813D518 *animation);

void func_0813D518(void)
{
    s16 reference_x = 0;
    s16 reference_y = 0;
    u8 index;

    for (index = 0; index < 20; index++) {
        if (data_0200F3B0->active[index]) {
            if (data_083A9058[index].reference == -1) {
                func_0813E030(&data_0200F3B0->entries[index],
                              data_083A9058[index].x,
                              data_083A9058[index].y,
                              data_083A9058[index].priority, 0,
                              data_083A9058[index].palette,
                              data_083A9058[index].draw_mode,
                              data_083A9058[index].flags);
            } else {
                switch (data_083A9058[index].reference) {
                case 0:
                    reference_x = data_083A9058[index].reference_x +
                        g_control_flags_03000940.bg0hofs;
                    reference_y = data_083A9058[index].reference_y +
                        g_control_flags_03000940.bg0vofs;
                    break;
                case 1:
                    reference_x = data_083A9058[index].reference_x +
                        g_control_flags_03000940.bg1hofs;
                    reference_y = data_083A9058[index].reference_y +
                        g_control_flags_03000940.bg1vofs;
                    break;
                }
                func_0813E030(&data_0200F3B0->entries[index],
                              data_083A9058[index].x - reference_x,
                              data_083A9058[index].y - reference_y,
                              data_083A9058[index].priority, 0,
                              data_083A9058[index].palette,
                              data_083A9058[index].draw_mode,
                              data_083A9058[index].flags);
            }

            if ((s16)data_0200F3B0->ids[index] == -1) {
                if ((u8)func_0813EDFC(&data_0200F3B0->entries[index]))
                    data_0200F3B0->active[index] = 0;
            } else {
                if (--data_0200F3B0->ids[index] == 0)
                    data_0200F3B0->active[index] = 0;
            }
        }
    }
}
