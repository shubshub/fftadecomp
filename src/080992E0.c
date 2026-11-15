#include "ffta.h"

/* Complete target [0x080992E0, 0x080993F4): 276 bytes, 127 instructions.
 * f0b557464e464546e0b481b000908846bc277f004744464684364546803517208146aa46
 * 3078002821d0b18c0120084000281cd020200840002818d180225200101c08400004040c
 * 002c10d1281c2ff0c7f80006002806d0387801380006000e012800d83c7000985146f9f7
 * 79f8842040003f1836182d1801225242914448460028ceda204f4744204e4644204d4544
 * 0b229146a8463078002821d0b18c0120084000281cd020200840002818d180225200101c
 * 08400004040c002c10d1281c2ff08ef80006002806d0387801380006000e012800d83c70
 * 00984146f9f740f8842040003f1836182d1801225242914448460028ceda01b038bc9846
 * a146aa46f0bc01bc00470000bc300000c82f0000c42f0000
 */

typedef struct {
    u8 unknown_00[4];
    u8 active;
    u8 unknown_05[0x23];
    u16 flags;
    u8 unknown_2A[0xCE];
    u8 facing;
    u8 unknown_F9[0x0F];
} SceneRecord;

typedef struct {
    u8 unknown_00[0x80];
    SceneRecord first[24];
    u8 unknown_1940[0x1684];
    SceneRecord second[12];
} SceneState;

extern u8 func_080C84C0(const void *object);
extern void *func_08092440(void *context, SceneRecord *record);

/* The body both loops run on a record. The ROM holds two expansions of it
 * (0x08099302 and 0x08099374) and no out-of-line copy. */
static inline void show_record(void *context, SceneRecord *record)
{
    if (record->active == 0)
        return;
    if (!(record->flags & 1))
        return;
    if (record->flags & 0x20)
        return;
    if (record->flags & 0x100)
        return;
    if (func_080C84C0(record) && (record->facing == 1 || record->facing == 2))
        record->facing = 0;
    func_08092440(context, record);
}

void func_080992E0(void *context, SceneState *scene)
{
    s32 i;

    for (i = 0; i < 24; i++)
        show_record(context, &scene->first[i]);
    for (i = 0; i < 12; i++)
        show_record(context, &scene->second[i]);
}
