typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

struct Descriptor {
    u16 phase;
    u16 unknown_02;
    u8 *actor;
};

struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
};

struct RotatingObject {
    void *object;
    struct InterpolationState x_motion;
    struct InterpolationState y_motion;
    s16 rotation;
    u16 unknown_1e;
};

struct MovingObject {
    void *object;
    struct InterpolationState x_motion;
    struct InterpolationState y_motion;
};

struct Payload {
    u16 counter;
    u16 unknown_02;
    u8 *actor;
    struct RotatingObject rotating[11];
    u8 unknown_168[0x60];
    struct MovingObject moving[14];
    void *resource_task;
    void *effect_task;
    void *record_task;
};

struct RotatingDefinition {
    s16 start_x;
    s16 start_y;
    s16 end_x;
    s16 end_y;
    const u16 *x_scale;
    const u16 *y_scale;
    u16 rotation;
    u16 unknown_12;
};

struct MovingDefinition {
    u8 kind;
    u8 start_x;
    u8 start_y;
    u8 unknown_03;
    s16 end_x;
    s16 end_y;
};

struct ControlState {
    u16 flags;
    u8 unknown_02[0x42];
    u32 window_mask : 6;
    u32 window_unknown : 2;
    u32 inverse_mask : 6;
    u32 inverse_unknown : 2;
    u32 unknown_46 : 16;
    u32 unknown_48 : 16;
    u32 blend_low : 4;
    u32 blend_high : 4;
};

/* Address bindings and local offset views; original extents are unknown. */
extern struct ControlState g_control_flags_03000940;
extern const u8 data_088F46CC[];
extern const struct RotatingDefinition data_083A2FD8[];
extern const u8 data_08501DB0[];
extern const struct MovingDefinition data_083A30F0[];
extern const u8 data_08501E68[];
extern const u8 data_0894D9D0[];
extern const u8 data_083A2F10[];
extern const u8 data_0894AA18[];

extern void *func_080D3AF8(void);
extern void func_08000B20(void *, u16, u32, u16);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void func_08003620(u8);
extern void *func_080D5CC0(const void *, u16, s16, s16, u16, u8, u8, u32);
extern void func_08011100(void *, u8);
extern void func_080110F8(void *, u8);
extern void func_080112E8(void *, u8);
extern void func_080112CC(void *, s16, s16, u16);
extern void func_080E0608(struct InterpolationState *, s16, s16, s16);
extern u32 func_080035D0(u8);
extern void *func_080D3EC0(const void *, u16, void *);
extern void func_0801DB3C(void);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D4704(const void *, void *);
extern void func_080D47DC(void *, u8);
extern void func_080E064C(struct InterpolationState *);
extern void func_080107D4(void *, s16, s16, u8);
extern u8 func_080E0690(struct InterpolationState *);
extern void func_08011428(void *);
extern u32 func_080035A8(u8);
extern void *func_080D4774(void *);
extern void *func_080D3F08(void *);

/* Target: complete [0x081104DC, 0x08110888), 940 bytes, 402 instructions. */
u32 func_081104DC(void *task, struct Descriptor *descriptor, struct Payload *payload)
{
    u8 index;

    switch (descriptor->phase) {
    case 0: {
        u16 resource;

        payload->actor = descriptor->actor;
        g_control_flags_03000940.blend_low = 15;
        g_control_flags_03000940.blend_high = 14;
        g_control_flags_03000940.flags &= 0x9fff;
        resource = 0x63fd;
        func_08000B20(func_080D3AF8(), resource, 0x06005800, 0x400);
        break;
    }
    case 1:
        break;
    case 0x100:
        descriptor->phase++;
        break;
    case 0x101:
        g_control_flags_03000940.blend_low = 15;
        g_control_flags_03000940.blend_high = 14;
        func_080D7220(data_088F46CC, 0, 2, 0, 0, 0);
        func_08003620(0);
        g_control_flags_03000940.blend_low = 0;
        g_control_flags_03000940.blend_high = 0;
        for (index = 0; index < 11; index++) {
            const struct RotatingDefinition *definition = &data_083A2FD8[index];
            struct RotatingObject *object = &payload->rotating[index];

            object->object = func_080D5CC0(data_08501DB0, index,
                definition->start_x, definition->start_y, 0x2f0, 6, 0, 0);
            func_08011100(object->object, 2);
            func_080110F8(object->object, 1);
            func_080112E8(object->object, 1);
            func_080112CC(object->object, 0x100, 0x100, 0);
            func_080E0608(&object->x_motion, definition->start_x,
                definition->end_x, 60);
            func_080E0608(&object->y_motion, definition->start_y,
                definition->end_y, 60);
        }
        for (index = 0; index < 14; index++) {
            const struct MovingDefinition *definition = &data_083A30F0[index];
            struct MovingObject *object = &payload->moving[index];

            object->object = func_080D5CC0(data_08501E68, definition->kind,
                definition->start_x, definition->start_y, 0x2d4, 6, 0, 0);
            func_08011100(object->object, 2);
            func_080E0608(&object->x_motion, definition->start_x,
                definition->end_x, 60);
            func_080E0608(&object->y_motion, definition->start_y,
                definition->end_y, 60);
        }
        g_control_flags_03000940.window_mask = 0x3f;
        g_control_flags_03000940.window_unknown = 0;
        g_control_flags_03000940.inverse_mask = 0x3f & ~func_080035D0(2);
        g_control_flags_03000940.inverse_unknown = 0;
        g_control_flags_03000940.flags |= 0x8000;
        payload->resource_task = func_080D3EC0(data_0894D9D0, 40, task);
        func_0801DB3C();
        payload->record_task = func_080DFD8C(data_083A2F10, 1, 4, 0, task);
        payload->effect_task = func_080D4704(data_0894AA18, task);
        func_080D47DC(payload->effect_task, 6);
        descriptor->phase++;
        break;
    case 0x102: {
        u32 finished = 1;
        u8 update_index;

        payload->counter++;
        for (update_index = 0; update_index < 11; update_index++) {
            const struct RotatingDefinition *definition = &data_083A2FD8[update_index];
            struct RotatingObject *object = &payload->rotating[update_index];
            u16 x_scale;
            u16 y_scale;
            u16 rotation;

            if (object->object == 0)
                continue;
            func_080E064C(&object->x_motion);
            func_080E064C(&object->y_motion);
            func_080107D4(object->object, object->x_motion.current,
                object->y_motion.current, 0);
            object->rotation += definition->rotation;
            x_scale = 0x100;
            if (definition->x_scale != 0)
                x_scale = definition->x_scale[payload->counter];
            y_scale = 0x100;
            if (definition->y_scale != 0)
                y_scale = definition->y_scale[payload->counter];
            rotation = object->rotation;
            func_080112CC(object->object, (s16)x_scale, (s16)y_scale,
                rotation);
            if (func_080E0690(&object->x_motion)) {
                func_08011428(object->object);
                object->object = 0;
            } else {
                finished = 0;
            }
        }
        for (update_index = 0; update_index < 14; update_index++) {
            struct MovingObject *object = &payload->moving[update_index];

            if (object->object == 0)
                continue;
            func_080E064C(&object->x_motion);
            func_080E064C(&object->y_motion);
            func_080107D4(object->object, object->x_motion.current,
                object->y_motion.current, 0);
            if (func_080E0690(&object->x_motion)) {
                func_08011428(object->object);
                object->object = 0;
            } else {
                finished = 0;
            }
        }
        if (finished) {
            g_control_flags_03000940.flags &= ~func_080035A8(2);
            *payload->actor = 7;
            descriptor->phase++;
        }
        break;
    }
    case 0x103:
        payload->effect_task = func_080D4774(payload->effect_task);
        if (payload->effect_task != 0)
            break;
        payload->resource_task = func_080D3F08(payload->resource_task);
        if (payload->resource_task == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
