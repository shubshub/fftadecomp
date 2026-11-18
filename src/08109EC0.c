#include "ffta.h"
#include "effect_task.h"

/* Complete target: [0x08109EC0, 0x0810A134), 628 bytes.
 * Local offset views describe the observed accesses, not original types. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u32 unknown_08;
    u32 flags;
    u8 unknown_10[6];
    u16 mode;
} Descriptor08109EC0;

typedef struct {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} InterpolationState;

typedef struct {
    s16 x;
    s16 y;
    u8 unknown_04[2];
    u8 alternate;
    u8 kind;
    u8 ready;
    u8 unknown_09[3];
    void *watch;
    void *position_source;
    void *actor_object;
    void *actor;
    void *initial_task;
    void *graphic_task;
    void *fade_task;
    void *object_task;
    void *output_task;
    InterpolationState tween;
    void *label_task;
} Payload08109EC0;

extern u8 data_0600FFC0[];
extern const u8 data_083A1A00[];
extern const u8 data_083A1A44[];
extern const u8 data_08507134[];
extern const u8 data_083A1A48[];
extern const u8 data_088F5AFC[];
extern const u8 data_0894DC90[];
extern const u8 data_083A1A30[];
extern const u8 data_083A1A50[];
extern u16 g_control_flags_03000940;

extern void func_0814186C(const void *, void *, u32);
extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *,
                          u16, u16, void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
/* Coordinate views use the low halfwords consumed and signed-interpreted
 * by the saved entries; they do not assert historical nominal declarations. */
extern void *func_080D5CC0(const void *, u16, s16, s16, s16, u8, u8, u8);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_08011484(void *);
extern void func_080D73AC(const void *, u8, u8, s16, s16, u8);
extern u32 func_080035A8(u8);
extern void func_08003620(u8);
extern void *func_080D3E9C(const void *, void *);

extern void func_080E0608(InterpolationState *, s16, s16, s16);
extern void func_080E064C(InterpolationState *);
extern void func_080D74A4(const void *, u8, s16, s16);
extern u8 func_080E0690(InterpolationState *);
extern void *func_080D3F08(void *);
/* The complete DE1F0 entry ignores its incoming R0 word. */
extern u8 func_080DE1F0(void *);
extern void *func_080DBA5C(void *);

u32 func_08109EC0(void *task, Descriptor08109EC0 *descriptor,
                  Payload08109EC0 *payload)
{
    u8 mode;
    u16 animation;
    u16 zero;

    switch (descriptor->phase) {
    case 0:
        payload->kind = descriptor->mode;
        payload->actor = descriptor->actor;
        mode = 4;
        if (payload->kind != 0)
            mode = 0;
        if (descriptor->flags & 2)
            payload->alternate = 1;
        zero = 0;
        func_0814186C(&zero, data_0600FFC0, 0x01000020);
        payload->initial_task = func_080E03F8(payload->actor,
            data_083A1A00, mode, 0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_task = func_080E05DC(payload->initial_task);
        if (payload->initial_task != 0)
            break;
        if (func_080D3B54(payload->actor)) {
            descriptor->phase = 2;
            break;
        }
        animation = 88;
        if (payload->alternate != 0)
            animation = 52;
        payload->output_task = func_080DDF68(payload->actor,
            &payload->watch, animation, 1, &payload->ready,
            data_083A1A44, 0, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->ready == 0)
            break;
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        payload->actor_object = func_080DD4A4(payload->actor, 0);
        payload->position_source = func_080DD748(payload->actor_object,
            &payload->x, &payload->y, 0);
        payload->graphic_task = func_080D5CC0(data_08507134, 3,
            payload->x, (s16)(payload->y - 32), 1000, 6, 0, 0);
        payload->label_task = func_080DFD8C(data_083A1A48,
            1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x102:
        payload->graphic_task = func_08011484(payload->graphic_task);
        if (payload->graphic_task != 0)
            break;
        func_080D73AC(data_088F5AFC, 0, 2, payload->x,
            (s16)(payload->y - 24), 0);
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940;
            flags |= mask;
            g_control_flags_03000940 = flags;
        }
        func_08003620(1);
        payload->fade_task = func_080D3E9C(data_0894DC90, task);
        payload->object_task = func_080DCFE4(payload->actor_object,
            data_083A1A30, 12, 50, 12, task, 50);
        payload->label_task = func_080DFD8C(data_083A1A50,
            1, 4, 0, task);
        func_080E0608(&payload->tween, 24, 34, 50);
        descriptor->phase++;
        break;
    case 0x103:
        func_080E064C(&payload->tween);
        func_080D74A4(data_088F5AFC, 2, payload->x,
            (s16)(payload->y - payload->tween.current));
        if (func_080E0690(&payload->tween) == 0)
            break;
        payload->fade_task = func_080D3F08(payload->fade_task);
        if (payload->fade_task != 0)
            break;
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940;
            flags &= ~mask;
            g_control_flags_03000940 = flags;
        }
        func_08003620(0);
        if (func_080DE1F0(payload->watch) == 0)
            break;
        payload->object_task = func_080DBA5C(payload->object_task);
        if (payload->object_task == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
