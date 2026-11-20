#ifndef GUARD_BATTLE_POSITION_SEARCH_H
#define GUARD_BATTLE_POSITION_SEARCH_H

#include "ffta.h"

struct ObjectContext08099544;

typedef struct {
    u8 unknown_00[0xE8];
    u8 flags;
} Unit;

typedef struct {
    Unit flag_record;
    u8 unknown_after_flags[0xF6 - sizeof(Unit)];
    u8 x;
    u8 y;
    u8 direction;
} PositionedUnit;

typedef struct {
    PositionedUnit *unit;
    u8 unknown_04[0x7C];
    struct ObjectContext08099544 *collection;
} BattleUnit;

typedef struct {
    u16 action;
    u16 parameter;
} BattleAction;

typedef struct {
    u8 x;
    u8 y;
    u8 height;
    u8 unknown_03;
} Position;

typedef struct {
    BattleUnit *actor;
    BattleUnit *target;
    u16 action;
    u16 unit_value;
    void *group;
    void *other_group;
    BattleAction *selection;
    u8 unknown_18[0x10];
    u8 side;
    u8 unknown_29[0x183];
    u8 start_x;
    u8 start_y;
    u8 end_x;
    u8 end_y;
    u8 direction;
    u8 has_position;
    u8 has_candidate;
    u8 candidate_x;
    u8 candidate_y;
    u8 candidate_end_x;
    u8 candidate_end_y;
    u8 unknown_1B7;
    u16 status;
    u8 unknown_1BA[0x46];
    void *small_buffer;
    Position *positions;
    u8 unknown_208[4];
    s16 count;
    u8 unknown_20E[6];
    u8 *map;
    u8 flags;
} PositionSearch;

typedef u32 (*PositionEvaluator)(PositionSearch *, void *);
u32 func_080BEAC8(PositionSearch *search, void *work);
u32 func_080BEF28(PositionSearch *search, void *work);
u32 func_080BF5A4(PositionSearch *search, void *work);
u32 func_080BF7C4(PositionSearch *search, void *work);
u32 func_080BFDB0(PositionSearch *search, void *work);

#endif
