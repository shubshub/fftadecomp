#include "battle_position_search.h"

typedef void (*Clear)(void *, u32);
extern Clear const g_callbacks_0836D4B8[];
extern void *func_08022840(u32 size);
struct SceneObject08099544;
extern struct SceneObject08099544 *func_08099544(struct ObjectContext08099544 *context);
extern u8 func_080CD944(Unit *unit);
extern u32 func_080CCD50(u16 action, u8 field);
extern s32 func_0812F0D8(const void *unit, u16 *items);
extern u8 func_0812EE98(void *unit, u16 item);
/* Complete [0x080C01D0, 0x080C034C), 380 bytes. */
PositionEvaluator func_080C01D0(PositionSearch *state, BattleUnit *source, BattleUnit *target,
                        void *group, void *other_group, BattleAction *selection,
                        u8 side, u8 *map, u8 alternate)
{
    u16 items[2];
    s32 uses_equipment;

    g_callbacks_0836D4B8[0](state, sizeof(*state));
    state->actor = source;
    state->target = target;
    state->action = selection->action;
    state->unit_value = selection->parameter;
    state->selection = selection;
    state->map = map;
    state->group = group;
    state->other_group = other_group;
    state->side = side;
    state->positions = func_08022840(1024);
    state->small_buffer = func_08022840(256);
    if (alternate)
        state->flags |= 4;
    if (func_08099544(source->collection) && !func_080CD944(&source->unit->flag_record))
        state->flags |= 2;

    uses_equipment = 0;
    if (state->action) {
        if (state->action == 0x109)
            return func_080BF5A4;
        if (func_080CCD50(state->action, 4) & 0x80)
            uses_equipment = 1;
        if (!uses_equipment)
            goto ability;
    }
    state->flags |= 1;
    func_0812F0D8(source->unit, items);
    switch (func_0812EE98(source->unit, items[0])) {
    case 13:
    case 14:
    case 19:
        return func_080BF7C4;
    default:
        return func_080BFDB0;
    }
ability:
    switch (func_080CCD50(state->action, 6)) {
    case 4:
    case 6:
    case 7:
        return func_080BFDB0;
    }
    if (func_080CCD50(state->action, 4) & 0x40)
        return func_080BFDB0;
    if (source == target)
        return func_080BEAC8;
    return func_080BEF28;
}
