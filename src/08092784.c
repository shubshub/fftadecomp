#include "ffta.h"

/* Complete target [0x08092784, 0x08096B2C): 17320 bytes, 7226 reachable instructions. */
typedef struct Unit Unit;
/* The unit's battle record (src/08099E68.c declares x and y at 0xF6, and
   src/08128C3C.c the MP at 0x1C, after the HP at 0x18). */
typedef struct {
    u8 unknown_00[0x1c];
    u16 mp;
    u8 unknown_1e[0xb8];
    u16 unknown_d6;
    u8 unknown_d8[0x1e];
    u8 x, y, direction;
    u8 unknown_f9[8];
    u8 unknown_101;
    u8 unknown_102[2];
    u8 unknown_104;
} UnitRecord;
typedef struct { u16 x, z, y, unknown_06; } MapPosition;
typedef struct { Unit *unit; u8 target; s8 delay; s8 ticks; } TurnState;
struct Unit {
    UnitRecord *record;
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
typedef struct { u16 current, depth, stack[34]; } Phase;
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
    Phase phase;
    u8 path[32][4];
    s32 path_count;
    s32 saved_height;
    s8 step;
    u8 timer, unknown_1ae[2];
    void *sub_menu;
    u32 saved_random;
} ActionState;
/* The map cursor object at 0x0200F3AC (func_08024ABC's argument); the ROM
   forms 0x0200F390 and 0x0200F3AC from one another (0x0809306E, 0x08093D2A). */
typedef struct {
    u8 unknown_00[4];
    u8 view;
    u8 unknown_05[5];
    u8 position_changed;
    u8 unknown_0b;
    MapPosition position, destination;
    u8 unknown_1c[0x5c];
    u16 flags;
} MapCursor;
typedef struct {
    u8 unknown_00[2], mode, unknown_03[0x19];
    MapCursor cursor;
} MapControl;
/* The selection record at 0x0200F6A0 (src/08092638.c's State08092638). */
typedef struct { Unit *unit; u8 x, y; u8 unknown_06[0x4e]; } SelectionState;
extern MapControl g_state_0200F390;
extern u8 g_state_02000080[];
/* The battle record at 0x02000000 (src/08024108.c reads flags at 0x3C24). */
typedef struct {
    u8 unknown_0000[0x2FC0];
    u8 unknown_2fc0;
    u8 unknown_2fc1[0xC63];
    u32 flags;
    u8 unknown_3c28[6];
    u16 ability;
    u8 unknown_3c30[0x6C];
    u16 unknown_3c9c;
} BattleState;
extern BattleState g_state_02000000;
/* The link state at 0x030028A0 (src/08062430.c, src/08005028.c). */
typedef struct {
    u8 flags;
    u8 unknown_01;
    u8 type;
    u8 unknown_03[0x121];
    /* Tested as (mode & 0xFFFF): S59 loads the mask before the halfword
       load and its pop reuses it (0x08095C6E, 0x08095CB2). */
    u32 mode;
} LinkState;
extern LinkState data_030028A0;
extern u8 data_0200F4C0[];
extern SelectionState data_0200F6A0;
extern u8 g_table_0854CD54[][40];
extern void (*data_0839403C)(void *);
extern void (*data_08394054)(void *, u32);
extern void (*const g_callbacks_0836D4B8[])(void *, u32);

/* The cursor tile, taken by address as src/0804CBB4.c takes SELECTION: the
   ROM loads the position's own address 0x0200F3B8 and reads [r,#0] and
   [r,#4] (0x08094520, 0x080945B0), and forms the cursor object as that
   address - 0xC (0x08094772).  Member reads go through 0x0200F390 + 0x28. */
#define CURSOR_TILE (&g_state_0200F390.cursor.position)

/* Centre the map cursor on a unit.  Each copy builds the packed position in a
   stack slot of its own (0x08092D72, 0x08093036, ...), as a block-scope local
   in a statement macro does.  A plain braced block: the nine copies' positions
   are all spilled while S82's open-coded one stays in r5:r6 (0x0809448A),
   which needs these references outside any loop. */
#define FOCUS_ON_UNIT(unit)                                                 \
    {                                                                       \
        MapPosition position;                                               \
        position.x = (unit)->x >> 5;                                        \
        position.y = (unit)->y >> 5;                                        \
        position.z = (unit)->z >> 4;                                        \
        g_state_0200F390.cursor.position = g_state_0200F390.cursor.destination = position; \
        g_state_0200F390.cursor.position_changed = 1;                              \
    }

/* Close a unit's turn.  The ROM repeats these three calls six times with the
   unit loaded once into r4 (0x08093306, 0x0809379E, 0x08093C46, 0x0809564C,
   0x0809620A, 0x08096274). */
#define FINISH_UNIT(unit)                                                   \
    {                                                                       \
        Unit *finished = (unit);                                            \
                                                                            \
        func_0809F8EC(finished->record);                                    \
        func_08096F8C(finished);                                            \
        func_080A9548();                                                    \
    }

/* The state stack.  Expression macros on a Phase pointer: S84 assigns the
   value of a pop to the current state again, and the ROM re-reads the
   popped slot for it (0x080947FC: ldrh/strh twice through r0). */
#define PushState(phase) ((phase)->stack[(phase)->depth++] = (phase)->current)
#define PopState(phase) ((phase)->current = (phase)->stack[--(phase)->depth])
#define ClearStates(phase) ((phase)->depth = 0)
#define SAVE_STATE() PushState(&s->phase)
#define POP_STATE() PopState(&s->phase)

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

extern void func_080917F8(void *);
extern void *func_0809185C(u32),*func_08091DC0(void);

extern void func_08092288(void *),func_080922C4(void *);
extern void func_080922CC(void *,s16,s16,s16,s32,s32,s32,s32);
extern u32 func_08092390(void *);
extern u32 func_080924F4(void *,void *);

extern void func_08092638(void *,u8,u8);
extern void *func_08096D7C(void);
extern void func_08096F8C(void *),func_08098130(void *),func_0809836C(void *,u32,s8,u32);
extern u32 func_08098A88(void *);
extern Unit *func_08099544(void *),*func_08099560(void *,void *),*func_08099644(void *,s8,s8);
extern void func_0809993C(void *,u8),func_08099A70(void *,void *);
extern void *func_08099C30(void *);
extern s32 func_08099CDC(void *,Unit **);
extern void func_08099E68(void *,s8,s8),func_08099EA0(void *),func_08099F00(void *);
extern s32 func_08099FB0(void *,s32,s32);
extern void func_0809A260(void *,u32),func_0809A5C0(void *,u8),func_0809A5E0(void *,u8,void *);
extern s32 func_0809A604(void *,u8,u8,u8,void *);
extern void func_0809A624(void *),func_0809A63C(void *,u8),func_0809A664(void *,u8),func_0809A710(void *);

extern void func_0809A950(void *,s32),func_0809A9A8(void *),func_0809A9CC(void *);
extern Unit *func_0809AA38(void *,u8);
extern void func_0809B818(void *);
extern s32 func_0809B88C(void *),func_0809CAF4(void);
extern u32 func_0809D464(void *,void *,void *,u32), func_0809D614(void *);
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

extern void *func_080A7138(void *,void *);
extern void func_080A80C8(void *);
extern void *func_080A8194(void *,u16,u16,s8,s8,u8,u8);
extern void func_080A8264(void *);
extern u32 func_080A8270(void *);
extern void func_080A8288(void *,s16,s16,s16,s8);
extern s32 func_080A82C0(u16,u16);
extern void *func_080A8934(void *),*func_080A899C(void *),*func_080A89D8(void *,void *,u8 *);
extern void func_080A8940(void *),func_080A8A54(void *,void *),func_080A8A64(void *);

extern u8 func_080A8A80(void *);
extern void *func_080A8A90(void *);
extern void func_080A8AAC(void *),func_080A9528(void),func_080A9548(void);

extern void func_080B5880(void *,u8,u8);
extern u32 func_080B7E08(void *,u16,u16);
extern void *func_080B7E1C(void *,u16,u16,u8,u8,u8);
extern void func_080B7E7C(void *),func_080B7EDC(void *,s8 *,s8 *),func_080B7EFC(void *,s8,s8),func_080B7F18(void *,u8),func_080B7F4C(void);
extern void *func_080B8100(void *,void *,u32);

extern void func_080BA6D0(void *),func_080BC780(void *,u16);
extern u8 func_080BC798(void);

extern void func_080BC7D4(void *,void *,void *,u8),func_080BC878(void *,void *,u8,u8),func_080BC8C4(void *),func_080BC8E8(void *,void *,u8,u8);

extern void *func_080BC914(void *,u16),*func_080BC950(void *);
extern u8 func_080BC934(void *),func_080BC984(void *),func_080BC9B8(void *),func_080BC9CC(void *);
extern void func_080BC944(void *),func_080BC994(void *),func_080BC9E4(void *);
extern void *func_080BCA24(void *);
extern u8 func_080BCA40(void *,u16);
extern void func_080BCA54(void *);
extern void *func_080BD328(void);
extern void func_080BD340(void *);

extern u32 func_080C1438(void);
extern void func_080C144C(void *),func_080C1460(void);
extern s32 func_080C1484(s32);
extern void func_080C14B0(s8 *,s8 *),func_080C14D8(s8 *,s8 *);
extern u32 func_080C1514(void), func_080C1528(void);
extern void func_080C15C0(void),func_080C15DC(u8,u8,u32),func_080C1654(u8,u8,u16,u16,u8),func_080C1700(u8),func_080C1748(void),func_080C1780(void),func_080C17B8(void),func_080C17C8(void);
extern u32 func_080C1994(void), func_080C19F0(void);
extern void func_080C1980(u32),func_080C19BC(u32),func_080C19DC(u8),func_080C1A04(u8,u16,u8,u8);
extern u32 func_080C1A78(u8,s8 *,s8 *), func_080C1B18(void);
extern void func_080C1AD4(u16),func_080C71B4(u16),func_080C7214(void),func_080C7240(void),func_080C7284(void);

extern void func_080C7378(void),func_080C738C(void),func_080C7668(u32);
extern s32 func_080C7EA4(const void *,u32);
extern u8 func_080C8298(void *),func_080C9540(u16),func_080C95A8(u16);
extern void func_080C9574(u16,u32),func_080C95C0(u16,u32);
extern s32 func_080CA3EC(const void *);
extern u32 func_080CCD50(u16,u8),func_080CD584(void *);
extern u8 func_080CD944(void *),func_080CD95C(void *),func_080CDA7C(void *),func_080CDB54(void *),func_080CDB6C(void *),func_080CDB9C(void *),func_080CDBB4(void *);
extern void func_080CDEA4(void *,u8),func_081219F4(void);
extern u8 func_0812E4A8(void *),func_0812F1AC(u16),func_08134B38(void *),func_08134B88(void *,u8,u8),func_08135624(void *);
extern void func_08141540(u16);
extern u32 func_08149368(void *);
extern u8 func_0808FA98(void *,u16,u16);
extern u8 func_08091930(void *,u16,u16);
extern u8 func_08091E48(void *);
extern u8 func_080922A4(void *);
extern u8 func_080925A4(void *);
extern u8 func_0809A204(void *);
extern u8 func_0809A900(void *);
extern u8 func_0809D3A8(TurnState *);
extern u8 func_0809F9D8(void *);
extern u8 func_080A8958(void *);
extern u8 func_080A8A68(void *,u16,u16);
extern u8 func_080A9588(void);
extern u8 func_080B8414(void *,u16,u16);
extern u8 func_080BC7FC(void);
extern u8 func_080BC810(void *,u8,u8);
extern u8 func_080BC900(void);
extern u8 func_080BD34C(void *);
extern u8 func_080C1500(void);
extern u8 func_080C153C(void);
extern u8 func_080C1920(void *);
extern u8 func_080C19A8(void);
extern u8 func_080C1B2C(void *);
extern u8 func_080C72E4(void);
extern u8 func_080C72F8(void);
extern u8 func_080C75F4(void);
extern u8 func_080C7650(void);
extern u8 func_080C76C4(void);
/* An inlined copy of func_08096F3C (src/08096F3C.c). */
static inline void MoveCamera(s16 x, s16 y, s16 z)
{
    func_080922CC(data_0200F4C0, x, y, z, -120, -86, 4, 100);
}

u32 func_08092784(void *object, u16 first, u16 second)
{
    ActionState *s = object;

    if (func_080C95A8(13)) {
        if (s->flags & 0x4000)
            return 1;
        if (s->flags & 0x800) {
            if (func_080C72F8()) {
                if (!(s->flags & 0x10000))
                    s->flags = (s->flags & ~0x800) | 0x1000;
            } else {
                s->flags &= ~0x10000;
            }
        }
        if (!(s->flags & 0x2000)) {
            if (s->flags & 0x1000) {
                func_08004C40();
                func_081219F4();
                s->flags |= 0x6000;
            }
        }
        if (s->flags & 0x4000)
            return 1;
    }
    if (s->action == 1) {
        s32 result = (s16)func_08025464();

        if (!result)
            return 1;
        if (result < 0)
            s->action = 0;
        else
            s->action = 2;
    }
    if (s->flags & 0x40) {
        if (s->tracking == s->current || !s->tracking || !s->current || !func_0812E4A8(s->tracking->record)) {
            s->flags &= ~0x40;
        } else if (s->flags & 0x80) {
            s32 old_direction = s->tracking->direction;
            s32 moving = func_0809D3A8(&s->tracking_turn);

            if (old_direction != s->tracking->direction && moving == 1) {
                func_0809836C(s->tracking, 9, s->tracking->direction, 0);
                data_0839403C(s->tracking->animation);
                s->tracking->record->direction = old_direction;
            } else if (!moving) {
                func_0809836C(s->tracking, 0, s->tracking->direction, 0);
                data_0839403C(s->tracking->animation);
                s->flags &= ~0x80;
            }
        } else {
            if (s->current->x >> 5 != s->tracking->record->x || s->current->y >> 5 != s->tracking->record->y) {
                s32 value = func_0809D6BC((s->current->x >> 5) - s->tracking->record->x, (s->current->y >> 5) - s->tracking->record->y);
                if (value != s->tracking->direction) {
                    s->tracking->record->direction = value;
                    s->flags |= 0x80;
                    s->tracking_turn.unit = s->tracking;
                    s->tracking_turn.delay = 8;
                    s->tracking_turn.target = value;
                    s->tracking_turn.ticks = 0;
                }
            }
        }
    }

    switch (s->phase.current) {
    case 8:
        if (g_state_0200F390.cursor.flags & 1)
            break;
        if (g_state_0200F390.cursor.flags & 2) {
            s->phase.current = 13;
            if (func_080C95A8(13)) {
                SAVE_STATE();
                s->phase.current = 45;
            }
            break;
        }
        if (!(g_state_0200F390.cursor.flags & 4))
            break;
        s->phase.current = 11;
        SAVE_STATE(); s->phase.current = 9;
        SAVE_STATE(); s->phase.current = 15;
        break;
    case 9:
        s->dialog = func_08021854(func_08099C30(s->actor), 0);
        s->phase.current = 10;
        break;
    case 10:
        if (func_0802192C(s->dialog, 1))
            break;
        func_0802200C(s->dialog);
        POP_STATE();
        break;
    case 11:
        func_080BC780(s->actor, func_0800A018());
        s->phase.current = 12;
        break;
    case 12: {
        if (func_080BC798())
            break;
        if (func_080C95A8(13))
            func_080C9574(0x42, (data_030028A0.flags >> 3) & 1);
        s->tracking = func_08099544(s->actor);
        if (!(g_state_0200F390.cursor.flags & 0x80)) {
            Unit **units;
            s32 n, i;

            units = func_08022840(0x34);
            n = func_08099CDC(s->actor, units);
            for (i = 0; i < n; i++)
                func_0809836C(units[i], 10, units[i]->record->direction, 0);
            func_08022854(units);
            func_0809A9A8(s->actor);
            func_0809A9CC(s->actor);
            s->phase.current = 0;
            break;
        }
        s->current = func_0809AA38(s->actor, func_080C95A8(0x34));
        if (!s->current) {
            s->phase.current = 0;
            break;
        }
        if (func_080924F4(s->current->record, s->actor)) {
            s->phase.current = 0;
            break;
        }
        FOCUS_ON_UNIT(s->current);
        s->flags |= 0x40;
        func_0809A5C0(s->actor, 0);
        s->other = s->current;
        s->phase.current = 19;
        SAVE_STATE(); s->phase.current = 21;
        SAVE_STATE(); s->phase.current = 2;
        break;
    }
    case 6:
        if (!func_080A9588())
            break;
        if (!func_0800A5C8(s->sound)) {
            POP_STATE();
            break;
        }
        s->flags &= ~0xc0;
        func_08009FD0();
        s->phase.current = 7;
        break;
    case 7:
        if (func_08009FBC()) {
            if (!(g_state_0200F390.cursor.flags & 8))
                break;
            SAVE_STATE(); s->phase.current = 106;
            break;
        }
        s->flags |= 0x40;
        POP_STATE();
        break;
    case 15:
        s->text = func_0808F8E8(g_table_0854CD54[func_0800A024()]);
        s->phase.current = 16;
        break;
    case 16:
        if (func_0808FA98(s->text, first, second))
            break;
        func_0808F848(s->text);
        POP_STATE();
        break;
    case 13:
        func_080A9548();
        if (!func_080A9588())
            break;
        s->sub_menu = func_080B8100(s->actor, g_state_02000080, 0x18);
        s->phase.current = 14;
        break;
    case 14:
        if (func_080B8414(s->sub_menu, first, second))
            break;
        func_080BA6D0(s->sub_menu);
        g_state_0200F390.cursor.flags &= 0xfffd;
        s->phase.current = 8;
        break;
    case 0:
        if (!func_080A9588())
            break;
        if (func_080C95A8(13))
            func_080C19BC(1);
        s->phase.current = 1;
        if (func_080C95A8(13)) {
            SAVE_STATE(); s->phase.current = 52;
            SAVE_STATE(); s->phase.current = 51;
            func_080C71B4(2);
            break;
        }
    case 1:
        if (func_0802D72C(1))
            func_0802D704(func_0802D72C(1));
        s->current = 0;
        s->phase.current = 5;
        s->tracking = func_08099544(s->actor);
        if (!s->tracking)
            break;
        s->other = s->tracking;
        SAVE_STATE();
        s->phase.current = 77;
        s->saved_height = 255;
        break;
    case 5:
        if (func_0802D72C(1)) {
            if ((func_0802B880(func_0802D72C(1)) & ~0x10) != 3)
                break;
        }
        func_08024ABC(&g_state_0200F390.cursor, 0);
        ClearStates(&s->phase);
        s->saved_mode_count = 0;
        func_080C9574(3, 0);
        func_080C9574(4, 0);
        s->current = func_0809F850(s->actor);
        if (!s->current)
            break;
        func_080C95C0(0x34, s->current->record->unknown_104);
        FOCUS_ON_UNIT(s->current);
        s->flags |= 0x40;
        {
            s16 mp = func_080C7EA4(s->current->record, 0x15);

            mp += 5;
            if (mp > (u32)func_080C7EA4(s->current->record, 0x16))
                mp = func_080C7EA4(s->current->record, 0x16);
            s->current->record->mp = mp;
        }
        s->other = s->current;
        func_080255FC(4);
        s->flags &= ~4;
        {
            s32 count = s->current->record->unknown_101 + 1;

            if (count > 255)
                count = 255;
            s->current->record->unknown_101 = count;
        }
        s->sound = 3;
        s->phase.current = 4;
        SAVE_STATE(); s->phase.current = 6;
        SAVE_STATE(); s->phase.current = 2;
        break;
    case 4:
        s->phase.current = 19;
        if (func_080924F4(s->current->record, s->actor)) {
            SAVE_STATE(); s->phase.current = 33;
            SAVE_STATE(); s->phase.current = 25;
            if (func_080C8298(s->current->record)) {
                SAVE_STATE(); s->phase.current = 23;
            }
            SAVE_STATE(); s->phase.current = 31;
            SAVE_STATE(); s->phase.current = 76;
        }
        SAVE_STATE(); s->phase.current = 20;
        s->auxiliary = 0;
        if (s->tracking && s->tracking != s->current && func_08135624(s->current->record)) {
            s->auxiliary = func_08134B38(s->current->record);
            SAVE_STATE(); s->phase.current = 17;
        }
        SAVE_STATE(); s->phase.current = 111;
        SAVE_STATE(); s->phase.current = 21;
        SAVE_STATE(); s->phase.current = 76;
        break;
    case 111:
        if (!func_0809F9D8(s->current)) {
            u32 old_appearance = s->current->appearance;
            u8 old_kind = s->current->kind;

            func_08098130(s->current);
            if (old_appearance != s->current->appearance || old_kind != s->current->kind)
                func_0809836C(s->current, 10, s->current->direction, 0);
            POP_STATE();
            break;
        }
        s->motion = func_0809F9A8(s->current);
        s->phase.current = 112;
        break;
    case 112: {
        u32 old_appearance;
        u8 old_kind;

        if (func_0809F9C0(s->motion))
            break;
        func_0809F9D0(s->motion);
        s->motion = 0;
        old_appearance = s->current->appearance;
        old_kind = s->current->kind;
        func_08098130(s->current);
        if (old_appearance != s->current->appearance || old_kind != s->current->kind)
            func_0809836C(s->current, 10, s->current->direction, 0);
        if (func_0812E4A8(s->current->record)) {
            POP_STATE();
            break;
        }
        FINISH_UNIT(s->current);
        func_080C9574(3, 1);
        func_080C9574(4, 1);
        ClearStates(&s->phase);
        s->other = s->current;
        s->sound = 6;
        s->phase.current = 0;
        SAVE_STATE(); s->phase.current = 6;
        break;
    }
    case 2:
        func_08099A70(s->actor, s->current);
        POP_STATE();
        break;
    case 3:
        /* Folded into case 92's pop at 0x08096B00 (the last case). */
        POP_STATE();
        break;
    case 23:
        s->flags &= ~0xc0;
        func_080A9528();
        s->menu = func_080BC950(s->actor);
        s->phase.current = 24;
        break;
    case 24: {
        s32 value;

        if (!func_080A9588())
            break;
        if (func_080BC984(s->menu)) {
            if (!func_080BC9CC(s->menu))
                break;
            func_080BC9E4(s->menu);
            func_080A9548();
            SAVE_STATE(); s->phase.current = 33;
            break;
        }
        value = func_080BC9B8(s->menu);
        func_080BC994(s->menu);
        s->menu = 0;
        POP_STATE();
        if (value) {
            s->phase.current = 26;
            s->other = s->current;
            SAVE_STATE(); s->phase.current = 76;
        }
        break;
    }
    case 25:
        func_080A9528();
        s->phase.current = 26;
        break;
    case 26:
        if (!func_080A9588())
            break;
        s->flags = (s->flags | 4) & ~8;
        func_080C144C(s->current);
        s->phase.current = 27;
        s->delay = 40;
        SAVE_STATE(); s->phase.current = 96;
        break;
    case 27:
        if (s->delay)
            s->delay--;
        if (!(s->flags & 8)) {
            if (func_080C1438())
                break;
            s->flags |= 8;
            func_080C1460();
        }
        if (s->delay)
            break;
        s->step = 0;
        func_080A9548();
        POP_STATE();
        if (!func_080C95A8(13) || !func_080C1B2C(s->current))
            break;
        func_080C15C0();
        func_080C17C8();
        func_080C19BC(1);
        func_080C1980(*func_08002830());
        func_080C17B8();
        SAVE_STATE();
        s->phase.current = 42;
        func_080C71B4(1);
        break;
    case 98:
        func_08141540(100);
        func_0801D624(s->target_x, s->target_y, 2);
        func_0801D918();
        s->phase.current = 99;
        SAVE_STATE(); s->phase.current = 96;
        MoveCamera(s->target_x * 32 + 16, func_0801CC18(s->target_x, s->target_y) << 4,
                   s->target_y * 32 + 16);
        SAVE_STATE(); s->phase.current = 22;
        break;
    case 99: {
        s32 x, y;

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
        POP_STATE();
        break;
    }
    case 96:
        s->timer = 12;
        s->phase.current = 97;
        break;
    case 97:
        if (--s->timer)
            break;
        POP_STATE();
        break;
    case 28: {
        s32 value, i;

        if (!func_080924F4(s->current->record, s->actor)) {
            s->flags &= ~4;
            ClearStates(&s->phase);
            s->phase.current = 19;
            if (func_080C95A8(13) && (data_030028A0.flags & 8)) {
                func_080C15C0();
                func_080C1700(s->current->direction);
                func_080C19BC(1);
                func_080C17B8();
                SAVE_STATE();
                s->phase.current = 42;
                func_080C71B4(1);
                break;
            }
            break;
        }
        func_080C71B4(0);
        switch (func_080C1484(s->step)) {
        case 0:
            value = func_080C1500();
            if (s->current->direction != value)
                func_0809836C(s->current, 0, value, 0);
            if (!func_080C9540(3)) {
                g_state_02000000.flags &= ~2;
                g_state_02000000.ability = 0xffff;
            }
            FINISH_UNIT(s->current);
            func_080C9574(3, 1);
            func_080C9574(4, 1);
            s->sound = 6;
            s->phase.current = 0;
            SAVE_STATE(); s->phase.current = 6;
            SAVE_STATE(); s->phase.current = 33;
            break;
        case 2:
            func_080C14B0(&s->target_x, &s->target_y);
            s->path_count = func_0809A604(s->current, s->target_x, s->target_y,
                              (u8)func_080CA3EC(s->current->record) / 10, s->path);
            s->target_x = s->path[s->path_count - 1][0];
            s->target_y = s->path[s->path_count - 1][1];
            s->phase.current = 19;
            SAVE_STATE(); s->phase.current = 45;
            SAVE_STATE(); s->phase.current = 21;
            if (func_0809D8F0(s->current)) {
                SAVE_STATE(); s->phase.current = 40;
                SAVE_STATE(); s->phase.current = 79;
                SAVE_STATE(); s->phase.current = 96;
            } else {
                SAVE_STATE(); s->phase.current = 79;
                SAVE_STATE(); s->phase.current = 40;
            }
            SAVE_STATE(); s->phase.current = 21;
            SAVE_STATE(); s->phase.current = 96;
            SAVE_STATE(); s->phase.current = 98;
            SAVE_STATE(); s->phase.current = 96;
            SAVE_STATE(); s->phase.current = 21;
            s->other = s->current;
            SAVE_STATE(); s->phase.current = 29;
            SAVE_STATE(); s->phase.current = 33;
            SAVE_STATE(); s->phase.current = 44;
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
            s->flags |= 1;
            if (func_080C153C())
                s->flags |= 2;
            if (func_0812F1AC(s->ability))
                s->flags |= 0x20;
            else
                s->flags &= ~0x20;
            s->other = s->current;
            s->phase.current = 19;
            SAVE_STATE(); s->phase.current = 21;
            if (s->ability == 0x21) {
                SAVE_STATE(); s->phase.current = 48;
            }
            SAVE_STATE(); s->phase.current = 48;
            SAVE_STATE(); s->phase.current = 33;
            break;
        case 4:
            SAVE_STATE(); s->phase.current = 26;
            s->other = s->current;
            SAVE_STATE(); s->phase.current = 76;
            break;
        case 5:
            s->other = s->current;
            s->message_id = func_080C1B18();
            func_080A9548();
            SAVE_STATE(); s->phase.current = 25;
            SAVE_STATE(); s->phase.current = 31;
            SAVE_STATE(); s->phase.current = 69;
            SAVE_STATE(); s->phase.current = 118;
            SAVE_STATE(); s->phase.current = 33;
            break;
        case 6:
            s->other = s->current;
            func_080A9548();
            SAVE_STATE(); s->phase.current = 126;
            SAVE_STATE(); s->phase.current = 52;
            SAVE_STATE(); s->phase.current = 50;
            SAVE_STATE(); s->phase.current = 33;
            break;
        }
        s->step++;
        break;
    }
    case 76:
        s->saved_height = s->other->height;
    case 77:
        s->other->height = 0x30;
        func_08099EA0(s->other);
        func_08099F00(s->other);
        s->phase.current = 78;
        break;
    case 78:
        func_0809A5E0(s->actor, 1, s->other);
        if (!func_08149368(s->other->render))
            break;
        s->other->height = s->saved_height;
        func_0809A5C0(func_08096D7C(), 1);
        POP_STATE();
        break;
    case 20:
        if (func_0812E4A8(s->current->record)) {
            POP_STATE();
            break;
        }
        func_080C9574(3, 1);
        func_080C9574(4, 1);
        FINISH_UNIT(s->current);
        ClearStates(&s->phase);
        s->phase.current = 0;
        break;
    case 19:
        s->flags |= 0x40;
        if (!func_080925A4(s->current->record)) {
            if (s->flags & 4) {
                s->phase.current = 28;
                SAVE_STATE(); s->phase.current = 76;
            } else {
                s->phase.current = 46;
            }
            break;
        }
        if (s->flags & 4) {
            s->phase.current = 28;
            SAVE_STATE(); s->phase.current = 76;
            break;
        }
        s->flags &= ~1;
        FOCUS_ON_UNIT(s->current);
        func_08024ABC(&g_state_0200F390.cursor, 4);
        s->other = s->current;
        s->phase.current = 35;
        if (!(s->flags & 0x10)) {
            SAVE_STATE(); s->phase.current = 31;
        }
        s->flags &= ~0x10;
        func_080A9528();
        func_080C71B4(7);
        break;
    case 31:
        s->message = func_0802B70C(s->other->record, 0);
        s->phase.current = 32;
        break;
    case 32:
        if ((func_0802B880(func_0802D72C(1)) & ~0x10) == 2) {
            POP_STATE();
            break;
        }
        break;
    case 33:
        func_0802D704(s->message);
        s->phase.current = 34;
        break;
    case 34:
        if ((func_0802B880(func_0802D72C(1)) & ~0x10) == 3) {
            POP_STATE();
            break;
        }
        break;
    case 35:
        s->flags &= ~0x22;
        func_080294E4(s->current->record);
        func_0802542C(4);
        s->action = 1;
        s->phase.current = 37;
        break;
    case 36:
        FOCUS_ON_UNIT(s->current);
        func_08024ABC(&g_state_0200F390.cursor, 4);
        s->flags &= ~0x22;
        func_080294E4(s->current->record);
        func_08025448(4);
        s->action = 1;
        s->phase.current = 37;
        break;
    case 37:
        if (!s->action) {
            if (!func_080C9540(4)) {
                s->phase.current = 19;
                SAVE_STATE(); s->phase.current = 82;
                s->flags |= 0x10;
            } else {
                func_08024ABC(&g_state_0200F390.cursor, 0);
                POP_STATE();
                SAVE_STATE(); s->phase.current = 33;
            }
            break;
        }
        switch (func_080254A0() - 7) {
        case 0:
            if (func_080C9540(4)) {
                s->phase.current = 19;
                break;
            }
            s->phase.current = 19;
            SAVE_STATE(); s->phase.current = 38;
            s->other = s->current;
            SAVE_STATE(); s->phase.current = 29;
            SAVE_STATE(); s->phase.current = 76;
            SAVE_STATE(); s->phase.current = 33;
            break;
        case 1:
            s->phase.current = 19;
            func_080C9574(3, 1);
            break;
        case 5:
            s->phase.current = 36;
            SAVE_STATE(); s->phase.current = 31;
            SAVE_STATE(); s->phase.current = 48;
            SAVE_STATE(); s->phase.current = 33;
            s->ability = 0;
            s->chain_index = 0;
            s->variant = 255;
            break;
        case 6: case 7: case 8:
            s->phase.current = 36;
            SAVE_STATE(); s->phase.current = 72;
            break;
        case 9:
            s->ability = func_080CD584(s->current->record);
            s->chain_index = 0;
            s->variant = 255;
            s->phase.current = 36;
            SAVE_STATE(); s->phase.current = 31;
            SAVE_STATE(); s->phase.current = 48;
            SAVE_STATE(); s->phase.current = 33;
            s->flags |= 0x20;
            break;
        case 10:
            s->phase.current = 36;
            SAVE_STATE(); s->phase.current = 31;
            SAVE_STATE(); s->phase.current = 48;
            SAVE_STATE(); s->phase.current = 33;
            s->flags |= 2;
            s->ability = 0;
            s->chain_index = 0;
            s->variant = 255;
            break;
        case 2:
            s->phase.current = 19;
            SAVE_STATE(); s->phase.current = 46;
            break;
        case 3:
            s->phase.current = 36;
            SAVE_STATE(); s->phase.current = 31;
            func_080A9548();
            SAVE_STATE(); s->phase.current = 72;
            func_080294E4(s->current->record);
            break;
        case 4:
            s->phase.current = 19;
            SAVE_STATE(); s->phase.current = 113;
            SAVE_STATE(); s->phase.current = 33;
            func_080A9548();
            func_080255FC(4);
            break;
        }
        break;
    case 113:
        func_0809A260(s->actor, 0);
        s->saved_modes[s->saved_mode_count++] = g_state_0200F390.cursor.view;
        func_08024ABC(&g_state_0200F390.cursor, 0);
        s->unit_menu = func_080A8A90(s->current);
        s->phase.current = 114;
        break;
    case 114:
        if (func_080A8A80(s->unit_menu))
            break;
        func_080A8AAC(s->unit_menu);
        s->unit_menu = 0;
        func_08024ABC(&g_state_0200F390.cursor, s->saved_modes[--s->saved_mode_count]);
        func_0809A260(s->actor, 1);
        POP_STATE();
        break;
    case 72:
        if (!func_080A9588())
            break;
        func_080C7214();
        g_state_0200F390.cursor.flags &= 0xffdf;
        g_state_0200F390.cursor.flags &= 0xffbf;
        s->chain_index = 0;
        g_state_0200F390.mode = 1;
        func_08024ABC(&g_state_0200F390.cursor, 0);
        s->phase.current = 75;
        break;
    case 73: case 74:
        s->phase.current = 74;
        g_state_0200F390.mode = 2;
        func_08024ABC(&g_state_0200F390.cursor, 0);
        s->phase.current = 75;
        break;
    case 75:
        if (g_state_0200F390.mode & 0x80) {
            g_state_0200F390.mode = 0;
            func_080C71B4(7);
            func_080A9528();
            POP_STATE();
            break;
        }
        if (g_state_0200F390.mode)
            break;
        s->phase.current = 73;
        if (!(g_state_0200F390.cursor.flags & 0x40))
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
            SAVE_STATE(); s->phase.current = 31;
        }
        SAVE_STATE(); s->phase.current = 48;
        SAVE_STATE(); s->phase.current = 33;
        func_080A9528();
        break;
    case 93:
        func_0802542C(10);
        s->action = 1;
        func_08024ABC(&g_state_0200F390.cursor, 4);
        s->phase.current = 95;
        break;
    case 94:
        func_08024ABC(&g_state_0200F390.cursor, 4);
        func_08025448(10);
        s->action = 1;
        s->phase.current = 95;
        break;
    case 95:
        if (!s->action) {
            POP_STATE();
            func_08024ABC(&g_state_0200F390.cursor, s->saved_modes[--s->saved_mode_count]);
            s->selection = -1;
            break;
        }
        if (s->action != 2)
            break;
        s->action = 0;
        s->phase.current = 94;
        SAVE_STATE(); s->phase.current = 31;
        func_080A9548();
        SAVE_STATE(); s->phase.current = 72;
        break;
    case 82:
        {
            MapPosition position;
            position.x = s->other->x >> 5;
            position.y = s->other->y >> 5;
            position.z = s->other->z >> 4;
            g_state_0200F390.cursor.position = g_state_0200F390.cursor.destination = position;
            g_state_0200F390.cursor.position_changed = 1;
            g_callbacks_0836D4B8[0](&data_0200F6A0, sizeof(data_0200F6A0));
            data_0200F6A0.unit = s->other;
            data_0200F6A0.x = position.x;
            data_0200F6A0.y = position.y;
        }
    case 83:
        func_080A9528();
        func_08024ABC(&g_state_0200F390.cursor, 1);
        s->phase.current = 84;
        s->action = 0;
        break;
    case 84:
        func_08092638(s->actor, CURSOR_TILE->x, CURSOR_TILE->y);
        if ((first & 0x208) && !func_080C9540(4) && !func_080C9540(3)) {
            if (first & 0x200)
                s->flags |= 0x400;
            else
                s->flags &= ~0x400;
            func_08024ABC(&g_state_0200F390.cursor, 0);
            SAVE_STATE(); s->phase.current = 101;
            break;
        }
        if (first & 1) {
            Unit *unit = func_08099644(s->actor, CURSOR_TILE->x, CURSOR_TILE->y);

            if (unit && func_080C8298(unit->record))
                unit = 0;
            if (!unit || unit == s->current) {
                POP_STATE();
                s->other = s->current;
                if (data_0200F6A0.unit != s->current)
                    s->flags &= ~0x10;
                SAVE_STATE(); s->phase.current = 21;
                func_08024ABC(&g_state_0200F390.cursor, 4);
                if (data_0200F6A0.unit) {
                    if (data_0200F6A0.unit != s->current) {
                        SAVE_STATE(); s->phase.current = 33;
                    }
                } else {
                    SAVE_STATE(); s->phase.current = 34;
                }
                func_08024ABC(&g_state_0200F390.cursor, 4);
                FOCUS_ON_UNIT(s->other);
                break;
            }
            func_080294E4(unit->record);
            s->saved_modes[s->saved_mode_count++] = g_state_0200F390.cursor.view;
            func_08024ABC(&g_state_0200F390.cursor, 4);
            SAVE_STATE(); s->phase.current = 93;
            s->other = unit;
            SAVE_STATE(); s->phase.current = 32;
            SAVE_STATE(); s->phase.current = 21;
            break;
        }
        if (first & 2) {
            Unit *unit = func_08099644(s->actor, CURSOR_TILE->x, CURSOR_TILE->y);

            func_080A9548();
            func_08024ABC(&g_state_0200F390.cursor, 0);
            if (unit && func_080C8298(unit->record))
                unit = 0;
            if (!unit) {
                s->phase.current = 83;
                SAVE_STATE(); s->phase.current = 87;
                g_callbacks_0836D4B8[0](&data_0200F6A0, sizeof(data_0200F6A0));
                data_0200F6A0.y = data_0200F6A0.x = -1;
                SAVE_STATE(); s->phase.current = 33;
                break;
            }
            s->other = unit;
            /* The ROM reads the popped slot and stores it twice (0x080947FC). */
            s->phase.current = POP_STATE();
            SAVE_STATE(); s->phase.current = 82;
            SAVE_STATE(); s->phase.current = 31;
            SAVE_STATE(); s->phase.current = 21;
            SAVE_STATE(); s->phase.current = 79;
            SAVE_STATE(); s->phase.current = 85;
            SAVE_STATE(); s->phase.current = 29;
            SAVE_STATE(); s->phase.current = 76;
            SAVE_STATE(); s->phase.current = 21;
            SAVE_STATE(); s->phase.current = 76;
            SAVE_STATE(); s->phase.current = 33;
            break;
        }
        break;
    case 85:
        func_08024ABC(&g_state_0200F390.cursor, 3);
        s->phase.current = 86;
        break;
    case 86:
        if (second & 2)
            break;
        func_08024ABC(&g_state_0200F390.cursor, 0);
        s->selection3 = s->selection2 = s->selection = -1;
        POP_STATE();
        break;
    case 101:
        func_080A9548();
        if (!func_080A9588())
            break;
        func_08024ABC(&g_state_0200F390.cursor, 0);
        s->phase.current = 102;
        SAVE_STATE(); s->phase.current = 33;
        break;
    case 102:
        if (s->flags & 0x400)
            func_0802542C(17);
        else
            func_0802542C(1);
        func_080255FC(2);
        s->action = 1;
        s->phase.current = 103;
        break;
    case 103:
        if (s->action == 2) {
            switch (func_080254A0() - 1) {
            case 0:
                g_state_0200F390.mode = 1;
                s->action = 0;
                SAVE_STATE(); s->phase.current = 104;
                s->other = 0;
                break;
            case 1: case 3:
                g_state_0200F390.mode = 1;
                SAVE_STATE(); s->phase.current = 105;
                break;
            case 4:
                s->phase.current = 102;
                SAVE_STATE(); s->phase.current = 124;
                break;
            case 5:
                s->phase.current = 120;
                break;
            case 2:
                g_state_0200F390.mode = 1;
                s->action = 0;
                SAVE_STATE(); s->phase.current = 105;
                break;
            }
        } else if (!s->action) {
            func_08024ABC(&g_state_0200F390.cursor, 1);
            g_callbacks_0836D4B8[0](&data_0200F6A0, sizeof(data_0200F6A0));
            data_0200F6A0.y = data_0200F6A0.x = -1;
            func_08092638(s->actor, CURSOR_TILE->x, CURSOR_TILE->y);
            func_080A9528();
            POP_STATE();
            break;
        }
        break;
    case 105: {
        s32 result;

        if (g_state_0200F390.mode & 0x80) {
            s->action = 1;
            g_state_0200F390.mode = 0;
            if (!(s->flags & 0x400)) {
                func_08025448(1);
                POP_STATE();
                break;
            }
            POP_STATE();
            POP_STATE();
            s->action = 0;
            SAVE_STATE(); s->phase.current = 71;
            break;
        }
        if (g_state_0200F390.mode)
            break;
        result = (s8)func_08025560();
        if (result < 0) {
            s->action = 1;
            g_state_0200F390.mode = 0;
            if (!(s->flags & 0x400)) {
                func_08025448(1);
                POP_STATE();
                break;
            }
            POP_STATE();
            POP_STATE();
            s->action = 0;
            SAVE_STATE(); s->phase.current = 71;
            break;
        }
        if (result == 0)
            s->message_id = 0x162;
        else
            s->message_id = 0x163;
        POP_STATE();
        POP_STATE();
        s->other = s->current;
        FOCUS_ON_UNIT(s->current);
        SAVE_STATE(); s->phase.current = 71;
        SAVE_STATE(); s->phase.current = 69;
        if (func_080C95A8(13)) {
            SAVE_STATE(); s->phase.current = 117;
            func_080C15C0();
            func_080C1AD4(s->message_id);
            func_080C1980(*func_08002830());
            func_080C19BC(1);
            func_080C17B8();
            SAVE_STATE(); s->phase.current = 42;
            func_080C71B4(1);
        }
        SAVE_STATE(); s->phase.current = 21;
        break;
    }
    case 104: {
        void *record;

        record = func_080294FC();
        if (!record)
            break;
        if (!s->other || record != s->other->record) {
            s->other = func_08099560(s->actor, record);
            SAVE_STATE(); s->phase.current = 21;
            break;
        }
        if (g_state_0200F390.mode & 0x80) {
            s->other = func_08099560(s->actor, record);
            FOCUS_ON_UNIT(s->other);
            s->action = 1;
            g_state_0200F390.mode = 0;
            if (!(s->flags & 0x400)) {
                func_08025448(1);
                POP_STATE();
                break;
            }
            POP_STATE();
            POP_STATE();
            s->action = 0;
            SAVE_STATE(); s->phase.current = 71;
            break;
        }
        if (g_state_0200F390.mode)
            break;
        s->other = func_08099560(s->actor, record);
        FOCUS_ON_UNIT(s->other);
        func_080A9528();
        POP_STATE();
        POP_STATE();
        func_08024ABC(&g_state_0200F390.cursor, 1);
        g_callbacks_0836D4B8[0](&data_0200F6A0, sizeof(data_0200F6A0));
        data_0200F6A0.y = data_0200F6A0.x = -1;
        break;
    }
    case 124:
        func_08029544(5);
        s->phase.current = 125;
        break;
    case 125:
        if (!func_08011860())
            break;
        POP_STATE();
        if (!func_08013380()) {
            s->phase.current = 126;
            if (func_080C95A8(13)) {
                SAVE_STATE(); s->phase.current = 52;
                SAVE_STATE(); s->phase.current = 50;
                func_080C15C0();
                func_080C1780();
                func_080C19BC(2);
                func_080C1700(s->current->direction);
                func_080C19BC(2);
                func_080C17B8();
                SAVE_STATE(); s->phase.current = 42;
                func_080C71B4(1);
            }
        } else if (s->flags & 0x400) {
            POP_STATE();
            s->action = 0;
            SAVE_STATE(); s->phase.current = 71;
        }
        func_0802966C();
        break;
    case 126:
        func_08009AFC(0xaa);
        s->flags &= ~0xc0;
        func_08009FD0();
        s->phase.current = 7;
        break;
    case 120:
        s->system_menu = func_080BD328();
        s->phase.current = 121;
        break;
    case 121:
        switch (func_080BD34C(s->system_menu)) {
        case 1:
            if (!(s->flags & 0x400)) {
                func_080BD340(s->system_menu);
                s->phase.current = 102;
                break;
            }
        case 2:
            func_080BD340(s->system_menu);
            func_08024ABC(&g_state_0200F390.cursor, 1);
            g_callbacks_0836D4B8[0](&data_0200F6A0, sizeof(data_0200F6A0));
            data_0200F6A0.y = data_0200F6A0.x = -1;
            func_08092638(s->actor, CURSOR_TILE->x, CURSOR_TILE->y);
            func_080A9528();
            POP_STATE();
            break;
        case 3:
            func_080BD340(s->system_menu);
            func_080230A8();
            s->phase.current = 110;
            break;
        }
        break;
    case 69:
        s->notice = func_080BC914(s->current, s->message_id);
        s->phase.current = 70;
        break;
    case 70:
        if (func_080BC934(s->notice))
            break;
        func_080BC944(s->notice);
        POP_STATE();
        break;
    case 71:
        func_08024ABC(&g_state_0200F390.cursor, 1);
        func_080A9528();
        g_callbacks_0836D4B8[0](&data_0200F6A0, sizeof(data_0200F6A0));
        data_0200F6A0.y = data_0200F6A0.x = -1;
        POP_STATE();
        break;
    case 117:
        func_080C7668(1);
        s->phase.current = 119;
        break;
    case 118:
        func_080C7668(0);
        s->phase.current = 119;
        break;
    case 119:
        if (func_080C76C4())
            break;
        POP_STATE();
        break;
    case 106:
        if (func_080C95A8(13))
            s->flags &= ~0x800;
        switch (func_0809A900(s->actor)) {
        case 1:
            g_state_02000000.flags |= 1;
            s->outcome_menu = func_0809185C(g_state_0200F390.cursor.flags & 0x10 ? 0x80 : 0);
            SAVE_STATE(); s->phase.current = 109;
            break;
        case 2:
            g_state_02000000.flags &= ~1;
            s->outcome_menu = func_0809185C(g_state_0200F390.cursor.flags & 0x10 ? 0x81 : 1);
            SAVE_STATE(); s->phase.current = 109;
            break;
        case 3:
            s->transition = func_08091DC0();
            s->phase.current = 107;
            break;
        }
        break;
    case 107:
        if (!func_08091E48(s->transition) || !func_080922A4(s->transition))
            break;
        func_080922C4(s->transition);
        s->phase.current = 108;
        break;
    case 108:
        if (func_08091E48(s->transition))
            break;
        func_08092288(s->transition);
        func_0809A950(g_state_02000080, 0x18);
        g_state_0200F390.cursor.flags &= 0xfff7;
        s->phase.current = 110;
        break;
    case 109:
        if (func_08091930(s->outcome_menu, first, second))
            break;
        func_080917F8(s->outcome_menu);
        g_state_0200F390.cursor.flags &= 0xfff7;
        s->phase.current = 110;
        break;
    case 87:
        func_08024ABC(&g_state_0200F390.cursor, 3);
        s->phase.current = 88;
        break;
    case 88:
        if (second & 2)
            break;
        MoveCamera(CURSOR_TILE->x * 32 + 16, func_0801CC18(CURSOR_TILE->x, CURSOR_TILE->y) << 4,
                   CURSOR_TILE->y * 32 + 16);
        s->phase.current = 22;
        break;
    case 48:
        if (!func_080A9588())
            break;
        if (s->flags & 4)
            s->ability_argument = func_080C1528();
        if (s->ability == 0x21) {
            s->ability_menu = func_080B7E1C(s->current, s->chain_ability[s->chain_index],
                                s->ability_argument, (s->flags >> 2) & 1, (s->flags >> 1) & 1, 255);
            if (s->chain_index == 0) {
                func_080B7F18(s->ability_menu, 1);
                if (s->flags & 4)
                    func_080B7EFC(s->ability_menu, s->chain_x[0], s->chain_y[0]);
            } else {
                func_080B7F18(s->ability_menu, 0);
                if (s->flags & 4)
                    func_080B7EFC(s->ability_menu, s->chain_x[1], s->chain_y[1]);
            }
        } else {
            s->ability_menu = func_080B7E1C(s->current, s->ability, s->ability_argument,
                                (s->flags >> 2) & 1, (s->flags >> 1) & 1, s->variant);
            func_080B7F18(s->ability_menu, 0);
            if (s->flags & 4)
                func_080B7EFC(s->ability_menu, s->target_x, s->target_y);
        }
        s->phase.current = 49;
        break;
    case 49:
        switch (func_080B7E08(s->ability_menu, first, second)) {
        case 1:
            func_080B7EDC(s->ability_menu, &s->target_x, &s->target_y);
            if (s->ability == 0x21) {
                func_080B7EDC(s->ability_menu, &s->chain_x[s->chain_index], &s->chain_y[s->chain_index]);
                if (!s->chain_index) {
                    s->chain_index++;
                    g_state_0200F390.cursor.flags |= 0x40;
                    func_080B7E7C(s->ability_menu);
                    s->ability_menu = 0;
                    POP_STATE();
                    break;
                }
                s->chain_index++;
                s->target_x = s->chain_x[0];
                s->target_y = s->chain_y[0];
            }
            func_080C9574(3, 1);
            func_080B7E7C(s->ability_menu);
            s->ability_menu = 0;
            s->flags |= 1;
            s->unknown_af = 0;
            s->other = s->current;
            s->phase.current = 19;
            SAVE_STATE(); s->phase.current = 21;
            SAVE_STATE(); s->phase.current = 56;
            if (!(g_state_02000000.unknown_2fc0 & 0x40)) {
                SAVE_STATE(); s->phase.current = 91;
            }
            SAVE_STATE(); s->phase.current = 89;
            s->chain_effects[1] = s->chain_effects[0] = 0;
            s->sound = 4;
            g_state_02000000.unknown_3c9c = s->ability;
            SAVE_STATE(); s->phase.current = 6;
            break;
        case 2:
            if (s->ability == 0x21 || (s->ability && func_080CCD50(s->ability, 0x1b)) || s->ability == 0x109) {
                func_080A9548();
                s->chain_index = 0;
                g_state_0200F390.cursor.flags &= 0xffbf;
            } else {
                func_080A9528();
            }
            func_080B7E7C(s->ability_menu);
            s->ability_menu = 0;
            POP_STATE();
            break;
        }
        break;
    case 46:
        func_080C71B4(7);
        func_08024ABC(&g_state_0200F390.cursor, 0);
        func_080A8288(s->current, -1, -1, -1, s->current->direction);
        s->phase.current = 47;
        break;
    case 47: {
        u8 old_x, old_y;

        switch (func_080A82C0(first, second)) {
        case -1:
            break;
        case -2:
            if (s->flags & 1)
                break;
            s->flags |= 0x10;
            POP_STATE();
            break;
        default:
            old_x = s->current->record->x;
            old_y = s->current->record->y;
            if (!func_080C9540(3)) {
                g_state_02000000.flags &= ~2;
                g_state_02000000.ability = 0xffff;
            }
            FINISH_UNIT(s->current);
            func_080C9574(3, 1);
            func_080C9574(4, 1);
            s->sound = 6;
            s->phase.current = 0;
            SAVE_STATE(); s->phase.current = 6;
            SAVE_STATE(); s->phase.current = 33;
            if (!func_080C95A8(13))
                break;
            func_080C15C0();
            if (s->current->record->x != old_x || s->current->record->y != old_y) {
                func_080C15DC(s->current->record->x, s->current->record->y, 0);
                func_080C19BC(2);
            }
            func_080C1700(s->current->direction);
            func_080C19BC(2);
            func_080C17B8();
            SAVE_STATE();
            s->phase.current = 42;
            func_080C71B4(1);
            break;
        }
        break;
    }
    case 68:
        if (func_080BC900())
            break;
        POP_STATE();
        break;
    case 17:
        s->flags &= ~0xc0;
        func_080BC7D4(s->tracking, s->current, s->effect, s->auxiliary);
        s->phase.current = 18;
        break;
    case 18:
        if (func_080BC7FC())
            break;
        s->flags |= 0x40;
        if (s->auxiliary != 1) {
            s->current = 0;
            ClearStates(&s->phase);
            func_0809A260(s->actor, 1);
            s->phase.current = 0;
            SAVE_STATE(); s->phase.current = 6;
            if (!func_080C95A8(13))
                break;
            SAVE_STATE(); s->phase.current = 52;
            SAVE_STATE(); s->phase.current = 50;
            break;
        }
        s->other = s->current;
        POP_STATE();
        if (!func_080C95A8(13))
            break;
        SAVE_STATE(); s->phase.current = 52;
        SAVE_STATE(); s->phase.current = 50;
        break;
    case 50:
        func_080C71B4(2);
    case 51:
        func_08005028();
        POP_STATE();
        break;
    case 52:
        if (!func_080C75F4())
            break;
        func_080C71B4(0);
        s->frame_delay = 0;
        s->phase.current = 53;
        break;
    case 53:
        if ((data_030028A0.mode & 0xFFFF) != 0x101 || data_030028A0.type != 3)
            break;
        s->frame_delay = 0;
        s->phase.current = 54;
        break;
    case 54:
        if (s->frame_delay <= 15) {
            s->frame_delay++;
            break;
        }
        POP_STATE();
        break;
    case 55: {
        u8 old_x, old_y;
        s32 j;

        old_x = s->current->x >> 5;
        old_y = s->current->y >> 5;
        func_080C15C0();
        func_080C19DC(s->variant);
        if (s->current->record->x != old_x || s->current->record->y != old_y)
            func_080C15DC(old_x, old_y, 0);
        for (j = 0; j < 2; j++)
            func_080C1A04(j, s->chain_ability[j], s->chain_x[j], s->chain_y[j]);
        func_080C1654(s->target_x, s->target_y, s->ability, s->ability_argument, (s->flags >> 1) & 1);
        func_080C1748();
        func_080C1980(*func_08002830());
        s->saved_random = func_080C1994();
        func_080C19BC(2);
        func_080C17B8();
        POP_STATE();
        SAVE_STATE(); s->phase.current = 52;
        SAVE_STATE(); s->phase.current = 50;
        SAVE_STATE();
        s->phase.current = 42;
        func_080C71B4(1);
        break;
    }
    case 56:
        s->phase.current = 57;
        if (func_080C95A8(13)) {
            if (!(s->flags & 4) && func_080C1920(s->current)) {
                SAVE_STATE(); s->phase.current = 55;
                break;
            }
            SAVE_STATE(); s->phase.current = 52;
            SAVE_STATE(); s->phase.current = 51;
            func_080C71B4(2);
            break;
        }
    case 57:
        if (s->flags & 0x80)
            break;
        if (func_080C95A8(13))
            func_080C19BC(1);
        s->flags &= ~0xc0;
        func_0809A260(s->actor, 0);
        func_080A9548();
        if (!func_080A9588() || func_0809A204(s->current->unknown_80))
            break;
        s->saved_x = s->current->record->x;
        s->saved_y = s->current->record->y;
        s->current->record->direction = s->current->direction;
        func_08099E68(s->current, s->current->x >> 5, s->current->y >> 5);
    case 58:
        if (func_080C95A8(13)) {
            *func_08002830() = func_080C1994();
            s->saved_random = *func_08002830();
        }
        func_080CDEA4(s->current->record, 0);
        s->current->appearance &= ~0x20000;
        if (s->ability == 0x21) {
            s->chain_effects[s->unknown_af] = func_080A8194(s->current, s->chain_ability[s->unknown_af],
                                 s->ability_argument, s->chain_x[s->unknown_af],
                                 s->chain_y[s->unknown_af], (s->flags >> 1) & 1, 255);
            if (s->chain_effects[s->unknown_af])
                func_080A8264(s->chain_effects[s->unknown_af]);
        } else {
            s->ability_effect = func_080A8194(s->current, s->ability, s->ability_argument,
                                 s->target_x, s->target_y, (s->flags >> 1) & 1, s->variant);
            if (s->ability_effect)
                func_080A8264(s->ability_effect);
        }
        if (func_080C95A8(13))
            func_080C1980(*func_08002830());
        func_0809993C(s->actor, 1);
        if (s->flags & 0x20)
            s->current->record->unknown_d6 = 0;
        if (s->flags & 2)
            s->current->record->unknown_d6 = 0;
        s->phase.current = 60;
        if (s->ability == 0x21 && s->unknown_af)
            break;
        if (!func_080C95A8(13))
            break;
        s->delay = 8;
        func_080C7378();
        SAVE_STATE(); s->phase.current = 59;
        break;
    case 59:
        if ((data_030028A0.mode & 0xFFFF) != 0x101 || data_030028A0.type != 3)
            break;
        if (s->delay > 0) {
            s->delay--;
            break;
        }
        func_080C738C();
        s->flags |= 0x2000;
        s->flags |= 0x10000;
        POP_STATE();
        break;
    case 60:
        if (s->flags & 0x10000)
            break;
        if (s->ability == 0x21) {
            void *effect = s->chain_effects[s->unknown_af];

            if (effect && func_080A8270(effect))
                break;
            if (++s->unknown_af <= 1 && func_0812E4A8(s->current->record) &&
                !func_080CD95C(s->current->record) && !func_080CDB9C(s->current->record) &&
                !func_080CDBB4(s->current->record)) {
                s->phase.current = 58;
                break;
            }
        } else if (func_080A8270(s->ability_effect)) {
            break;
        }
        s->phase.current = 62;
        if (func_080C95A8(13)) {
            s->flags &= ~0x800;
            s->delay = 2;
            SAVE_STATE(); s->phase.current = 61;
            break;
        }
    case 62: {
        u8 changed, changed_single;

        if (func_080C95A8(13)) {
            if (!func_080C72E4() && !func_080C72F8())
                break;
            s->flags |= 0x800;
            func_080C19BC(1);
            s->flags &= ~0x2000;
        }
        s->flags |= 0x40;
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
            if (!changed)
                s->effect_list = func_080A89D8(s->effect_list, s->chain_effects[1], &changed);
            if (changed) {
                s32 value = func_080C9540(0x42);

                func_080C9574(0x42, value ^ 1);
            }
        } else {
            changed_single = 0;
            s->effect_list = func_080A899C(s->ability_effect);
            s->effect_list = func_080A89D8(s->effect_list, s->ability_effect, &changed_single);
            if (changed_single) {
                s32 value = func_080C9540(0x42);

                func_080C9574(0x42, value ^ 1);
            }
        }
        if (s->effect_list) {
            s->phase.current = 66;
            SAVE_STATE(); s->phase.current = 65;
            break;
        }
    }
    case 66:
        if (s->ability == 0x21)
            s->effect_result = func_080A7138(s->chain_effects[0], s->chain_effects[1]);
        else
            s->effect_result = func_080A8934(s->ability_effect);
        s->phase.current = 64;
        if (s->effect_result) {
            SAVE_STATE(); s->phase.current = 67;
            break;
        }
    case 64: {
        s32 i;  /* the first score and the loop index: both r5 (0x08095F84, 0x08095FEA) */

        s->flags &= ~0x300;
        s->auxiliary = 0;
        if (s->tracking && func_0812E4A8(s->tracking->record)) {
            if (s->ability == 0x21) {
                i = func_08134B88(s->chain_effects[0], 1, 1);
                if (i >= func_08134B88(s->chain_effects[1], 1, 1))
                    s->auxiliary = func_08134B88(s->chain_effects[0], 0, 1);
                else
                    s->auxiliary = func_08134B88(s->chain_effects[1], 0, 1);
                if (s->auxiliary)
                    s->flags |= 0x100;
                func_080BC8C4(s->tracking);
                for (i = 0; i < 2; i++) {
                    if (s->chain_effects[i] && func_080BC810(s->chain_effects[i], s->auxiliary, 1)) {
                        s->flags |= 0x200;
                        func_080BC8E8(s->tracking, s->chain_effects[i], s->auxiliary, 1);
                    }
                }
            } else {
                s->auxiliary = func_08134B88(s->ability_effect, 0, 0);
                if (s->auxiliary)
                    s->flags |= 0x100;
                if (func_080BC810(s->ability_effect, s->auxiliary, 0)) {
                    s->flags |= 0x200;
                    func_080BC878(s->tracking, s->ability_effect, s->auxiliary, 0);
                }
            }
        }
        if (s->ability == 0x21) {
            if (s->chain_effects[1])
                func_080A80C8(s->chain_effects[1]);
            if (s->chain_effects[0])
                func_080A80C8(s->chain_effects[0]);
            s->chain_effects[1] = 0;
            s->chain_effects[0] = 0;
        } else {
            func_080A80C8(s->ability_effect);
            s->ability_effect = 0;
        }
        g_state_02000000.flags &= ~2;
        g_state_02000000.flags |= s->flags & 2;
        g_state_02000000.ability = s->ability;
        s->ability_effect = 0;
        s->flags &= ~0x22;
        s->saved_x = s->current->record->x;
        s->saved_y = s->current->record->y;
        s->sound = 5;
        s->phase.current = 63;
        SAVE_STATE(); s->phase.current = 6;
        if (func_0812E4A8(s->current->record)) {
            SAVE_STATE(); s->phase.current = 2;
        }
        if (func_080C95A8(13)) {
            SAVE_STATE(); s->phase.current = 52;
            SAVE_STATE(); s->phase.current = 50;
        }
        if (s->flags & 0x200) {
            SAVE_STATE(); s->phase.current = 68;
        }
        if (!(s->flags & 0x100))
            break;
        s->other = s->tracking;
        SAVE_STATE(); s->phase.current = 17;
        SAVE_STATE();
        s->phase.current = 77;
        s->saved_height = 255;
        break;
    }
    case 63:
        func_0809A260(s->actor, 1);
        if (!func_0812E4A8(s->current->record)) {
            FINISH_UNIT(s->current);
            func_080C9574(3, 1);
            func_080C9574(4, 1);
            ClearStates(&s->phase);
            s->phase.current = 0;
            break;
        }
        if (s->flags & 4) {
            POP_STATE();
            break;
        }
        if (!func_080CD944(s->current->record) && !func_080CDB54(s->current->record) &&
            !func_080CDB6C(s->current->record)) {
            POP_STATE();
            break;
        }
        FINISH_UNIT(s->current);
        func_080C9574(3, 1);
        func_080C9574(4, 1);
        ClearStates(&s->phase);
        s->phase.current = 0;
        break;
    case 61:
        if (s->delay > 0) {
            s->delay--;
            break;
        }
        func_080C7240();
        func_080C7284();
        POP_STATE();
        break;
    case 65:
        if (func_080A8A68(s->effect_list, first, second))
            break;
        func_080A8A64(s->effect_list);
        POP_STATE();
        break;
    case 67:
        if (func_080A8958(s->effect_result))
            break;
        func_080A8940(s->effect_result);
        s->effect_result = 0;
        POP_STATE();
        break;
    case 115:
        s->special_menu = func_080BCA24(s->actor);
        s->phase.current = 116;
        break;
    case 116:
        if (func_080BCA40(s->special_menu, first))
            break;
        func_080BCA54(s->special_menu);
        s->special_menu = 0;
        POP_STATE();
        break;
    case 38:
        func_080C9574(4, 0);
        FOCUS_ON_UNIT(s->current);
        func_08024ABC(&g_state_0200F390.cursor, 1);
        func_080B7F4C();
        s->phase.current = 39;
        break;
    case 39:
        if (first & 2) {
            func_0802D704(func_0802D72C(1));
            func_0802D704(func_0802D72C(0));
            s->other = s->current;
            func_08141540(104);
            if (CURSOR_TILE->x == s->current->record->x &&
                CURSOR_TILE->y == s->current->record->y) {
                func_08024ABC(&g_state_0200F390.cursor, 4);
                POP_STATE();
                SAVE_STATE(); s->phase.current = 21;
                SAVE_STATE(); s->phase.current = 79;
            } else {
                s->phase.current = 38;
                func_08024ABC(&g_state_0200F390.cursor, 0);
                SAVE_STATE(); s->phase.current = 21;
            }
            break;
        }
        if (first & 1) {
            if (!func_08099FB0(s->current, (s8)CURSOR_TILE->x,
                                         (s8)CURSOR_TILE->y)) {
                func_08141540(106);
                break;
            }
            s->target_x = CURSOR_TILE->x;
            s->target_y = CURSOR_TILE->y;
            func_0802D704(func_0802D72C(1));
            func_0802D704(func_0802D72C(0));
            if (CURSOR_TILE->x == s->current->record->x &&
                CURSOR_TILE->y == s->current->record->y) {
                func_08141540(100);
                func_0802D704(func_0802D72C(1));
                func_0802D704(func_0802D72C(0));
                func_08024ABC(&g_state_0200F390.cursor, 4);
                s->other = s->current;
                if (CURSOR_TILE->x == s->current->record->x &&
                    CURSOR_TILE->y == s->current->record->y) {
                    s->phase.current = 21;
                    SAVE_STATE(); s->phase.current = 79;
                } else {
                    s->phase.current = 38;
                    SAVE_STATE(); s->phase.current = 21;
                }
                break;
            }
            s->path_count = func_0809A604(s->current, CURSOR_TILE->x, CURSOR_TILE->y,
                              (u32)func_080CA3EC(s->current->record) / 10, s->path);
            func_08024ABC(&g_state_0200F390.cursor, 0);
            s->other = s->current;
            s->phase.current = 38;
            SAVE_STATE(); s->phase.current = 21;
            SAVE_STATE(); s->phase.current = 29;
            SAVE_STATE(); s->phase.current = 76;
            SAVE_STATE(); s->phase.current = 19;
            SAVE_STATE(); s->phase.current = 45;
            SAVE_STATE(); s->phase.current = 21;
            if (func_0809D8F0(s->current)) {
                SAVE_STATE(); s->phase.current = 40;
                SAVE_STATE(); s->phase.current = 79;
                SAVE_STATE(); s->phase.current = 96;
            } else {
                SAVE_STATE(); s->phase.current = 79;
                SAVE_STATE(); s->phase.current = 40;
            }
            SAVE_STATE(); s->phase.current = 44;
            SAVE_STATE(); s->phase.current = 21;
            SAVE_STATE(); s->phase.current = 99;
            func_08141540(100);
            break;
        }
        func_080B5880(s->actor, CURSOR_TILE->x, CURSOR_TILE->y);
        break;
    case 42:
        if (func_080C7650())
            break;
        func_080C71B4(0);
        POP_STATE();
        break;
    case 44:
        if (func_080C95A8(13))
            s->flags |= 0x2000;
        POP_STATE();
        break;
    case 45:
        if (func_080C95A8(13))
            s->flags &= ~0x2000;
        POP_STATE();
        break;
    case 40:
        s->phase.current = 41;
    case 41: {
        u8 *attribute;

        func_0809A664(s->current->unknown_80, 0);
        func_0809A63C(s->current, 1);
        if (s->path_count <= 1) {
            func_080C9574(4, 1);
            func_0809A664(s->current->unknown_80, 1);
            POP_STATE();
            break;
        }
        if (func_080C95A8(13))
            s->flags |= 0x2000;
        attribute = (u8 *)func_080C7EA4(s->current->record, 0x44);
        func_0809D464(s->effect, s->current, s->path, s->path_count);
        func_0809B818(s->effect);
        if (!func_0809D8F0(s->current))
            func_0809D7E4(s->current, 16, -120, -86);
        if (attribute[1] == 4) {
            func_0809D638(s->effect, 3);
            func_0809D620(s->effect, 2, 2, 2, 2);
        }
        s->phase.current = 43;
        data_08394054(s->current->animation, 1);
        data_08394054(s->current->secondary_animation, 1);
        func_0809993C(s->actor, 1);
        func_080A9548();
        break;
    }
    case 43: {
        s32 count, value, result, moving, i;

        if (!func_080A9588())
            break;
        count = 1;
        value = 0;
        result = 0;
        moving = 0;
        if (!func_0809D8F0(s->current)) {
            if (func_080C95A8(13))
                count = func_080C19A8();
            if (func_080C8298(s->current->record))
                count = 2;
        }
        for (i = 0; i < count; i++) {
            result = func_0809B88C(s->effect);
            moving = 0;
            if (!func_0809D614(s->effect))
                moving = func_0809D640(s->actor, s->current);
        }
        if (!func_0809D8F0(s->current))
            value = func_0809CAF4();
        if (result || value || moving)
            break;
        if (func_080C95A8(13))
            s->flags &= ~0x2000;
        func_0809993C(s->actor, 0);
        func_080C9574(4, 1);
        func_0809A664(s->current->unknown_80, 1);
        func_0809A710(s->current);
        data_08394054(s->current->animation, 0);
        data_08394054(s->current->secondary_animation, 0);
        POP_STATE();
        break;
    }
    case 21:
        MoveCamera(s->other->x, s->other->z, s->other->y);
        s->phase.current = 22;
        break;
    case 22:
        if (func_08092390(data_0200F4C0))
            break;
        POP_STATE();
        break;
    case 29:
        func_08099E68(s->other, s->other->record->x, s->other->record->y);
        if (s->other->direction != s->other->record->direction)
            func_0809836C(s->other, 0, s->other->record->direction, 0);
        func_0809A624(s->other);
        s->phase.current = 30;
        break;
    case 30:
        if (!func_08098A88(s->other))
            break;
        POP_STATE();
        break;
    case 79:
        func_0801D938();
        s->phase.current = 80;
        break;
    case 80:
        func_080231AC();
        s->wait = 2;
        s->phase.current = 81;
        break;
    case 81:
        if (--s->wait > 0)
            break;
        POP_STATE();
        break;
    case 89:
        if (s->target_x == s->current->x >> 5 && s->target_y == s->current->y >> 5) {
            POP_STATE();
            break;
        }
        s->turn.unit = s->current;
        s->turn.delay = 8;
        s->turn.target = func_0809D6BC(s->target_x - (s->current->x >> 5),
                                     s->target_y - (s->current->y >> 5));
        s->turn.ticks = 0;
        s->phase.current = 90;
        break;
    case 90: {
        s32 old_direction, moving;

        old_direction = s->current->direction;
        moving = func_0809D3A8(&s->turn);
        if (old_direction != s->current->direction && moving == 1)
            func_0809836C(s->current, 9, s->current->direction, 0);
        if (moving)
            break;
        func_0809836C(s->current, 0, s->current->direction, 0);
        POP_STATE();
        break;
    }
    case 91:
        if (!s->ability) {
            POP_STATE();
            break;
        }
        func_08025688(0, s->ability, 0);
        s->timer = 0;
        s->phase.current = 92;
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
        POP_STATE();
        break;
    }
    return 1;
}
