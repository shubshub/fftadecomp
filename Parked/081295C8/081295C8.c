#include "control_flags.h"

typedef struct {
    u8 unknown_00[6];
    u8 complete;
} PanelContext;

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u32 unknown_08[5];
} TaskRequest;

typedef struct {
    u16 value;
    u8 unknown_02[22];
} Ramp;

typedef struct {
    u16 identifier : 4;
    u16 job : 7;
    u16 alternate : 1;
    u16 unknown_0C : 4;
} __attribute__((packed)) Key;

typedef struct {
    u8 unknown_00[0x1C];
} Transfer;

typedef struct {
    PanelContext *context;
    void *task;
    void *unit;
    Key *key;
    Ramp rows;
    u8 text[0x290];
    u16 *tilemap;
    u16 *blank;
    const u8 *script;
    Transfer transfers[4];
    u8 unknown_334[0x70];
    u8 next_transfer;
    u8 mode;
    u8 delay;
    u8 unknown_3A7;
    u8 line[0x2C];
    u8 index;
    u8 count;
    u16 sound;
} PanelState;

typedef struct {
    u8 unknown_00[0x0C];
    u16 value;
    u16 pose;
    u8 unknown_10[0x7C];
    void *instance;
    void *resource;
} PortraitTask;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
    u16 *tilemap;
} Background;

typedef struct {
    u16 unknown_00;
    u16 pressed;
} InputState;

typedef void (*ClearFunction)(void *destination, u32 size);
typedef void (*CopyFunction)(void *destination, const void *source, u32 size);
typedef u32 (*TaskCallback)(void *task, void *request, void *payload);

extern Background data_030008B0;
extern Background data_03000990;
extern InputState data_03000000;
extern u16 data_03003960[];
extern u8 data_06005000[];
extern u8 data_06005800[];
extern u8 data_06008000[];
extern const u16 data_083C4510[];
extern const u16 data_083C4770[];
extern const u16 data_083C47FC[];
extern ClearFunction g_callbacks_0836D4B8[];
extern CopyFunction data_0836D4BC[];
extern const u8 *const g_table_085567F0[];

extern u32 func_08129D90(void *task, void *request, void *payload);
extern void *func_08121B64(u32 size);
extern void func_08121B78(void *allocation);
extern void *func_08121B8C(TaskCallback callback, u16 payload_size,
                          void *request, void *parent);
extern void func_0801E458(u8 layer, u8 format, u8 mode, s16 x, s16 y,
                          void *source, void *destination);
extern const void *func_080CBABC(u32 index);
extern const void *func_080CBA84(u32 index);
extern void func_081288C8(PanelState *state);
extern void func_08128968(PanelState *state);
extern u8 func_08128B4C(PanelState *state);
extern u8 func_0812949C(PanelState *state);
extern u8 func_0802DD58(void);
extern Key *func_0802FF84(u8 index);
extern void *func_0802DE10(Key *key);
extern void func_08007620(Ramp *ramp, u16 first, u16 second, u16 target,
                          s16 duration);
extern void func_080076F4(Ramp *ramp);
extern u32 func_08007894(const void *ramp);
extern void func_08000B68(Transfer *request, u32 fill,
                         void *destination, u32 count);
extern void func_08000BAC(Transfer *request, const void *source,
                         void *destination, u16 width, u16 height,
                         u16 source_stride, u16 destination_stride);
extern void func_08013528(void *renderer, const void *source);
extern u16 func_08018C24(u8 *destination, const u8 *source);
extern void *func_08005BFC(void *task);
extern u8 func_08021C5C(void *instance);
extern void *func_08021618(void *resource, void *instance, u32 x, u32 y,
                          u32 value, u32 first, u32 second);
extern void func_08021DF8(void *resource, u16 clear, u16 set);
extern void func_08141570(s32 player_id, u16 song_id);

/* The same text as next_transfer in src/081288C8.c.  The ROM repeats its
 * instruction group eleven times here, first at 0x08129848. */
static inline Transfer *next_transfer(PanelState *state)
{
    Transfer *transfer = &state->transfers[state->next_transfer++];

    state->next_transfer &= 3;
    return transfer;
}

/* The ROM has this block twice, at 0x08129C28 with pose 8 and at 0x08129C96
 * with pose 12.  At the second site the pose constant is loaded at
 * 0x08129C94, ahead of the state->task load and the func_08005BFC call that
 * open the block: the argument is evaluated before the body starts. */
static inline void set_pose(PanelState *state, u16 pose)
{
    PortraitTask *portrait = func_08005BFC(state->task);

    portrait->pose = pose;
    func_08021618(portrait->resource, portrait->instance, 0, 20,
                 portrait->value, portrait->pose + 3, 0);
    func_08021DF8(portrait->resource, 2, 1);
}

/* Target [0x081295C8, 0x08129D90): 1992 bytes, 823 instructions. */
u32 func_081295C8(void *task, TaskRequest *request, PanelState *state)
{
    switch (request->phase)
    {
    case 1:
        if (state->blank)
        {
            func_08121B78(state->blank);
            state->blank = 0;
        }
        if (state->tilemap)
        {
            func_08121B78(state->tilemap);
            state->tilemap = 0;
        }
        break;

    case 0:
        g_control_flags_03000940.display |= 0xC00;
        g_control_flags_03000940.bldcnt_lo =
            g_control_flags_03000940.bldcnt_hi = 0;
        g_control_flags_03000940.bldalpha_lo =
            g_control_flags_03000940.bldalpha_hi = 0;
        func_0801E458(2, 0, 0, 0, 0, data_06008000, data_06005800);
        func_0801E458(3, 0, 1, 0, 0, data_06008000, data_06005000);
        state->context = request->object;
        state->next_transfer = 0;
        state->delay = 0;
        state->index = 0;
        state->blank = func_08121B64(0x260);
        state->tilemap = func_08121B64(0x260);
        g_callbacks_0836D4B8[0](state->blank, 0x260);
        data_0836D4BC[0](data_03003960, func_080CBABC(18), 0x40);
        data_0836D4BC[0](&data_03003960[0x20], func_080CBA84(10), 0x20);
        data_03003960[0x23] = 0x41DF;
        break;

    case 0x100:
    {
        TaskRequest child;

        func_081288C8(state);
        child.object = state;
        state->task = func_08121B8C(func_08129D90, 0x98, &child, task);
        state->mode = 1;
        state->count = func_0802DD58();
        request->phase = 0x10D;
        break;
    }

    case 0x101:
        func_08000B68(next_transfer(state), 0,
                     data_030008B0.tiles + 0x3000, 0x3E0);
        g_callbacks_0836D4B8[0](state->tilemap, 0x260);
        request->phase = 0x105;
        break;

    case 0x105:
        state->key = func_0802FF84(state->index);
        state->unit = func_0802DE10(state->key);
        state->mode = 2;
        request->phase = 0x106;
        break;

    case 0x106:
        func_08128968(state);
        request->phase = 0x103;
        break;

    case 0x103:
        if (func_08007894(&state->rows))
        {
            state->mode = 3;
            request->phase = 0x107;
        }
        else
        {
            func_080076F4(&state->rows);
            func_08000BAC(next_transfer(state), state->blank,
                         data_030008B0.tilemap + 0x46, 19, 16, 38, 64);
            func_08000BAC(next_transfer(state), state->tilemap,
                         data_030008B0.tilemap + 0x46, 19,
                         state->rows.value, 38, 64);
            func_08000BAC(next_transfer(state), data_083C4510,
                         data_03000990.tilemap + 0x46, 19,
                         state->rows.value, 38, 64);
        }
        break;

    case 0x104:
        if (func_08007894(&state->rows))
        {
            func_08000BAC(next_transfer(state), state->blank,
                         data_030008B0.tilemap + 0x46, 19, 2, 38, 64);
            func_08000BAC(next_transfer(state), state->blank,
                         data_03000990.tilemap + 0x46, 19, 2, 38, 64);
            state->delay = 16;
            request->phase = 0x10D;
        }
        else
        {
            func_080076F4(&state->rows);
            func_08000BAC(next_transfer(state), state->blank,
                         data_030008B0.tilemap + 0x46, 19, 16, 38, 64);
            func_08000BAC(next_transfer(state), state->blank,
                         data_03000990.tilemap + 0x46, 19, 16, 38, 64);
            func_08000BAC(next_transfer(state), state->tilemap,
                         data_030008B0.tilemap + 0x46, 19,
                         state->rows.value, 38, 64);
            func_08000BAC(next_transfer(state), data_083C4510,
                         data_03000990.tilemap + 0x46, 19,
                         state->rows.value, 38, 64);
        }
        break;

    case 0x107:
        func_08013528(state->text, data_030008B0.tiles + 0x3300);
        state->line[0] = 0x8C;
        state->line[1] = 0x65;
        func_08018C24(&state->line[2],
                     g_table_085567F0[state->key->unknown_0C + 0x2CC]);
        state->script = state->line;
        state->sound = 0;
        state->delay = 32;
        request->phase = 0x108;
        break;

    case 0x108:
        if (func_08128B4C(state))
        {
            state->delay = 32;
            request->phase = 0x109;
        }
        break;

    case 0x109:
        if (func_0812949C(state))
        {
            state->delay = 48;
            request->phase = 0x10A;
        }
        break;

    case 0x10A:
        if (state->delay)
            state->delay--;
        else
        {
            const u16 *source;

            source = state->key->alternate ? data_083C4770 : data_083C47FC;
            func_08000BAC(next_transfer(state), source,
                         data_03000990.tilemap + 0x166, 10, 7, 20, 64);
            set_pose(state, 8);
            func_08141570(1, 0x127);
            request->phase = 0x10B;
        }
        break;

    case 0x10B:
        if (func_08021C5C(((PortraitTask *)func_08005BFC(state->task))->instance))
        {
            set_pose(state, 12);
            state->delay = 16;
            request->phase = 0x10C;
        }
        break;

    case 0x10C:
        if (state->delay)
            state->delay--;
        else if (data_03000000.pressed & 1)
        {
            state->mode = 1;
            state->index++;
            func_08007620(&state->rows, 16, 0, 1, 6);
            request->phase = 0x104;
        }
        break;

    case 0x10D:
        if (state->delay)
            state->delay--;
        else if (state->index >= state->count)
            request->phase = 0x102;
        else
        {
            func_08007620(&state->rows, 1, 0, 16, 6);
            request->phase = 0x101;
        }
        break;

    case 0x102:
        func_0801E458(2, 0, 0, 0, 0, data_06008000, data_06005800);
        func_0801E458(3, 0, 0, 0, 0, data_06008000, data_06005000);
        func_08121B78(state->blank);
        state->blank = 0;
        func_08121B78(state->tilemap);
        state->tilemap = 0;
        state->context->complete = 1;
        request->phase = 3;
        break;
    }
    return 0;
}
