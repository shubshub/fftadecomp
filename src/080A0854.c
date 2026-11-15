#include "ffta.h"

/* Complete [0x080A0854, 0x080A09BC): 360 bytes, 180 instructions, no literal
 * pool.
 * f0b557464e464546e0b485b084460d9c0e9d0f9e1098090412041b0424042d0436040004
 * 000c8146080c00900f14110c019112149046180c02901a14210c039124142b0c9a462d14
 * 300c04903614e01b002800da4042b11a002900da494241184346e81a0b18e41b002c00da
 * 6442b11a002900da494266184f4638040214041c93420add1198002806d1281c3038b11a
 * 401a0004000c8246131c21146514c81a40102c188c4200dd0c1c2a1a6846018860460185
 * 019d2804011418316746798569460989b9856d46ad893d86574639040914183165466986
 * 6f463f8aaf86614646310b808046002b01dc711000e05910604644300180051c60463023
 * c15e2826805f0b1a002b00da5b4267463420395e2c26b85f081a002800da4042834200db
 * 181c40102880a24209db6146483101200880474638148018083908800ce0614648310220
 * 0880404601148a1860464030028009190230018005b038bc9846a146aa46f0bc01bc0047
 */

typedef struct {
    u8 unknown_00[0x28];
    s16 start_x;
    s16 start_y;
    s16 start_z;
    u8 unknown_2E[2];
    s16 end_x;
    s16 end_y;
    s16 end_z;
    u8 unknown_36[0x0A];
    s16 heights[2];
    s16 unknown_44;
    s16 unknown_46;
    s16 count;
} Motion;

extern s32 abs(s32 value);

/* abs is the compiler builtin, expanded in line at every use.  The six entry
 * sign extensions, in parameter order, are this call's arguments; the planar
 * part is evaluated afresh for distance below rather than shared. */
static inline s32 travel_distance(s16 start_x, s16 start_y, s16 start_z,
                                  s16 end_x, s16 end_y, s16 end_z)
{
    return abs(end_x - start_x) + abs(end_z - start_z) + (end_y - start_y);
}

void func_080A0854(Motion *motion, s16 start_x, s16 start_y, s16 start_z,
                   s16 end_x, s16 end_y, s16 end_z, s16 limit,
                   s32 keep_end_height, s32 reversed)
{
    s32 travel;
    s32 distance;
    s32 half;
    s32 slack;
    s32 upper;
    s32 lower;
    s32 dx;
    s32 dz;

    travel = travel_distance(start_x, start_y, start_z, end_x, end_y, end_z);
    distance = abs(end_x - start_x) + abs(end_z - start_z);
    if (travel > limit) {
        if (keep_end_height == 0)
            end_y -= distance - limit + 48;
        travel = limit;
    }
    half = limit >> 1;
    slack = (limit - travel) >> 1;
    upper = half + slack;
    if (upper > limit)
        upper = limit;
    lower = half - slack;

    motion->start_x = start_x;
    motion->start_y = start_y + 24;
    motion->start_z = start_z;
    motion->end_x = end_x;
    motion->end_y = end_y + 24;
    motion->end_z = end_z;
    motion->unknown_46 = travel;
    if (travel <= 0)
        motion->unknown_44 = distance >> 1;
    else
        motion->unknown_44 = travel >> 1;

    dx = abs(motion->end_x - motion->start_x);
    dz = abs(motion->end_z - motion->start_z);
    if (dx >= dz)
        dz = dx;
    motion->unknown_44 = dz >> 1;

    if (lower >= upper) {
        motion->count = 1;
        motion->heights[0] = start_y + lower;
    } else {
        motion->count = 2;
        motion->heights[0] = start_y + lower;
        motion->heights[1] = start_y + upper;
    }
}
