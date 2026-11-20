#ifndef GUARD_MOVEMENT_TILE_H
#define GUARD_MOVEMENT_TILE_H

#include "object_list.h"

typedef struct {
    u32 value : 7;
    u32 enabled : 1;
    u32 mode : 4;
    u32 flag4 : 1;
    u32 flag5 : 1;
    u32 flag6 : 1;
    u32 unknown_flag : 1;
    u8 direction : 7;
    u8 valid : 1;
    u8 unknown_3;
    u8 unknown_4;
    u8 unknown_5;
    u8 unknown_6;
} __attribute__((packed)) PathGrid;

typedef struct {
    u8 unknown_00[0xF6];
    u8 x;
    u8 y;
    u8 unknown_F8[5];
    u8 movement;
} MovementUnit;

typedef struct {
    u8 unknown_00[0x10];
    ListContext *objects;
} Scene;

typedef struct Actor {
    MovementUnit *unit;
    u8 unknown_04[0x16];
    u8 phase;
    u8 range;
    u8 unknown_1C[0x20];
    PathGrid *grid;
    u8 unknown_40[0x40];
    Scene *scene;
} Actor;

typedef struct {
    u8 unknown_00[4];
    s8 x;
    s8 y;
    u8 unknown_06[2];
    Actor *match;
} TileSearch;

u32 func_08149384(PathGrid *grid, u8 x, u8 y);
u8 func_081493AC(PathGrid *grid, u8 x, u8 y);
s32 func_08097504(Actor *actor, s8 x, s8 y, u8 range);
u32 func_0809ABB0(ListNode *node, void *payload);
s32 func_08099FB0(Actor *actor, s32 x, s32 y);

#endif
