#include "control_flags.h"

/* Effect IDs 0x92..0x96 share this 0x44-byte task payload.
 * Complete Thumb function 0x080FE594..0x080FE7BC, including its pools. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[12];
    u16 effect_id;
    u16 flag;
} Descriptor;

typedef struct {
    u16 tick;
    u8 channels[2];
    u16 commands[2];
} SequenceEvent;

typedef struct {
    u16 unknown_00;
    s16 x, y;
    u8 variant;
    u8 unknown_07;
    u8 flag;
    u8 unknown_09[3];
    void *position;
    void *outputs[4];
    void *coordinate_task;
    void *display;
    void *script;
    void *initial_task;
    void *actor;
    void *effect_task;
    void *sound_task;
    SequenceEvent event;
} Payload;

typedef void (*BufferInitializer)(void *, u32);
extern BufferInitializer const g_callbacks_0836D4B8[];
extern const u8 data_0839DA9C[];
extern const void *const data_0839DA88[];
extern const u16 data_0839DC40[];
extern const u8 data_0839DB90[];
extern const void *const data_0839DB7C[];
extern const void *const data_0839DC18[];
extern const u16 data_0839D8C8[];
extern const void *const data_0839DC2C[];
extern const void *const data_0839DBFC[];
extern const u8 data_0839DC10[];

extern void *func_080E03F8(void *, const void *, u8, u8, const s16 *, void *);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern u32 func_080DD73C(const void *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void **, const void *, void *);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern u16 func_080035A8(u8);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DFD8C(const SequenceEvent *, u8, u16, u16, void *);
extern void *func_080D3F08(void *);
extern void *func_080D4D2C(void *, u8);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_080FE594(void *task, Descriptor *descriptor, Payload *payload)
{
    void *object;
    u8 mode;
    u16 duration;

    switch (descriptor->phase) {
    case 0:
        payload->variant = descriptor->effect_id - 0x92;
        payload->flag = descriptor->flag;
        payload->actor = descriptor->actor;
        mode = data_0839DA9C[payload->variant];
        if (payload->flag)
            mode = 0;
        payload->initial_task = func_080E03F8(payload->actor,
            data_0839DA88[payload->variant], mode, 1, 0, task);
        g_callbacks_0836D4B8[0](&payload->event, sizeof(payload->event));
        payload->event.commands[0] = data_0839DC40[payload->variant];
        break;
    case 1:
        break;
    case 0x100:
        payload->initial_task = func_080E05DC(payload->initial_task);
        if (payload->initial_task)
            break;
        if (!func_080D8858(payload->actor, 0)) {
            descriptor->phase = 2;
            break;
        }
        object = func_080DD4A4(payload->actor, 0);
        payload->position = func_080DD748(object, &payload->x, &payload->y, 0);
        if ((u8)func_080DD73C(payload->position))
            payload->y -= 8;
        payload->coordinate_task = func_080D6098(payload->x, payload->y, 0, 1,
            data_0839DB90[payload->variant], payload->outputs,
            data_0839DB7C[payload->variant], task);
        func_080D49FC(0, 2, 0, payload->x, payload->y);
        payload->display = func_080D4B64(0, data_0839DC18[payload->variant],
            data_0839D8C8[payload->variant], 6);
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940.display;
            flags |= mask;
            g_control_flags_03000940.display = flags;
        }
        payload->script = func_080D3E9C(data_0839DC2C[payload->variant], task);
        duration = 2;
        if (payload->variant != 1)
            duration = 10;
        payload->effect_task = func_080DCFE4(object, data_0839DBFC[payload->variant],
            12, data_0839DC10[payload->variant], duration, task,
            data_0839DC10[payload->variant]);
        payload->sound_task = func_080DFD8C(&payload->event, 1, 20, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        payload->script = func_080D3F08(payload->script);
        if (payload->script)
            break;
        payload->display = func_080D4D2C(payload->display, 0);
        if (payload->display)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task)
            break;
        payload->effect_task = func_080DBA5C(payload->effect_task);
        if (!payload->effect_task)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
