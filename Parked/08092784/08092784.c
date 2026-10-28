#include "ffta.h"

/* Complete target [0x08092784, 0x08096B2C): 17320 bytes, 7226 reachable instructions. */
typedef struct Unit Unit;
typedef struct { s32 x:16; s32 z:16; s32 y:16; s32 unknown_06:16; } MapPosition;
typedef struct { Unit *unit; u8 target; s8 delay; s8 ticks; } TurnState;
struct Unit {
    u8 *record;
    u32 unknown_04;
    s16 x, z, y;
    u8 unknown_0e[0x10];
    u8 kind;
    s8 direction;
    u8 unknown_20[0x10];
    u32 appearance;
    u8 unknown_34[4];
    s16 height;
    u16 unknown_3a;
    void *render;
    u8 unknown_40[0x14];
    void *animation, *secondary_animation;
    u8 unknown_5c[0x24];
    void *unknown_80;
};
typedef struct {
    Unit *actor, *current, *other;
    u8 unknown_0c[0x34];
    Unit *tracking;
    void *effect;
    void *ability_effect, *chain_effects[2], *effect_result, *effect_list;
    void *motion;
    void *ability_menu, *outcome_menu, *transition;
    void *text;
    void *notice;
    void *menu, *unit_menu;
    void *special_menu, *system_menu;
    TurnState turn, tracking_turn;
    void *dialog;
    s16 selection, selection2, selection3;
    u16 unknown_9e;
    void *message;
    u16 message_id, ability, ability_argument, chain_ability[2];
    u8 chain_index, unknown_af, variant, unknown_b1, auxiliary, unknown_b3[3];
    u8 sound, saved_modes[16], saved_mode_count, action;
    s8 target_x, target_y;
    s8 chain_x[2], chain_y[2];
    u8 unknown_cf;
    u32 flags;
    u8 saved_x, saved_y;
    s8 delay, wait;
    s8 frame_delay;
    u8 unknown_d9[3];
    u16 state, state_count, states[34];
    u8 path[32][4];
    u32 path_count;
    s32 saved_height;
    s8 step;
    u8 timer, unknown_1ae[2];
    void *sub_menu;
    u32 saved_random;
} ActionState;
typedef struct {
    u8 unknown_00[2], mode, unknown_03[0x23];
    u8 position_changed, unknown_27;
    MapPosition position, destination;
    u8 unknown_38[0x5c];
    u16 flags;
} MapControl;
typedef struct { Unit *unit; s8 x, y; u8 unknown_06[0x4e]; } SelectionState;
extern MapControl g_state_0200F390;
extern u8 g_state_02000000[], g_state_02000080[], data_030028A0[];
extern u8 data_0200F3AC[], data_0200F3B8[], data_0200F4C0[], data_0200F6A0[];
extern u8 g_table_0854CD54[][40];
extern void (*data_0839403C)(void *);
extern void (*data_08394054)(void *, u32);
extern void (*g_callbacks_0836D4B8)(void *, u32);

#define SAVE_STATE() (s->states[s->state_count++] = s->state)
#define POP_STATE() (s->state = s->states[--s->state_count])

extern u32 *func_08002830(void);
extern void func_08004C40(void), func_08005028(void), func_08009FD0(void);
extern void func_08009AFC(u16);
extern u8 func_08009FBC(void);
extern u16 func_0800A018(void), func_0800A024(void), func_08011860(void);
extern u32 func_0800A5C8(u32);
extern s8 func_08013380(void);
extern u8 func_0801CC18(u8,u8), func_0801CC7C(u8,u8), func_0801D8B8(void);
extern void func_0801D624(u8,u8,u8),func_0801D918(void),func_0801D938(void);
extern void *func_08021854(void *,u32);
extern u32 func_0802192C(void *,u32);
extern void func_0802200C(void *);
extern void *func_08022840(u32);
extern void func_08022854(void *),func_080230A8(void),func_080231AC(void);
extern void func_08024ABC(void *,u8),func_0802542C(u8),func_08025448(u8);
extern s32 func_08025464(void),func_080254A0(void),func_08025560(void);
extern u32 func_08025584(void),func_080294D8(void);
extern void func_080255FC(u32),func_08025688(u32,u16,u32),func_080294E4(void *);
extern void *func_080294FC(void);
extern void func_08029514(void),func_08029544(u32),func_0802966C(void);
extern void *func_0802B70C(void *,u32),*func_0802D72C(u8);
extern u8 func_0802B880(void *);
extern void func_0802D704(void *);
extern void func_0808F848(void *);
extern void *func_0808F8E8(void *);
extern u32 func_0808FA98(void *,u16,u16);
extern void func_080917F8(void *);
extern void *func_0809185C(u32),*func_08091DC0(void);
extern u32 func_08091930(void *,u16,u16),func_08091E48(void *),func_080922A4(void *);
extern void func_08092288(void *),func_080922C4(void *);
extern void func_080922CC(void *,s16,s16,s16,s16,s16,u32,u32);
extern u32 func_08092390(void *);
extern u8 func_080924F4(void *,void *);
extern u32 func_080925A4(void *);
extern void func_08092638(void *,u8,u8);
extern void *func_08096D7C(void);
extern void func_08096F8C(void *),func_08098130(void *),func_0809836C(void *,u32,s8,u32);
extern u32 func_08098A88(void *);
extern Unit *func_08099544(void *),*func_08099560(void *),*func_08099644(void *,s8,s8);
extern void func_0809993C(void *,u8),func_08099A70(void *,void *);
extern void *func_08099C30(void *);
extern s32 func_08099CDC(void *,Unit **);
extern void func_08099E68(void *,s8,s8),func_08099EA0(void *),func_08099F00(void *);
extern u32 func_08099FB0(void *,s8,s8),func_0809A204(void *);
extern void func_0809A260(void *,u32),func_0809A5C0(void *,u8),func_0809A5E0(void *,u8,void *);
extern s32 func_0809A604(void *,u8,u8,u8,void *);
extern void func_0809A624(void *),func_0809A63C(void *,u8),func_0809A664(void *,u8),func_0809A710(void *);
extern u32 func_0809A900(void *);
extern void func_0809A950(void *,s32),func_0809A9A8(void *),func_0809A9CC(void *);
extern Unit *func_0809AA38(void *,u8);
extern void func_0809B818(void *);
extern s32 func_0809B88C(void *),func_0809CAF4(void);
extern u32 func_0809D3A8(TurnState *),func_0809D464(void *,void *,void *,u32),func_0809D614(void *);
extern void func_0809D620(Rec5 *,u16,u16,u16,u16),func_0809D638(void *,u8);
extern s32 func_0809D640(void *,void *);
extern u32 func_0809D6BC(s8,s8);
extern void func_0809D7E4(void *,u32,s16,s16);
extern u8 func_0809D8F0(void *);
extern Unit *func_0809F850(void *);
extern void func_0809F8EC(void *);
extern void *func_0809F9A8(void *);
extern u8 func_0809F9C0(void *);
extern void func_0809F9D0(void *);
extern s32 func_0809F9D8(void *);
extern void *func_080A7138(void *,void *);
extern void func_080A80C8(void *);
extern void *func_080A8194(void *,u16,u16,u8,u8,u8,u8);
extern void func_080A8264(void *);
extern u32 func_080A8270(void *);
extern void func_080A8288(void *,s16,s16,s16,s8);
extern s32 func_080A82C0(u16,u16);
extern void *func_080A8934(void *),*func_080A899C(void *),*func_080A89D8(void *,void *,u8 *);
extern void func_080A8940(void *),func_080A8A54(void *,void *),func_080A8A64(void *);
extern u32 func_080A8958(void *),func_080A8A68(void *,u16,u16);
extern u8 func_080A8A80(void *);
extern void *func_080A8A90(void *);
extern void func_080A8AAC(void *),func_080A9528(void),func_080A9548(void);
extern u32 func_080A9588(void);
extern void func_080B5880(void *,u8,u8);
extern u32 func_080B7E08(void *,u16,u16);
extern void *func_080B7E1C(void *,u16,u16,u8,u8,u8);
extern void func_080B7E7C(void *),func_080B7EDC(void *,s8 *,s8 *),func_080B7EFC(void *,u8,u8),func_080B7F18(void *,u8),func_080B7F4C(void);
extern void *func_080B8100(void *,void *,u32);
extern u32 func_080B8414(void *,u16,u16);
extern void func_080BA6D0(void *),func_080BC780(void *,u16);
extern u32 func_080BC798(void),func_080BC7FC(void),func_080BC810(void *,u8,u8);
extern void func_080BC7D4(void *,void *,void *,u8),func_080BC878(void *,void *,u8,u8),func_080BC8C4(void *),func_080BC8E8(void *,void *,u8,u8);
extern u32 func_080BC900(void);
extern void *func_080BC914(void *,u16),*func_080BC950(void *);
extern u8 func_080BC934(void *),func_080BC984(void *),func_080BC9B8(void *),func_080BC9CC(void *);
extern void func_080BC944(void *),func_080BC994(void *),func_080BC9E4(void *);
extern void *func_080BCA24(void *);
extern u8 func_080BCA40(void *,u16);
extern void func_080BCA54(void *);
extern void *func_080BD328(void);
extern void func_080BD340(void *);
extern u32 func_080BD34C(void *);
extern u32 func_080C1438(void);
extern void func_080C144C(void *),func_080C1460(void);
extern s32 func_080C1484(s32);
extern void func_080C14B0(s8 *,s8 *),func_080C14D8(s8 *,s8 *);
extern u32 func_080C1500(void),func_080C1514(void),func_080C1528(void),func_080C153C(void);
extern void func_080C15C0(void),func_080C15DC(u8,u8,u32),func_080C1654(u8,u8,u16,u16,u8),func_080C1700(s8),func_080C1748(void),func_080C1780(void),func_080C17B8(void),func_080C17C8(void);
extern u32 func_080C1920(void *),func_080C1994(void),func_080C19A8(void),func_080C19F0(void);
extern void func_080C1980(u32),func_080C19BC(u32),func_080C19DC(u8),func_080C1A04(u8,u16,u8,u8);
extern u32 func_080C1A78(u8,s8 *,s8 *),func_080C1B18(void),func_080C1B2C(void *);
extern void func_080C1AD4(u16),func_080C71B4(u16),func_080C7214(void),func_080C7240(void),func_080C7284(void);
extern u32 func_080C72E4(void),func_080C72F8(void),func_080C75F4(void),func_080C7650(void),func_080C76C4(void);
extern void func_080C7378(void),func_080C738C(void),func_080C7668(u32);
extern s32 func_080C7EA4(void *,u32);
extern u8 func_080C8298(void *),func_080C9540(u16),func_080C95A8(u16);
extern void func_080C9574(u16,u16),func_080C95C0(u16,u32);
extern u32 func_080CA3EC(void *),func_080CCD50(u16,u8),func_080CD584(void *);
extern u8 func_080CD944(void *),func_080CD95C(void *),func_080CDA7C(void *),func_080CDB54(void *),func_080CDB6C(void *),func_080CDB9C(void *),func_080CDBB4(void *);
extern void func_080CDEA4(void *,u8),func_081219F4(void);
extern u8 func_0812E4A8(void *),func_0812F1AC(u16),func_08134B38(void *),func_08134B88(void *,u8,u8),func_08135624(void *);
extern void func_08141540(u16);
extern u32 func_08149368(void *);
u32 func_08092784(void *object, u16 first, u16 second)
{
    ActionState *s = object;
    u32 *flags;
    u16 *state;
    Unit *unit, *tracking, **units;
    SelectionState *selection = (SelectionState *)data_0200F6A0;
    s32 i, x, y, result, count, old_direction, moving;
    u32 old_appearance, value, other_value;
    u8 old_kind, old_x, old_y, changed, changed_single;
    void *record, *effect;

    if (func_080C95A8(13)) {
        if (s->flags & 0x4000)
            return 1;
        if (s->flags & 0x800) {
            if ((u8)func_080C72F8()) {
                if (!(s->flags & 0x10000))
                    s->flags = (s->flags & ~0x800) | 0x1000;
            } else {
                s->flags &= ~0x10000;
            }
        }
        if (!(s->flags & 0x2000) && (s->flags & 0x1000)) {
            func_08004C40();
            func_081219F4();
            s->flags |= 0x6000;
        }
        if (s->flags & 0x4000)
            return 1;
    }
    if (s->action == 1) {
        result = (s16)func_08025464();
        if (!result)
            return 1;
        s->action = result < 0 ? 0 : 2;
    }
    flags = &s->flags;
    if (*flags & 0x40) {
        tracking = s->tracking;
        if (tracking == s->current || !tracking || !s->current || !func_0812E4A8(tracking->record)) {
            *flags &= ~0x40;
        } else if (*flags & 0x80) {
            old_direction = tracking->direction;
            moving = (u8)func_0809D3A8(&s->tracking_turn);
            if (old_direction != tracking->direction && moving == 1) {
                func_0809836C(tracking, 9, tracking->direction, 0);
                data_0839403C(tracking->animation);
                tracking->record[0xf8] = old_direction;
            } else if (!moving) {
                func_0809836C(tracking, 0, tracking->direction, 0);
                data_0839403C(tracking->animation);
                *flags &= ~0x80;
            }
        } else {
            x = s->current->x >> 5;
            y = s->current->y >> 5;
            if (x != tracking->record[0xf6] || y != tracking->record[0xf7]) {
                value = func_0809D6BC((s8)(x - tracking->record[0xf6]), (s8)(y - tracking->record[0xf7]));
                if (value != tracking->direction) {
                    tracking->record[0xf8] = value;
                    *flags |= 0x80;
                    s->tracking_turn.unit = tracking;
                    s->tracking_turn.target = value;
                    s->tracking_turn.delay = 8;
                    s->tracking_turn.ticks = 0;
                }
            }
        }
    }

    state = &s->state;
    switch (*state) {
    case 8:
        if (g_state_0200F390.flags & 1)
            break;
        if (g_state_0200F390.flags & 2) {
            *state = 13;
            if (func_080C95A8(13)) {
                SAVE_STATE();
                *state = 45;
            }
            break;
        }
        if (!(g_state_0200F390.flags & 4))
            break;
        *state = 11;
        SAVE_STATE(); *state = 9;
        SAVE_STATE(); *state = 15;
        break;
    case 9:
        s->dialog = func_08021854(func_08099C30(s->actor), 0);
        *state = 10;
        break;
    case 10:
        if (func_0802192C(s->dialog, 1))
            break;
        func_0802200C(s->dialog);
        goto pop_state;
    case 11:
        func_080BC780(s->actor, func_0800A018());
        *state = 12;
        break;
    case 12:
        if ((u8)func_080BC798())
            break;
        if (func_080C95A8(13))
            func_080C9574(42, (data_030028A0[0] >> 3) & 1);
        s->tracking = func_08099544(s->actor);
        if (!(g_state_0200F390.flags & 0x80)) {
            units = func_08022840(0x34);
            count = func_08099CDC(s->actor, units);
            for (i = 0; i < count; i++)
                func_0809836C(units[i], 10, (s8)units[i]->record[0xf8], 0);
            func_08022854(units);
            func_0809A9A8(s->actor);
            func_0809A9CC(s->actor);
            *state = 0;
            break;
        }
        s->current = func_0809AA38(s->actor, func_080C95A8(34));
        if (!s->current || !func_080924F4(s->current->record, s->actor)) {
            *state = 0;
            break;
        }
        {
            MapPosition position;
            position.x = s->current->x >> 5;
            position.y = s->current->y >> 5;
            position.z = s->current->z >> 4;
            g_state_0200F390.destination = g_state_0200F390.position = position;
            g_state_0200F390.position_changed = 1;
        }
        *flags |= 0x40;
        func_0809A5C0(s->actor, 0);
        s->other = s->current;
        *state = 19;
        SAVE_STATE(); *state = 21;
        SAVE_STATE(); *state = 2;
        break;
    case 6:
        if (!(u8)func_080A9588())
            break;
        if (!func_0800A5C8(s->sound))
            goto pop_state;
        *flags &= ~0xc0;
        func_08009FD0();
        *state = 7;
        break;
    case 7:
        if (func_08009FBC()) {
            if (!(g_state_0200F390.flags & 8))
                break;
            SAVE_STATE(); *state = 106;
            break;
        }
        *flags |= 0x40;
        goto pop_state;
    case 15:
        s->text = func_0808F8E8(g_table_0854CD54[func_0800A024()]);
        *state = 16;
        break;
    case 16:
        if ((u8)func_0808FA98(s->text, first, second))
            break;
        func_0808F848(s->text);
        goto pop_state;
    case 13:
        func_080A9548();
        if (!(u8)func_080A9588())
            break;
        s->sub_menu = func_080B8100(s->actor, g_state_02000080, 0x18);
        *state = 14;
        break;
    case 14:
        if ((u8)func_080B8414(s->sub_menu, first, second))
            break;
        func_080BA6D0(s->sub_menu);
        g_state_0200F390.flags &= 0xfffd;
        *state = 8;
        break;
    case 0:
        if (!(u8)func_080A9588())
            break;
        if (func_080C95A8(13))
            func_080C19BC(1);
        *state = 1;
        if (func_080C95A8(13))
            goto wait_cinematic;
    case 1:
        if (func_0802D72C(1))
            func_0802D704(func_0802D72C(1));
        s->current = 0;
        *state = 5;
        s->tracking = func_08099544(s->actor);
        if (!s->tracking)
            break;
        s->other = s->tracking;
        SAVE_STATE();
        goto lift_other;
    case 5:
        if (func_0802D72C(1)) {
            if ((func_0802B880(func_0802D72C(1)) & ~0x10) != 3)
                break;
        }
        func_08024ABC(data_0200F3AC, 0);
        s->state_count = 0;
        s->saved_mode_count = 0;
        func_080C9574(3, 0);
        func_080C9574(4, 0);
        s->current = func_0809F850(s->actor);
        if (!s->current)
            break;
        func_080C95C0(34, s->current->record[0x104]);
        {
            MapPosition position;
            position.x = s->current->x >> 5;
            position.y = s->current->y >> 5;
            position.z = s->current->z >> 4;
            g_state_0200F390.destination = g_state_0200F390.position = position;
            g_state_0200F390.position_changed = 1;
        }
        data_0200F3AC[10] = 1;
        *flags |= 0x40;
        {
            s16 replenished = func_080C7EA4(s->current->record, 0x15) + 5;
            if ((u32)replenished > (u32)func_080C7EA4(s->current->record, 0x16))
                replenished = func_080C7EA4(s->current->record, 0x16);
            *(u16 *)(s->current->record + 0x1c) = replenished;
        }
        s->other = s->current;
        func_080255FC(4);
        *flags &= ~4;
        value = s->current->record[0x101] + 1;
        if (value > 255)
            value = 255;
        s->current->record[0x101] = value;
        s->sound = 3;
        *state = 4;
        SAVE_STATE(); *state = 6;
        SAVE_STATE(); *state = 2;
        break;
    case 4:
        *state = 19;
        if (func_080924F4(s->current->record, s->actor)) {
            SAVE_STATE(); *state = 33;
            SAVE_STATE(); *state = 25;
            if (func_080C8298(s->current->record)) {
                SAVE_STATE(); *state = 23;
            }
            SAVE_STATE(); *state = 31;
            SAVE_STATE(); *state = 76;
        }
        SAVE_STATE(); *state = 20;
        s->auxiliary = 0;
        if (s->tracking && s->tracking != s->current && func_08135624(s->current->record)) {
            s->auxiliary = func_08134B38(s->current->record);
            SAVE_STATE(); *state = 17;
        }
        SAVE_STATE(); *state = 111;
        SAVE_STATE(); *state = 21;
        SAVE_STATE(); *state = 76;
        break;
    case 111:
        if (!(u8)func_0809F9D8(s->current)) {
            old_appearance = s->current->appearance;
            old_kind = s->current->kind;
            func_08098130(s->current);
            if (s->current->appearance != old_appearance || s->current->kind != old_kind)
                func_0809836C(s->current, 10, s->current->direction, 0);
            goto pop_state;
        }
        s->motion = func_0809F9A8(s->current);
        *state = 112;
        break;
    case 112:
        if (func_0809F9C0(s->motion))
            break;
        func_0809F9D0(s->motion);
        s->motion = 0;
        old_appearance = s->current->appearance;
        old_kind = s->current->kind;
        func_08098130(s->current);
        if (s->current->appearance != old_appearance || s->current->kind != old_kind)
            func_0809836C(s->current, 10, s->current->direction, 0);
        if (func_0812E4A8(s->current->record))
            goto pop_state;
        func_0809F8EC(s->current->record);
        func_08096F8C(s->current);
        func_080A9548();
        func_080C9574(3, 1);
        func_080C9574(4, 1);
        s->state_count = 0;
        s->other = s->current;
        s->sound = 6;
        *state = 0;
        SAVE_STATE(); *state = 6;
        break;
    case 2:
        func_08099A70(s->actor, s->current);
        goto pop_state;
    case 23:
        *flags &= ~0xc0;
        func_080A9528();
        s->menu = func_080BC950(s->actor);
        *state = 24;
        break;
    case 24:
        if (!(u8)func_080A9588())
            break;
        if (func_080BC984(s->menu)) {
            if (!func_080BC9CC(s->menu))
                break;
            func_080BC9E4(s->menu);
            func_080A9548();
            SAVE_STATE(); *state = 33;
            break;
        }
        value = func_080BC9B8(s->menu);
        func_080BC994(s->menu);
        s->menu = 0;
        POP_STATE();
        if (value) {
            *state = 26;
            s->other = s->current;
            SAVE_STATE(); *state = 76;
        }
        break;
    case 25:
        func_080A9528();
        *state = 26;
        break;
    case 26:
        if (!(u8)func_080A9588())
            break;
        *flags = (*flags | 4) & ~8;
        func_080C144C(s->current);
        *state = 27;
        s->delay = 40;
        SAVE_STATE(); *state = 96;
        break;
    case 27:
        if (s->delay)
            s->delay--;
        if (!(*flags & 8)) {
            if (func_080C1438())
                break;
            *flags |= 8;
            func_080C1460();
        }
        if (s->delay)
            break;
        s->step = 0;
        func_080A9548();
        POP_STATE();
        if (!func_080C95A8(13) || !(u8)func_080C1B2C(s->current))
            break;
        func_080C15C0();
        func_080C17C8();
        func_080C19BC(1);
        func_080C1980(*func_08002830());
        func_080C17B8();
        SAVE_STATE();
        goto queue_cinematic;
    case 98:
        func_08141540(100);
        func_0801D624(s->target_x, s->target_y, 2);
        func_0801D918();
        *state = 99;
        SAVE_STATE(); *state = 96;
        func_080922CC(data_0200F4C0, (s->target_x << 5) + 16,
                     func_0801CC18(s->target_x, s->target_y) << 4,
                     (s->target_y << 5) + 16, -120, -86, 4, 100);
        SAVE_STATE(); *state = 22;
        break;
    case 99:
        if (!func_0801D8B8())
            break;
        for (y = 0; y < 16; y++)
            for (x = 0; x < 16; x++)
                if (func_0801CC7C(x, y)) {
                    if (x == s->target_x && y == s->target_y)
                        func_0801D624(x, y, 2);
                    else
                        func_0801D624(x, y, 0);
                }
        func_0801D918();
        goto pop_state;
    case 96:
        s->timer = 12;
        *state = 97;
        break;
    case 97:
        if (--s->timer)
            break;
        goto pop_state;
    case 28:
        if (!func_080924F4(s->current->record, s->actor)) {
            *flags &= ~4;
            s->state_count = 0;
            *state = 19;
            if (func_080C95A8(13) && (data_030028A0[0] & 8)) {
                func_080C15C0();
                func_080C1700(s->current->direction);
                func_080C19BC(1);
                func_080C17B8();
                SAVE_STATE();
                goto queue_cinematic;
            }
            break;
        }
        func_080C71B4(0);
        switch (func_080C1484(s->step)) {
        case 0:
            value = (u8)func_080C1500();
            if (s->current->direction != value)
                func_0809836C(s->current, 0, value, 0);
            if (!func_080C9540(3)) {
                *(u32 *)(g_state_02000000 + 0x3c24) &= ~2;
                *(u16 *)(g_state_02000000 + 0x3c2e) = 0xffff;
            }
            func_0809F8EC(s->current->record);
            func_08096F8C(s->current);
            func_080A9548();
            func_080C9574(3, 1);
            func_080C9574(4, 1);
            s->sound = 6;
            *state = 0;
            SAVE_STATE(); *state = 6;
            SAVE_STATE(); *state = 33;
            break;
        case 2:
            func_080C14B0(&s->target_x, &s->target_y);
            s->path_count = func_0809A604(s->current, s->target_x, s->target_y,
                              (u8)((u32)(u8)func_080CA3EC(s->current->record) / 10), s->path);
            s->target_x = s->path[s->path_count - 1][0];
            s->target_y = s->path[s->path_count - 1][1];
            *state = 19;
            SAVE_STATE(); *state = 45;
            SAVE_STATE(); *state = 21;
            if (func_0809D8F0(s->current)) {
                SAVE_STATE(); *state = 40;
                SAVE_STATE(); *state = 79;
                SAVE_STATE(); *state = 96;
            } else {
                SAVE_STATE(); *state = 79;
                SAVE_STATE(); *state = 40;
            }
            SAVE_STATE(); *state = 21;
            SAVE_STATE(); *state = 96;
            SAVE_STATE(); *state = 98;
            SAVE_STATE(); *state = 96;
            SAVE_STATE(); *state = 21;
            s->other = s->current;
            SAVE_STATE(); *state = 29;
            SAVE_STATE(); *state = 33;
            SAVE_STATE(); *state = 44;
            break;
        case 3:
            func_080C9574(3, 1);
            s->ability = func_080C1514();
            s->ability_argument = func_080C1528();
            s->variant = 255;
            s->chain_index = 0;
            if (s->ability == 0x21)
                for (i = 0; i < 2; i++)
                    s->chain_ability[i] = func_080C1A78(i, &s->chain_x[i], &s->chain_y[i]);
            if (func_080CDA7C(s->current->record))
                s->variant = func_080C19F0();
            func_080C14D8(&s->target_x, &s->target_y);
            *flags |= 1;
            if ((u8)func_080C153C())
                *flags |= 2;
            if (func_0812F1AC(s->ability))
                *flags |= 0x20;
            else
                *flags &= ~0x20;
            s->other = s->current;
            *state = 19;
            SAVE_STATE(); *state = 21;
            if (s->ability == 0x21) {
                SAVE_STATE(); *state = 48;
            }
            SAVE_STATE(); *state = 48;
            SAVE_STATE(); *state = 33;
            break;
        case 4:
            SAVE_STATE(); *state = 26;
            s->other = s->current;
            SAVE_STATE(); *state = 76;
            break;
        case 5:
            s->other = s->current;
            s->message_id = func_080C1B18();
            func_080A9548();
            SAVE_STATE(); *state = 25;
            SAVE_STATE(); *state = 31;
            SAVE_STATE(); *state = 69;
            SAVE_STATE(); *state = 118;
            SAVE_STATE(); *state = 33;
            break;
        case 6:
            s->other = s->current;
            func_080A9548();
            SAVE_STATE(); *state = 126;
            SAVE_STATE(); *state = 52;
            SAVE_STATE(); *state = 50;
            SAVE_STATE(); *state = 33;
            break;
        }
        s->step++;
        break;
    case 76:
        s->saved_height = s->other->height;
    case 77:
        s->other->height = 30;
        func_08099EA0(s->other);
        func_08099F00(s->other);
        *state = 78;
        break;
    case 78:
        func_0809A5E0(s->actor, 1, s->other);
        if (!func_08149368(s->other->render))
            break;
        s->other->height = s->saved_height;
        func_0809A5C0(func_08096D7C(), 1);
        goto pop_state;
    case 20:
        if (func_0812E4A8(s->current->record))
            goto pop_state;
        func_080C9574(3, 1);
        func_080C9574(4, 1);
        func_0809F8EC(s->current->record);
        func_08096F8C(s->current);
        func_080A9548();
        goto reset_states;
    case 19:
        *flags |= 0x40;
        if (!(u8)func_080925A4(s->current->record)) {
            if (*flags & 4) {
                *state = 28;
                SAVE_STATE(); *state = 76;
            } else {
                *state = 46;
            }
            break;
        }
        if (*flags & 4) {
            *state = 28;
            SAVE_STATE(); *state = 76;
            break;
        }
        *flags &= ~1;
        {
            MapPosition position;
            position.x = s->current->x >> 5;
            position.y = s->current->y >> 5;
            position.z = s->current->z >> 4;
            g_state_0200F390.destination = g_state_0200F390.position = position;
            g_state_0200F390.position_changed = 1;
        }
        func_08024ABC(data_0200F3AC, 4);
        s->other = s->current;
        *state = 35;
        if (!(*flags & 0x10)) {
            SAVE_STATE(); *state = 31;
        }
        *flags &= ~0x10;
        func_080A9528();
        func_080C71B4(7);
        break;
    case 31:
        s->message = func_0802B70C(s->other->record, 0);
        *state = 32;
        break;
    case 32:
        if ((func_0802B880(func_0802D72C(1)) & ~0x10) == 2)
            goto pop_state;
        break;
    case 33:
        func_0802D704(s->message);
        *state = 34;
        break;
    case 34:
        if ((func_0802B880(func_0802D72C(1)) & ~0x10) == 3)
            goto pop_state;
        break;
    case 35:
        *flags &= ~0x22;
        func_080294E4(s->current->record);
        func_0802542C(4);
        s->action = 1;
        *state = 37;
        break;
    case 36:
        {
            MapPosition position;
            position.x = s->current->x >> 5;
            position.y = s->current->y >> 5;
            position.z = s->current->z >> 4;
            g_state_0200F390.destination = g_state_0200F390.position = position;
            g_state_0200F390.position_changed = 1;
        }
        func_08024ABC(data_0200F3AC, 4);
        *flags &= ~0x22;
        func_080294E4(s->current->record);
        func_08025448(4);
        s->action = 1;
        *state = 37;
        break;
    case 37:
        if (!s->action) {
            if (!func_080C9540(4)) {
                *state = 19;
                SAVE_STATE(); *state = 82;
                *flags |= 0x10;
            } else {
                func_08024ABC(data_0200F3AC, 0);
                POP_STATE();
                SAVE_STATE(); *state = 33;
            }
            break;
        }
        switch (func_080254A0() - 7) {
        case 0:
            if (func_080C9540(4)) {
                *state = 19;
                break;
            }
            *state = 19;
            SAVE_STATE(); *state = 38;
            s->other = s->current;
            SAVE_STATE(); *state = 29;
            SAVE_STATE(); *state = 76;
            SAVE_STATE(); *state = 33;
            break;
        case 1:
            *state = 19;
            func_080C9574(3, 1);
            break;
        case 5:
            *state = 36;
            SAVE_STATE(); *state = 31;
            SAVE_STATE(); *state = 48;
            SAVE_STATE(); *state = 33;
            s->ability = 0;
            s->chain_index = 0;
            s->variant = 255;
            break;
        case 6: case 7: case 8:
            *state = 36;
            SAVE_STATE(); *state = 72;
            break;
        case 9:
            s->ability = func_080CD584(s->current->record);
            s->chain_index = 0;
            s->variant = 255;
            *state = 36;
            SAVE_STATE(); *state = 31;
            SAVE_STATE(); *state = 48;
            SAVE_STATE(); *state = 33;
            *flags |= 0x20;
            break;
        case 10:
            *state = 36;
            SAVE_STATE(); *state = 31;
            SAVE_STATE(); *state = 48;
            SAVE_STATE(); *state = 33;
            *flags |= 2;
            s->ability = 0;
            s->chain_index = 0;
            s->variant = 255;
            break;
        case 2:
            *state = 19;
            SAVE_STATE(); *state = 46;
            break;
        case 3:
            *state = 36;
            SAVE_STATE(); *state = 31;
            func_080A9548();
            SAVE_STATE(); *state = 72;
            func_080294E4(s->current->record);
            break;
        case 4:
            *state = 19;
            SAVE_STATE(); *state = 113;
            SAVE_STATE(); *state = 33;
            func_080A9548();
            func_080255FC(4);
            break;
        }
        break;
    case 113:
        func_0809A260(s->actor, 0);
        s->saved_modes[s->saved_mode_count++] = data_0200F3AC[4];
        func_08024ABC(data_0200F3AC, 0);
        s->unit_menu = func_080A8A90(s->current);
        *state = 114;
        break;
    case 114:
        if (func_080A8A80(s->unit_menu))
            break;
        func_080A8AAC(s->unit_menu);
        s->unit_menu = 0;
        func_08024ABC(data_0200F3AC, s->saved_modes[--s->saved_mode_count]);
        func_0809A260(s->actor, 1);
        goto pop_state;
    case 72:
        if (!(u8)func_080A9588())
            break;
        func_080C7214();
        g_state_0200F390.flags &= 0xffdf;
        g_state_0200F390.flags &= 0xffbf;
        s->chain_index = 0;
        g_state_0200F390.mode = 1;
        func_08024ABC(data_0200F3AC, 0);
        *state = 75;
        break;
    case 73: case 74:
        *state = 74;
        g_state_0200F390.mode = 2;
        func_08024ABC(data_0200F3AC, 0);
        *state = 75;
        break;
    case 75:
        if (g_state_0200F390.mode & 0x80) {
            g_state_0200F390.mode = 0;
            func_080C71B4(7);
            func_080A9528();
            goto pop_state;
        }
        if (g_state_0200F390.mode)
            break;
        *state = 73;
        if (!(g_state_0200F390.flags & 0x40))
            s->chain_index = 0;
        if (s->chain_index)
            s->chain_ability[s->chain_index] = func_080254A0();
        else {
            s->chain_index = 0;
            s->ability = func_080254A0();
        }
        s->variant = 255;
        if (func_080CDA7C(s->current->record))
            s->variant = func_08025584();
        if (s->ability == 0x21)
            s->chain_ability[s->chain_index] = func_080294D8();
        else if ((s->ability && func_080CCD50(s->ability, 0x1b)) || s->ability == 0x109)
            s->ability_argument = func_080294D8();
        else {
            SAVE_STATE(); *state = 31;
        }
        SAVE_STATE(); *state = 48;
        SAVE_STATE(); *state = 33;
        func_080A9528();
        break;
    case 93:
        func_0802542C(10);
        s->action = 1;
        func_08024ABC(data_0200F3AC, 4);
        *state = 95;
        break;
    case 94:
        func_08024ABC(data_0200F3AC, 4);
        func_08025448(10);
        s->action = 1;
        *state = 95;
        break;
    case 95:
        if (!s->action) {
            POP_STATE();
            func_08024ABC(data_0200F3AC, s->saved_modes[--s->saved_mode_count]);
            s->selection = -1;
            break;
        }
        if (s->action != 2)
            break;
        s->action = 0;
        *state = 94;
        SAVE_STATE(); *state = 31;
        func_080A9548();
        SAVE_STATE(); *state = 72;
        break;
    case 82:
        {
            MapPosition position;
            position.x = s->other->x >> 5;
            position.y = s->other->y >> 5;
            position.z = s->other->z >> 4;
            g_state_0200F390.destination = g_state_0200F390.position = position;
            g_state_0200F390.position_changed = 1;
            g_callbacks_0836D4B8(selection, 0x54);
            selection->unit = s->other;
            selection->x = position.x;
            selection->y = position.y;
        }
    case 83:
        func_080A9528();
        func_08024ABC(data_0200F3AC, 1);
        s->action = 0;
        *state = 84;
        break;
    case 84:
        func_08092638(s->actor, g_state_0200F390.position.x, g_state_0200F390.position.y);
        if ((first & 0x208) && !func_080C9540(4) && !func_080C9540(3)) {
            if (first & 0x200)
                *flags |= 0x400;
            else
                *flags &= ~0x400;
            func_08024ABC(data_0200F3AC, 0);
            SAVE_STATE(); *state = 101;
            break;
        }
        if (first & 1) {
            unit = func_08099644(s->actor, g_state_0200F390.position.x, g_state_0200F390.position.y);
            if (unit && func_080C8298(unit->record))
                unit = 0;
            if (!unit || unit == s->current) {
                POP_STATE();
                s->other = s->current;
                if (selection->unit != s->current)
                    *flags &= ~0x10;
                SAVE_STATE(); *state = 21;
                func_08024ABC(data_0200F3AC, 4);
                if (selection->unit) {
                    if (selection->unit != s->current) {
                        SAVE_STATE(); *state = 33;
                    }
                } else {
                    SAVE_STATE(); *state = 34;
                }
                func_08024ABC(data_0200F3AC, 4);
                {
                    MapPosition position;
                    position.x = s->other->x >> 5;
                    position.y = s->other->y >> 5;
                    position.z = s->other->z >> 4;
                    g_state_0200F390.destination = g_state_0200F390.position = position;
                    g_state_0200F390.position_changed = 1;
                }
                break;
            }
            func_080294E4(unit->record);
            s->saved_modes[s->saved_mode_count++] = data_0200F3AC[4];
            func_08024ABC(data_0200F3AC, 4);
            SAVE_STATE(); *state = 93;
            s->other = unit;
            SAVE_STATE(); *state = 32;
            SAVE_STATE(); *state = 21;
            break;
        }
        if (!(first & 2))
            break;
        unit = func_08099644(s->actor, g_state_0200F390.position.x, g_state_0200F390.position.y);
        func_080A9548();
        func_08024ABC(data_0200F3AC, 0);
        if (unit && func_080C8298(unit->record))
            unit = 0;
        if (!unit) {
            *state = 83;
            SAVE_STATE(); *state = 87;
            g_callbacks_0836D4B8(selection, 0x54);
            selection->x = selection->y = -1;
            SAVE_STATE(); *state = 33;
            break;
        }
        s->other = unit;
        POP_STATE();
        SAVE_STATE(); *state = 82;
        SAVE_STATE(); *state = 31;
        SAVE_STATE(); *state = 21;
        SAVE_STATE(); *state = 79;
        SAVE_STATE(); *state = 85;
        SAVE_STATE(); *state = 29;
        SAVE_STATE(); *state = 76;
        SAVE_STATE(); *state = 21;
        SAVE_STATE(); *state = 76;
        SAVE_STATE(); *state = 33;
        break;
    case 85:
        func_08024ABC(data_0200F3AC, 3);
        *state = 86;
        break;
    case 86:
        if (second & 2)
            break;
        func_08024ABC(data_0200F3AC, 0);
        s->selection = s->selection2 = s->selection3 = -1;
        goto pop_state;
    case 101:
        func_080A9548();
        if (!(u8)func_080A9588())
            break;
        func_08024ABC(data_0200F3AC, 0);
        *state = 102;
        SAVE_STATE(); *state = 33;
        break;
    case 102:
        if (*flags & 0x400)
            func_0802542C(17);
        else
            func_0802542C(1);
        func_080255FC(2);
        s->action = 1;
        *state = 103;
        break;
    case 103:
        if (s->action == 2) {
            switch (func_080254A0() - 1) {
            case 0:
                g_state_0200F390.mode = 1;
                s->action = 0;
                SAVE_STATE(); *state = 104;
                s->other = 0;
                break;
            case 1: case 3:
                g_state_0200F390.mode = 1;
                SAVE_STATE(); *state = 105;
                break;
            case 2:
                g_state_0200F390.mode = 1;
                s->action = 0;
                SAVE_STATE(); *state = 105;
                break;
            case 4:
                *state = 102;
                SAVE_STATE(); *state = 124;
                break;
            case 5:
                *state = 120;
                break;
            }
        } else if (!s->action) {
            func_08024ABC(data_0200F3AC, 1);
            g_callbacks_0836D4B8(selection, 0x54);
            selection->x = selection->y = -1;
            func_08092638(s->actor, g_state_0200F390.position.x, g_state_0200F390.position.y);
            func_080A9528();
            goto pop_state;
        }
        break;
    case 105:
        if (g_state_0200F390.mode & 0x80) {
            s->action = 1;
            g_state_0200F390.mode = 0;
            if (!(*flags & 0x400)) {
                func_08025448(1);
                goto pop_state;
            }
            goto close_two_menus;
        }
        if (g_state_0200F390.mode)
            break;
        result = (s8)func_08025560();
        if (result < 0) {
            s->action = 1;
            g_state_0200F390.mode = 0;
            if (!(*flags & 0x400)) {
                func_08025448(1);
                goto pop_state;
            }
            goto close_two_menus;
        }
        s->message_id = result == 0 ? 0x162 : 0x163;
        POP_STATE();
        POP_STATE();
        s->other = s->current;
        {
            MapPosition position;
            position.x = s->current->x >> 5;
            position.y = s->current->y >> 5;
            position.z = s->current->z >> 4;
            g_state_0200F390.destination = g_state_0200F390.position = position;
            g_state_0200F390.position_changed = 1;
        }
        SAVE_STATE(); *state = 71;
        SAVE_STATE(); *state = 69;
        if (func_080C95A8(13)) {
            SAVE_STATE(); *state = 117;
            func_080C15C0();
            func_080C1AD4(s->message_id);
            func_080C1980(*func_08002830());
            func_080C19BC(1);
            func_080C17B8();
            SAVE_STATE(); *state = 42;
            func_080C71B4(1);
        }
        SAVE_STATE(); *state = 21;
        break;
    case 104:
        record = func_080294FC();
        if (!record)
            break;
        if (!s->other || s->other->record != record) {
            s->other = func_08099560(s->actor);
            SAVE_STATE(); *state = 21;
            break;
        }
        if (g_state_0200F390.mode & 0x80) {
            s->other = func_08099560(s->actor);
            {
                MapPosition position;
                position.x = s->other->x >> 5;
                position.y = s->other->y >> 5;
                position.z = s->other->z >> 4;
                g_state_0200F390.destination = g_state_0200F390.position = position;
                g_state_0200F390.position_changed = 1;
            }
            s->action = 1;
            g_state_0200F390.mode = 0;
            if (!(*flags & 0x400)) {
                func_08025448(1);
                goto pop_state;
            }
            goto close_two_menus;
        }
        if (g_state_0200F390.mode)
            break;
        s->other = func_08099560(s->actor);
        {
            MapPosition position;
            position.x = s->other->x >> 5;
            position.y = s->other->y >> 5;
            position.z = s->other->z >> 4;
            g_state_0200F390.destination = g_state_0200F390.position = position;
            g_state_0200F390.position_changed = 1;
        }
        func_080A9528();
        POP_STATE();
        POP_STATE();
        func_08024ABC(data_0200F3AC, 1);
        g_callbacks_0836D4B8(selection, 0x54);
        selection->x = selection->y = -1;
        break;
    case 124:
        func_08029544(5);
        *state = 125;
        break;
    case 125:
        if (!func_08011860())
            break;
        POP_STATE();
        if (!func_08013380()) {
            *state = 126;
            if (func_080C95A8(13)) {
                SAVE_STATE(); *state = 52;
                SAVE_STATE(); *state = 50;
                func_080C15C0();
                func_080C1780();
                func_080C19BC(2);
                func_080C1700(s->current->direction);
                func_080C19BC(2);
                func_080C17B8();
                SAVE_STATE(); *state = 42;
                func_080C71B4(1);
            }
        } else if (*flags & 0x400) {
            POP_STATE();
            s->action = 0;
            SAVE_STATE(); *state = 71;
        }
        func_0802966C();
        break;
    case 126:
        func_08009AFC(0xaa);
        *flags &= ~0xc0;
        func_08009FD0();
        *state = 7;
        break;
    case 120:
        s->system_menu = func_080BD328();
        *state = 121;
        break;
    case 121:
        switch ((u8)func_080BD34C(s->system_menu)) {
        case 1:
            if (!(*flags & 0x400)) {
                func_080BD340(s->system_menu);
                *state = 102;
                break;
            }
        case 2:
            func_080BD340(s->system_menu);
            func_08024ABC(data_0200F3AC, 1);
            g_callbacks_0836D4B8(selection, 0x54);
            selection->x = selection->y = -1;
            func_08092638(s->actor, g_state_0200F390.position.x, g_state_0200F390.position.y);
            func_080A9528();
            POP_STATE();
            break;
        case 3:
            func_080BD340(s->system_menu);
            func_080230A8();
            *state = 110;
            break;
        }
        break;
    case 69:
        s->notice = func_080BC914(s->current, s->message_id);
        *state = 70;
        break;
    case 70:
        if (func_080BC934(s->notice))
            break;
        func_080BC944(s->notice);
        goto pop_state;
    case 71:
        func_08024ABC(data_0200F3AC, 1);
        func_080A9528();
        g_callbacks_0836D4B8(selection, 0x54);
        selection->x = selection->y = -1;
        goto pop_state;
    case 117:
        func_080C7668(1);
        *state = 119;
        break;
    case 118:
        func_080C7668(0);
        *state = 119;
        break;
    case 119:
        if ((u8)func_080C76C4())
            break;
        goto pop_state;
    case 106:
        if (func_080C95A8(13))
            *flags &= ~0x800;
        switch ((u8)func_0809A900(s->actor)) {
        case 1:
            *(u32 *)(g_state_02000000 + 0x3c24) |= 1;
            s->outcome_menu = func_0809185C(g_state_0200F390.flags & 0x10 ? 0x80 : 0);
            SAVE_STATE(); *state = 109;
            break;
        case 2:
            *(u32 *)(g_state_02000000 + 0x3c24) &= ~1;
            s->outcome_menu = func_0809185C(g_state_0200F390.flags & 0x10 ? 0x81 : 1);
            SAVE_STATE(); *state = 109;
            break;
        case 3:
            s->transition = func_08091DC0();
            *state = 107;
            break;
        }
        break;
    case 107:
        if (!(u8)func_08091E48(s->transition) || !(u8)func_080922A4(s->transition))
            break;
        func_080922C4(s->transition);
        *state = 108;
        break;
    case 108:
        if ((u8)func_08091E48(s->transition))
            break;
        func_08092288(s->transition);
        func_0809A950(g_state_02000080, 0x18);
        g_state_0200F390.flags &= 0xfff7;
        *state = 110;
        break;
    case 109:
        if ((u8)func_08091930(s->outcome_menu, first, second))
            break;
        func_080917F8(s->outcome_menu);
        g_state_0200F390.flags &= 0xfff7;
        *state = 110;
        break;
    case 87:
        func_08024ABC(data_0200F3AC, 3);
        *state = 88;
        break;
    case 88:
        if (second & 2)
            break;
        func_080922CC(data_0200F4C0, (u16)g_state_0200F390.position.x * 32 + 16,
                     func_0801CC18(g_state_0200F390.position.x, g_state_0200F390.position.y) << 4,
                     (u16)g_state_0200F390.position.y * 32 + 16, -120, -86, 4, 100);
        *state = 22;
        break;
    case 48:
        if (!(u8)func_080A9588())
            break;
        if (*flags & 4)
            s->ability_argument = func_080C1528();
        if (s->ability == 0x21) {
            s->ability_menu = func_080B7E1C(s->current, s->chain_ability[s->chain_index],
                                s->ability_argument, (*flags >> 2) & 1, (*flags >> 1) & 1, 255);
            if (s->chain_index == 0) {
                func_080B7F18(s->ability_menu, 1);
                if (*flags & 4)
                    func_080B7EFC(s->ability_menu, s->chain_x[0], s->chain_y[0]);
            } else {
                func_080B7F18(s->ability_menu, 0);
                if (*flags & 4)
                    func_080B7EFC(s->ability_menu, s->chain_x[1], s->chain_y[1]);
            }
        } else {
            s->ability_menu = func_080B7E1C(s->current, s->ability, s->ability_argument,
                                (*flags >> 2) & 1, (*flags >> 1) & 1, s->variant);
            func_080B7F18(s->ability_menu, 0);
            if (*flags & 4)
                func_080B7EFC(s->ability_menu, s->target_x, s->target_y);
        }
        *state = 49;
        break;
    case 49:
        result = func_080B7E08(s->ability_menu, first, second);
        if (result == 1) {
            func_080B7EDC(s->ability_menu, &s->target_x, &s->target_y);
            if (s->ability == 0x21) {
                func_080B7EDC(s->ability_menu, &s->chain_x[s->chain_index], &s->chain_y[s->chain_index]);
                if (!s->chain_index) {
                    s->chain_index++;
                    g_state_0200F390.flags |= 0x40;
                    func_080B7E7C(s->ability_menu);
                    s->ability_menu = 0;
                    goto pop_state;
                }
                s->chain_index++;
                s->target_x = s->chain_x[0];
                s->target_y = s->chain_y[0];
            }
            func_080C9574(3, 1);
            func_080B7E7C(s->ability_menu);
            s->ability_menu = 0;
            *flags |= 1;
            s->unknown_af = 0;
            s->other = s->current;
            *state = 19;
            SAVE_STATE(); *state = 21;
            SAVE_STATE(); *state = 56;
            if (!(g_state_02000000[0x2fc0] & 0x40)) {
                SAVE_STATE(); *state = 91;
            }
            SAVE_STATE(); *state = 89;
            s->chain_effects[0] = s->chain_effects[1] = 0;
            s->sound = 4;
            *(u16 *)(g_state_02000000 + 0x3c9c) = s->ability;
            SAVE_STATE(); *state = 6;
            break;
        }
        if (result != 2)
            break;
        if (s->ability == 0x21 || (s->ability && func_080CCD50(s->ability, 0x1b)) || s->ability == 0x109) {
            func_080A9548();
            s->chain_index = 0;
            g_state_0200F390.flags &= 0xffbf;
        } else {
            func_080A9528();
        }
        func_080B7E7C(s->ability_menu);
        s->ability_menu = 0;
        goto pop_state;
    case 46:
        func_080C71B4(7);
        func_08024ABC(data_0200F3AC, 0);
        func_080A8288(s->current, -1, -1, -1, s->current->direction);
        *state = 47;
        break;
    case 47:
        result = func_080A82C0(first, second);
        if (result == -1)
            break;
        if (result == -2) {
            if (*flags & 1)
                break;
            *flags |= 0x10;
            goto pop_state;
        }
        old_x = s->current->record[0xf6];
        old_y = s->current->record[0xf7];
        if (!func_080C9540(3)) {
            *(u32 *)(g_state_02000000 + 0x3c24) &= ~2;
            *(u16 *)(g_state_02000000 + 0x3c2e) = 0xffff;
        }
        func_0809F8EC(s->current->record);
        func_08096F8C(s->current);
        func_080A9548();
        func_080C9574(3, 1);
        func_080C9574(4, 1);
        s->sound = 6;
        *state = 0;
        SAVE_STATE(); *state = 6;
        SAVE_STATE(); *state = 33;
        if (!func_080C95A8(13))
            break;
        func_080C15C0();
        if (s->current->record[0xf6] != old_x || s->current->record[0xf7] != old_y) {
            func_080C15DC(s->current->record[0xf6], s->current->record[0xf7], 0);
            func_080C19BC(2);
        }
        func_080C1700(s->current->direction);
        func_080C19BC(2);
        func_080C17B8();
        SAVE_STATE();
        goto queue_cinematic;
    case 68:
        if ((u8)func_080BC900())
            break;
        goto pop_state;
    case 17:
        *flags &= ~0xc0;
        func_080BC7D4(s->tracking, s->current, s->effect, s->auxiliary);
        *state = 18;
        break;
    case 18:
        if ((u8)func_080BC7FC())
            break;
        *flags |= 0x40;
        if (s->auxiliary != 1) {
            s->current = 0;
            s->state_count = 0;
            func_0809A260(s->actor, 1);
            *state = 0;
            SAVE_STATE(); *state = 6;
            if (!func_080C95A8(13))
                break;
            SAVE_STATE(); *state = 52;
            SAVE_STATE(); *state = 50;
            break;
        }
        s->other = s->current;
        POP_STATE();
        if (!func_080C95A8(13))
            break;
        SAVE_STATE(); *state = 52;
        SAVE_STATE(); *state = 50;
        break;
    case 50:
        func_080C71B4(2);
    case 51:
        func_08005028();
        goto pop_state;
    case 52:
        if (!(u8)func_080C75F4())
            break;
        func_080C71B4(0);
        s->frame_delay = 0;
        *state = 53;
        break;
    case 53:
        if (*(u16 *)(data_030028A0 + 0x124) != 0x101 || data_030028A0[2] != 3)
            break;
        s->frame_delay = 0;
        *state = 54;
        break;
    case 54:
        if (s->frame_delay > 15)
            goto pop_state;
        s->frame_delay++;
        break;
    case 55:
        old_x = s->current->x >> 5;
        old_y = s->current->y >> 5;
        func_080C15C0();
        func_080C19DC(s->variant);
        if (s->current->record[0xf6] != old_x || s->current->record[0xf7] != old_y)
            func_080C15DC(old_x, old_y, 0);
        for (i = 0; i < 2; i++)
            func_080C1A04(i, s->chain_ability[i], s->chain_x[i], s->chain_y[i]);
        func_080C1654(s->target_x, s->target_y, s->ability, s->ability_argument, (*flags >> 1) & 1);
        func_080C1748();
        func_080C1980(*func_08002830());
        s->saved_random = func_080C1994();
        func_080C19BC(2);
        func_080C17B8();
        POP_STATE();
        SAVE_STATE(); *state = 52;
        SAVE_STATE(); *state = 50;
        SAVE_STATE();
        goto queue_cinematic;
    case 56:
        *state = 57;
        if (func_080C95A8(13)) {
            if (!(*flags & 4) && (u8)func_080C1920(s->current)) {
                SAVE_STATE(); *state = 55;
                break;
            }
            goto wait_cinematic;
        }
    case 57:
        if (*flags & 0x80)
            break;
        if (func_080C95A8(13))
            func_080C19BC(1);
        *flags &= ~0xc0;
        func_0809A260(s->actor, 0);
        func_080A9548();
        if (!(u8)func_080A9588() || (u8)func_0809A204(s->current->unknown_80))
            break;
        s->saved_x = s->current->record[0xf6];
        s->saved_y = s->current->record[0xf7];
        s->current->record[0xf8] = s->current->direction;
        func_08099E68(s->current, s->current->x >> 5, s->current->y >> 5);
    case 58:
        if (func_080C95A8(13)) {
            *func_08002830() = func_080C1994();
            s->saved_random = *func_08002830();
        }
        func_080CDEA4(s->current->record, 0);
        s->current->appearance &= ~0x20000;
        if (s->ability == 0x21) {
            i = s->unknown_af;
            s->chain_effects[i] = func_080A8194(s->current, s->chain_ability[i], s->ability_argument,
                                 s->chain_x[i], s->chain_y[i], (*flags >> 1) & 1, 255);
            if (s->chain_effects[i])
                func_080A8264(s->chain_effects[i]);
        } else {
            s->ability_effect = func_080A8194(s->current, s->ability, s->ability_argument,
                                 s->target_x, s->target_y, (*flags >> 1) & 1, s->variant);
            if (s->ability_effect)
                func_080A8264(s->ability_effect);
        }
        if (func_080C95A8(13))
            func_080C1980(*func_08002830());
        func_0809993C(s->actor, 1);
        if (*flags & 0x20)
            *(u16 *)(s->current->record + 0xd6) = 0;
        if (*flags & 2)
            *(u16 *)(s->current->record + 0xd6) = 0;
        *state = 60;
        if (s->ability == 0x21 && s->unknown_af)
            break;
        if (!func_080C95A8(13))
            break;
        s->delay = 8;
        func_080C7378();
        SAVE_STATE(); *state = 59;
        break;
    case 59:
        if (*(u16 *)(data_030028A0 + 0x124) != 0x101 || data_030028A0[2] != 3)
            break;
        if (s->delay > 0)
            goto decrease_delay;
        func_080C738C();
        *flags |= 0x12000;
        goto pop_state;
    case 60:
        if (*flags & 0x10000)
            break;
        if (s->ability == 0x21) {
            effect = s->chain_effects[s->unknown_af];
            if (effect && func_080A8270(effect))
                break;
            if (++s->unknown_af <= 1 && func_0812E4A8(s->current->record) &&
                !func_080CD95C(s->current->record) && !func_080CDB9C(s->current->record) &&
                !func_080CDBB4(s->current->record)) {
                *state = 58;
                break;
            }
        } else if (func_080A8270(s->ability_effect)) {
            break;
        }
        *state = 62;
        if (func_080C95A8(13)) {
            *flags &= ~0x800;
            s->delay = 2;
            SAVE_STATE(); *state = 61;
            break;
        }
    case 62:
        if (func_080C95A8(13)) {
            if (!(u8)func_080C72E4() && !(u8)func_080C72F8())
                break;
            *flags |= 0x800;
            func_080C19BC(1);
            *flags &= ~0x2000;
        }
        *flags |= 0x40;
        func_0809993C(s->actor, 0);
        if (s->ability == 0x21) {
            s->effect_list = func_080A899C(s->chain_effects[0]);
            if (s->effect_list) {
                if (s->chain_effects[1])
                    func_080A8A54(s->effect_list, s->chain_effects[1]);
            } else if (s->chain_effects[1]) {
                s->effect_list = func_080A899C(s->chain_effects[1]);
            }
            changed = 0;
            s->effect_list = func_080A89D8(s->effect_list, s->chain_effects[0], &changed);
            if (!changed) {
                s->effect_list = func_080A89D8(s->effect_list, s->chain_effects[1], &changed);
                if (!changed)
                    goto collect_effect_result;
            }
            func_080C9574(42, func_080C9540(42) ^ 1);
        } else {
            changed_single = 0;
            s->effect_list = func_080A899C(s->ability_effect);
            s->effect_list = func_080A89D8(s->effect_list, s->ability_effect, &changed_single);
            if (changed_single)
                func_080C9574(42, func_080C9540(42) ^ 1);
        }
collect_effect_result:
        if (s->effect_list) {
            *state = 66;
            SAVE_STATE(); *state = 65;
            break;
        }
    case 66:
        if (s->ability == 0x21)
            s->effect_result = func_080A7138(s->chain_effects[0], s->chain_effects[1]);
        else
            s->effect_result = func_080A8934(s->ability_effect);
        *state = 64;
        if (s->effect_result) {
            SAVE_STATE(); *state = 67;
            break;
        }
    case 64:
        *flags &= ~0x300;
        s->auxiliary = 0;
        if (s->tracking && func_0812E4A8(s->tracking->record)) {
            if (s->ability == 0x21) {
                value = func_08134B88(s->chain_effects[0], 1, 1);
                other_value = func_08134B88(s->chain_effects[1], 1, 1);
                effect = value >= other_value ? s->chain_effects[0] : s->chain_effects[1];
                s->auxiliary = func_08134B88(effect, 0, 1);
                if (s->auxiliary)
                    *flags |= 0x100;
                func_080BC8C4(s->tracking);
                for (i = 0; i < 2; i++) {
                    if (s->chain_effects[i] && (u8)func_080BC810(s->chain_effects[i], s->auxiliary, 1)) {
                        *flags |= 0x200;
                        func_080BC8E8(s->tracking, s->chain_effects[i], s->auxiliary, 1);
                    }
                }
            } else {
                s->auxiliary = func_08134B88(s->ability_effect, 0, 0);
                if (s->auxiliary)
                    *flags |= 0x100;
                if ((u8)func_080BC810(s->ability_effect, s->auxiliary, 0)) {
                    *flags |= 0x200;
                    func_080BC878(s->tracking, s->ability_effect, s->auxiliary, 0);
                }
            }
        }
        if (s->ability == 0x21) {
            if (s->chain_effects[1])
                func_080A80C8(s->chain_effects[1]);
            if (s->chain_effects[0])
                func_080A80C8(s->chain_effects[0]);
            s->chain_effects[1] = s->chain_effects[0] = 0;
        } else {
            func_080A80C8(s->ability_effect);
            s->ability_effect = 0;
        }
        *(u32 *)(g_state_02000000 + 0x3c24) &= ~2;
        *(u32 *)(g_state_02000000 + 0x3c24) |= *flags & 2;
        *(u16 *)(g_state_02000000 + 0x3c2e) = s->ability;
        s->ability_effect = 0;
        *flags &= ~0x22;
        s->saved_x = s->current->record[0xf6];
        s->saved_y = s->current->record[0xf7];
        s->sound = 5;
        *state = 63;
        SAVE_STATE(); *state = 6;
        if (func_0812E4A8(s->current->record)) {
            SAVE_STATE(); *state = 2;
        }
        if (func_080C95A8(13)) {
            SAVE_STATE(); *state = 52;
            SAVE_STATE(); *state = 50;
        }
        if (*flags & 0x200) {
            SAVE_STATE(); *state = 68;
        }
        if (!(*flags & 0x100))
            break;
        s->other = s->tracking;
        SAVE_STATE(); *state = 17;
        SAVE_STATE();
lift_other:
        *state = 77;
        s->saved_height = 255;
        break;
    case 63:
        func_0809A260(s->actor, 1);
        if (!func_0812E4A8(s->current->record)) {
            func_0809F8EC(s->current->record);
            func_08096F8C(s->current);
            func_080A9548();
            func_080C9574(3, 1);
            func_080C9574(4, 1);
reset_states:
            s->state_count = 0;
            *state = 0;
            break;
        }
        if (*flags & 4)
            goto pop_state;
        if (!func_080CD944(s->current->record) && !func_080CDB54(s->current->record) &&
            !func_080CDB6C(s->current->record))
            goto pop_state;
        func_0809F8EC(s->current->record);
        func_08096F8C(s->current);
        func_080A9548();
        func_080C9574(3, 1);
        func_080C9574(4, 1);
        s->state_count = 0;
        *state = 0;
        break;
    case 61:
        if (s->delay > 0) {
decrease_delay:
            s->delay--;
            break;
        }
        func_080C7240();
        func_080C7284();
        goto pop_state;
    case 65:
        if ((u8)func_080A8A68(s->effect_list, first, second))
            break;
        func_080A8A64(s->effect_list);
        goto pop_state;
    case 67:
        if ((u8)func_080A8958(s->effect_result))
            break;
        func_080A8940(s->effect_result);
        s->effect_result = 0;
        goto pop_state;
    case 115:
        s->special_menu = func_080BCA24(s->actor);
        *state = 116;
        break;
    case 116:
        if (func_080BCA40(s->special_menu, first))
            break;
        func_080BCA54(s->special_menu);
        s->special_menu = 0;
        goto pop_state;
    case 38:
        func_080C9574(4, 0);
        {
            MapPosition position;
            position.x = s->current->x >> 5;
            position.y = s->current->y >> 5;
            position.z = s->current->z >> 4;
            g_state_0200F390.destination = g_state_0200F390.position = position;
            g_state_0200F390.position_changed = 1;
        }
        func_08024ABC(data_0200F3AC, 1);
        func_080B7F4C();
        *state = 39;
        break;
    case 39:
        if (first & 2) {
            func_0802D704(func_0802D72C(1));
            func_0802D704(func_0802D72C(0));
            s->other = s->current;
            func_08141540(104);
            if ((u16)((MapPosition *)data_0200F3B8)->x == s->current->record[0xf6] &&
                (u16)((MapPosition *)data_0200F3B8)->y == s->current->record[0xf7]) {
                func_08024ABC(data_0200F3AC, 4);
                POP_STATE();
                SAVE_STATE(); *state = 21;
                SAVE_STATE(); *state = 79;
            } else {
                *state = 38;
                func_08024ABC(data_0200F3AC, 0);
                SAVE_STATE(); *state = 21;
            }
            break;
        }
        if (first & 1) {
            if (!func_08099FB0(s->current, (s8)((MapPosition *)data_0200F3B8)->x,
                                         (s8)((MapPosition *)data_0200F3B8)->y)) {
                func_08141540(106);
                break;
            }
            s->target_x = ((MapPosition *)data_0200F3B8)->x;
            s->target_y = ((MapPosition *)data_0200F3B8)->y;
            func_0802D704(func_0802D72C(1));
            func_0802D704(func_0802D72C(0));
            if ((u16)((MapPosition *)data_0200F3B8)->x == s->current->record[0xf6] &&
                (u16)((MapPosition *)data_0200F3B8)->y == s->current->record[0xf7]) {
                func_08141540(100);
                func_0802D704(func_0802D72C(1));
                func_0802D704(func_0802D72C(0));
                func_08024ABC(data_0200F3AC, 4);
                s->other = s->current;
                if ((u16)((MapPosition *)data_0200F3B8)->x == s->current->record[0xf6] &&
                    (u16)((MapPosition *)data_0200F3B8)->y == s->current->record[0xf7]) {
                    *state = 21;
                    SAVE_STATE(); *state = 79;
                } else {
                    *state = 38;
                    SAVE_STATE(); *state = 21;
                }
                break;
            }
            s->path_count = func_0809A604(s->current, data_0200F3B8[0], data_0200F3B8[4],
                              (u8)((u32)func_080CA3EC(s->current->record) / 10), s->path);
            func_08024ABC(data_0200F3AC, 0);
            s->other = s->current;
            *state = 38;
            SAVE_STATE(); *state = 21;
            SAVE_STATE(); *state = 29;
            SAVE_STATE(); *state = 76;
            SAVE_STATE(); *state = 19;
            SAVE_STATE(); *state = 45;
            SAVE_STATE(); *state = 21;
            if (func_0809D8F0(s->current)) {
                SAVE_STATE(); *state = 40;
                SAVE_STATE(); *state = 79;
                SAVE_STATE(); *state = 96;
            } else {
                SAVE_STATE(); *state = 79;
                SAVE_STATE(); *state = 40;
            }
            SAVE_STATE(); *state = 44;
            SAVE_STATE(); *state = 21;
            SAVE_STATE(); *state = 99;
            func_08141540(100);
            break;
        }
        func_080B5880(s->actor, data_0200F3B8[0], data_0200F3B8[4]);
        break;
    case 42:
        if ((u8)func_080C7650())
            break;
        func_080C71B4(0);
        goto pop_state;
    case 44:
        if (func_080C95A8(13))
            *flags |= 0x2000;
        goto pop_state;
    case 45:
        if (func_080C95A8(13))
            *flags &= ~0x2000;
        goto pop_state;
    case 40:
        *state = 41;
    case 41:
        func_0809A664(s->current->unknown_80, 0);
        func_0809A63C(s->current, 1);
        if ((s32)s->path_count <= 1) {
            func_080C9574(4, 1);
            func_0809A664(s->current->unknown_80, 1);
            goto pop_state;
        }
        if (func_080C95A8(13))
            *flags |= 0x2000;
        record = (void *)func_080C7EA4(s->current->record, 0x44);
        func_0809D464(s->effect, s->current, s->path, s->path_count);
        func_0809B818(s->effect);
        if (!func_0809D8F0(s->current))
            func_0809D7E4(s->current, 16, -120, -86);
        if (((u8 *)record)[1] == 4) {
            func_0809D638(s->effect, 3);
            func_0809D620(s->effect, 2, 2, 2, 2);
        }
        *state = 43;
        data_08394054(s->current->animation, 1);
        data_08394054(s->current->secondary_animation, 1);
        func_0809993C(s->actor, 1);
        func_080A9548();
        break;
    case 43:
        if (!(u8)func_080A9588())
            break;
        count = 1;
        value = 0;
        result = 0;
        moving = 0;
        if (!func_0809D8F0(s->current)) {
            if (func_080C95A8(13))
                count = (u8)func_080C19A8();
            if (func_080C8298(s->current->record))
                count = 2;
        }
        while (count) {
            result = func_0809B88C(s->effect);
            moving = 0;
            if (!func_0809D614(s->effect))
                moving = func_0809D640(s->actor, s->current);
            count--;
        }
        if (!func_0809D8F0(s->current))
            value = func_0809CAF4();
        if (result || value || moving)
            break;
        if (func_080C95A8(13))
            *flags &= ~0x2000;
        func_0809993C(s->actor, 0);
        func_080C9574(4, 1);
        func_0809A664(s->current->unknown_80, 1);
        func_0809A710(s->current);
        data_08394054(s->current->animation, 0);
        data_08394054(s->current->secondary_animation, 0);
        goto pop_state;
    case 21:
        func_080922CC(data_0200F4C0, s->other->x, s->other->z, s->other->y, -120, -86, 4, 100);
        *state = 22;
        break;
    case 22:
        if (func_08092390(data_0200F4C0))
            break;
        goto pop_state;
    case 29:
        func_08099E68(s->other, (s8)s->other->record[0xf6], (s8)s->other->record[0xf7]);
        if (s->other->direction != s->other->record[0xf8])
            func_0809836C(s->other, 0, (s8)s->other->record[0xf8], 0);
        func_0809A624(s->other);
        *state = 30;
        break;
    case 30:
        if (!func_08098A88(s->other))
            break;
        goto pop_state;
    case 79:
        func_0801D938();
        *state = 80;
        break;
    case 80:
        func_080231AC();
        s->wait = 2;
        *state = 81;
        break;
    case 81:
        if (--s->wait > 0)
            break;
        goto pop_state;
    case 89:
        if (s->target_x == s->current->x >> 5 && s->target_y == s->current->y >> 5)
            goto pop_state;
        s->turn.unit = s->current;
        s->turn.delay = 8;
        s->turn.target = func_0809D6BC((s8)(s->target_x - (s->current->x >> 5)),
                                     (s8)(s->target_y - (s->current->y >> 5)));
        s->turn.ticks = 0;
        *state = 90;
        break;
    case 90:
        old_direction = s->current->direction;
        moving = (u8)func_0809D3A8(&s->turn);
        if (old_direction != s->current->direction && moving == 1)
            func_0809836C(s->current, 9, s->current->direction, 0);
        if (moving)
            break;
        func_0809836C(s->current, 0, s->current->direction, 0);
        goto pop_state;
    case 91:
        if (!s->ability)
            goto pop_state;
        func_08025688(0, s->ability, 0);
        s->timer = 0;
        *state = 92;
        break;
    case 92:
        s->timer++;
        if ((first & 3) && s->timer > 15)
            s->timer = 120;
        func_08025464();
        if (s->timer <= 119)
            break;
        s->timer = 0;
        func_08029514();
        s->action = 1;
        goto pop_state;
    case 3:
        goto pop_state;
    }
    return 1;

close_two_menus:
    POP_STATE();
    POP_STATE();
    s->action = 0;
    SAVE_STATE(); *state = 71;
    return 1;
wait_cinematic:
    SAVE_STATE(); *state = 52;
    SAVE_STATE(); *state = 51;
    func_080C71B4(2);
    return 1;
queue_cinematic:
    *state = 42;
    func_080C71B4(1);
    return 1;
pop_state:
    POP_STATE();
    return 1;
}
