#include "ffta.h"

/* Target 0x080FC800..0x080FCB8E, 910 bytes including literal pools.  Task
 * callback; its table entry at 0x08394C50 gives the 0x58-byte payload.  The
 * 3-byte initialiser of the phase 0x103 thresholds is the ROM bytes at
 * 0x08149D88.
 */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[14];
    u16 flag;
} Descriptor;

typedef struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} InterpolationState;

typedef struct {
    s16 x, y;
    u16 countdown;
    u8 flag;
    u8 ready;
    u8 property;
    u8 unknown_09[3];
    void *output;
    void *coordinate_result;
    void *actor;
    void *initial_child;
    void *sprite;
    void *objects[3];
    void *final_object;
    void *resource_child;
    void *effect_child;
    void *preparation;
    void *record_child;
    InterpolationState x_motion;
    InterpolationState y_motion;
} Payload;

extern const u8 data_0839D420[];
extern const u8 data_0839D464[];
extern const u8 data_0839D450[];
extern const u8 data_0839D468[];
extern const u8 data_08502DA4[];
extern const u8 data_084F6BC8[];
extern const u8 data_085000D8[];
extern const u8 data_089492DC[];

extern void *func_080E03F8(void *, const void *, u8, u8, const s16 *, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *,
                           u16, u16, void *);
extern u8 func_080DC058(void *, u8);
extern u8 func_080D8B4C(void);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern u8 func_080DD73C(void *);
extern s8 func_080DBC88(void *);
extern void *func_080D5CC0(const void *, u16, s16, s16, u16, u8, u8, u8);
extern void func_08011058(void *, s16);
extern void func_08011118(void *, u8);
extern void func_080E0608(InterpolationState *, s16, s16, s16);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void func_080E064C(InterpolationState *);
extern void func_080107D4(void *, s16, s16, u16);
extern void func_08011198(void *);
extern u8 func_080E0690(InterpolationState *);
extern void func_08011428(void *);
extern void *func_080D4704(const void *, void *);
extern u8 func_080DE1F0(void *);
extern u8 func_080D5F24(void **, u16);
extern void *func_08011484(void *);
extern void *func_080D4774(void *);
extern void *func_080DBA5C(void *);

u32 func_080FC800(void *task, Descriptor *descriptor, Payload *payload)
{
    u8 mode;
    u8 i;

    switch (descriptor->phase) {
    case 0:
        payload->flag = descriptor->flag;
        payload->actor = descriptor->actor;
        mode = 4;
        if (payload->flag != 0)
            mode = 0;
        payload->initial_child = func_080E03F8(payload->actor, data_0839D420,
            mode, 0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_child = func_080E05DC(payload->initial_child);
        if (payload->initial_child != 0)
            break;
        if (func_080D3B54(payload->actor)) {
            descriptor->phase = 2;
            break;
        }
        payload->preparation = func_080DDF68(payload->actor,
            &payload->output, 0x8007, 1, &payload->ready, data_0839D464,
            5, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->ready == 0)
            break;
        func_080DC058(payload->actor, 0);
        payload->countdown = 30;
        descriptor->phase++;
        /* fall through */
    case 0x102: {
        void *object;
        s16 x, y;

        if (payload->countdown != 0) {
            payload->countdown--;
            if (payload->countdown != 0)
                break;
        }
        if (func_080D8B4C())
            break;
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        object = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(object, &payload->x,
            &payload->y, 0);
        if (func_080DD73C(payload->output))
            payload->y -= 8;
        payload->property = func_080DBC88(payload->output);
        x = payload->x + 96;
        y = payload->y - 96;
        if (payload->property > 1)
            x = payload->x - 96;
        payload->sprite = func_080D5CC0(data_08502DA4, 0, x, y, 0x3F6, 6,
            0, 0);
        func_08011058(payload->sprite, 1);
        if (payload->property > 1)
            func_08011118(payload->sprite, 1);
        func_080E0608(&payload->x_motion, x, payload->x, 25);
        func_080E0608(&payload->y_motion, y, payload->y, 25);
        payload->effect_child = func_080DCFE4(object, data_0839D450, 12,
            25, 20, task, 25);
        payload->record_child = func_080DFD8C(data_0839D468, 1, 4, 0, task);
        descriptor->phase++;
        break;
    }
    case 0x103: {
        u8 thresholds[3] = {15, 30, 45};
        s16 x, y;

        func_080E064C(&payload->x_motion);
        func_080E064C(&payload->y_motion);
        func_080107D4(payload->sprite, payload->x_motion.current,
            payload->y_motion.current, 0);
        for (i = 0; i < 3; i++) {
            if (payload->objects[i] == 0
                && payload->y_motion.current >= thresholds[i]) {
                x = payload->x_motion.current + 3;
                y = payload->y_motion.current + 6;
                if (payload->property > 1)
                    x = payload->x_motion.current - 3;
                payload->objects[i] = func_080D5CC0(data_084F6BC8, 1,
                    x, y, 0x3D5, 7, 0, 0);
                if (payload->property > 1)
                    func_08011118(payload->objects[i], 1);
                func_08011198(payload->objects[i]);
            }
        }
        if (func_080E0690(&payload->x_motion)) {
            func_08011428(payload->sprite);
            payload->sprite = 0;
            payload->final_object = func_080D5CC0(data_085000D8, 0,
                payload->x, payload->y, 0x368, 7, 0, 0);
            if (payload->property > 1)
                func_08011118(payload->final_object, 1);
            func_08011198(payload->final_object);
            payload->resource_child = func_080D4704(data_089492DC, task);
            descriptor->phase++;
        }
        break;
    }
    case 0x104:
        if (func_080DE1F0(payload->output) == 0)
            break;
        func_080D5F24(payload->objects, 3);
        payload->final_object = func_08011484(payload->final_object);
        payload->resource_child = func_080D4774(payload->resource_child);
        if (payload->resource_child != 0)
            break;
        payload->effect_child = func_080DBA5C(payload->effect_child);
        if (payload->effect_child != 0)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
