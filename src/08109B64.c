#include "ffta.h"
#include "control_flags.h"

// Target 0x08109B64..0x08109EC0 (860 bytes, complete span including literal pool):
// f0b54f464646c0b48ab081468846171c0b88064883426fd083420edc012b3dd0012b05dc002b1bd08be1 ...
// (see the disassembly for the full byte string)
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u32 unknown_08;
    u32 flags;
    u8 unknown_10[6];
    u16 flag;
} Descriptor08109B64;

typedef struct {
    u16 countdown;
    u8 mode;
    u8 ready;
    u8 unknown_04;
    u8 flag;
    s16 x;
    s16 y;
    u8 unknown_0A[2];
    void *output;
    void *coordinate_result;
    void *actor_object;
    void *outputs[2];
    void *animation;
    void *resource_task;
    void *timeline;
    void *initial_task;
    void *actor;
    void *output_task;
    void *object_task;
    void *record_task;
} Payload08109B64;

typedef struct {
    s16 x;
    s16 y;
} Offset08109B64;


extern const u8 data_083A1920[];
extern const u8 data_083A19AC[];
extern const u8 data_083A1950[];
extern const u8 data_083A19B0[];
extern const u8 data_083A1980[];
extern const u8 data_083A19B8[];
extern const u8 data_083A1998[];
extern const u8 data_083A19C0[];
extern const u8 data_083A19C8[];
extern const u8 data_088ED3F0[];
extern const u8 data_0894D6B4[];

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *,
                         u16, u16, void *);
extern u8 func_080D8858(void *, u16);
extern s8 func_080DBC88(void *);
extern void func_080DBDC8(void *, s16 *, s16 *);
extern void *func_080D6098(s16, s16, s16, u8, u16, void *, const void *, void *);
extern void *func_080D6134(void *);
extern void func_080D8CD4(void *);
extern u8 func_080D8B4C(void);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern u16 func_080035A8(u8);
extern void *func_080D3E9C(const void *, void *);
extern u8 func_080DD580(void *);
extern u8 func_080DD670(void *, u8);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void func_080DF860(void *);
extern void *func_080D3F08(void *);
extern void *func_080D4D2C(void *, u8);
extern void *func_080DBA5C(void *);

u32 func_08109B64(void *task, Descriptor08109B64 *descriptor,
                  Payload08109B64 *payload)
{
    s16 x;
    s16 y;
    u8 blocked;
    u8 selector;
    u8 animation;
    u16 output_mode;

    switch (descriptor->phase) {
    case 0:
        payload->flag = descriptor->flag;
        payload->actor = descriptor->actor;
        animation = 4;
        if (payload->flag != 0)
            animation = 0;
        if (descriptor->flags & 2)
            payload->mode = 1;
        payload->initial_task = func_080E03F8(payload->actor, data_083A1920,
            animation, 0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_task = func_080E05DC(payload->initial_task);
        if (payload->initial_task != 0)
            break;
        blocked = func_080D3B54(payload->actor);
        if (blocked != 0) {
            descriptor->phase = 2;
            break;
        }
        output_mode = 0x58;
        if (payload->mode != 0)
            output_mode = 0x34;
        payload->output_task = func_080DDF68(payload->actor, &payload->output,
            output_mode, 1, &payload->ready, data_083A19AC, 0, 0,
            task);
        descriptor->phase++;
        break;
    case 0x101: {
        Offset08109B64 table[4] = {
            {-20, -12}, {-16, -24}, {16, -24}, {20, -12}
        };

        if (payload->ready == 0)
            break;
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        selector = func_080DBC88(payload->output);
        func_080DBDC8(payload->output, &x, &y);
        payload->animation = func_080D6098(
            x + table[selector].x,
            y + table[selector].y, 0, 1, 2,
            payload->outputs, data_083A1950, task);
        payload->record_task = func_080DFD8C(data_083A19B0, 1, 4, 0, task);
        descriptor->phase++;
        break;
    }
    case 0x102:
        payload->animation = func_080D6134(payload->animation);
        if (payload->animation != 0)
            break;
        func_080D8CD4(payload->actor);
        payload->countdown = 20;
        descriptor->phase++;
        break;
    case 0x103:
        if (func_080D8B4C() != 0)
            break;
        if (payload->countdown != 0 && --payload->countdown != 0)
            break;
        payload->actor_object = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(payload->actor_object,
            &payload->x, &payload->y, 0);
        payload->animation = func_080D6098(payload->x, payload->y, 0, 1, 1,
            payload->outputs, data_083A1980, task);
        payload->record_task = func_080DFD8C(data_083A19B8, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x104:
        payload->animation = func_080D6134(payload->animation);
        if (payload->animation != 0)
            break;
        func_080D49FC(0, 2, 0, payload->x, payload->y);
        payload->resource_task = func_080D4B64(0, data_088ED3F0, 943, 6);
        g_control_flags_03000940.display |= func_080035A8(2);
        payload->timeline = func_080D3E9C(data_0894D6B4, task);
        payload->countdown = 0;
        if (func_080DD580(payload->actor_object) != 0
            && func_080DD670(payload->actor_object, 8) != 0)
            payload->countdown = 16;
        if (payload->countdown == 0)
            payload->object_task = func_080DCFE4(payload->actor_object,
                data_083A1998, 12, 46, 4, task, 46);
        payload->record_task = func_080DFD8C(data_083A19C0, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x105:
        if (payload->countdown != 0) {
            if (--payload->countdown != 0)
                break;
            func_080DF860(payload->coordinate_result);
            payload->record_task = func_080DFD8C(data_083A19C8, 1, 4, 0, task);
        }
        payload->timeline = func_080D3F08(payload->timeline);
        if (payload->timeline != 0)
            break;
        payload->resource_task = func_080D4D2C(payload->resource_task, 0);
        if (payload->resource_task != 0)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        payload->object_task = func_080DBA5C(payload->object_task);
        if (payload->object_task == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
