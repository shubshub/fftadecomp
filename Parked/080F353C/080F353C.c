#include "ffta.h"

typedef struct Task080F353C Task080F353C;
typedef struct CoordinateSource080F353C CoordinateSource080F353C;
typedef struct EntityState080F353C EntityState080F353C;

typedef struct {
    u16 phase;
    u16 unknown_02;
    u32 input;
    u8 unknown_08[0x0E];
    u16 mode;
} Descriptor080F353C;

/* These six observed halfwords are a view, not a complete object extent. */
typedef struct {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} Interpolation080F353C;

typedef struct {
    s16 x;
    s16 y;
    u8 unknown_04;
    u8 mode;
    u8 unknown_06[2];
    void *object;
    CoordinateSource080F353C *coordinates;
    EntityState080F353C *entity;
    u32 input;
    Interpolation080F353C interpolation;
    Task080F353C *opening;
    u32 handle;
    Task080F353C *timeline;
    Task080F353C *child;
    Task080F353C *animation;
    Task080F353C *effect;
    Task080F353C *result;
} Payload080F353C;

extern u16 g_control_flags_03000940;
extern u32 func_080035A8(u8 index);
extern void func_080D38B4(void);
extern Task080F353C *func_080E03F8(u32 input, const void *resource,
                                  u8 mode, u8 flags, u16 value,
                                  Task080F353C *parent);
extern Task080F353C *func_080E05DC(Task080F353C *task);
extern u8 func_080D3B54(u32 input);
extern CoordinateSource080F353C *func_080DD4B4(u32 input, u8 index);
extern EntityState080F353C *func_080DD4A4(u32 input, u8 index);
extern void *func_080DD47C(u32 input);
extern u8 func_080D8858(u32 input, u16 flags);
extern Task080F353C *func_080DF75C(void *object,
                                  CoordinateSource080F353C *coordinates,
                                  s16 value, u16 id, u8 mode, u16 flags,
                                  Task080F353C *parent);
extern u8 func_080DBA3C(Task080F353C *task);
extern u8 func_080DD580(EntityState080F353C *entity);
extern void func_080DBDC8(CoordinateSource080F353C *coordinates,
                         s16 *x, s16 *y);
extern void func_080D49FC(u8 index, u8 mode, u16 flags, s16 x, s16 y);
extern u32 func_080D4B64(u8 index, const void *resource, u16 id, u8 mode);
extern void func_080E0608(Interpolation080F353C *state,
                         s16 start, s16 end, s16 duration);
extern Task080F353C *func_080D3E9C(const void *resource, Task080F353C *parent);
extern Task080F353C *func_080D4704(const void *resource, Task080F353C *parent);
extern Task080F353C *func_080DFD8C(const void *resource, u8 mode, u16 flags,
                                  u16 value, Task080F353C *parent);
extern Task080F353C *func_080DCFE4(EntityState080F353C *entity,
                                  const void *resource, u8 mode, u16 value,
                                  u16 flags, Task080F353C *parent, s16 extra);
extern void func_080E064C(Interpolation080F353C *state);
extern u32 func_080D4D2C(u32 handle, u8 index);
extern Task080F353C *func_080D3F08(Task080F353C *task);
extern Task080F353C *func_080D4774(Task080F353C *task);
extern Task080F353C *func_080DBA5C(Task080F353C *task);
extern void func_080DF790(Task080F353C *task);
extern void func_080DE328(EntityState080F353C *entity);

/* Target: complete [0x080F353C, 0x080F378C), 592 bytes, including
 * 538 code bytes, 48 literal bytes and six internal alignment bytes. */
u32 func_080F353C(Task080F353C *task, Descriptor080F353C *descriptor,
                  Payload080F353C *payload)
{
    switch (descriptor->phase) {
    case 0:
        {
            u8 mode;
            payload->mode = descriptor->mode;
            payload->input = descriptor->input;
            mode = 3;
            if (payload->mode != 0)
                mode = 0;
            payload->opening = func_080E03F8(payload->input,
                                            (const void *)0x0839ABA4,
                                            mode, 0, 0, task);
        }
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->opening = func_080E05DC(payload->opening);
        if (payload->opening)
            break;
        if (func_080D3B54(payload->input)) {
            descriptor->phase = 2;
            break;
        }
        payload->coordinates = func_080DD4B4(payload->input, 0);
        payload->entity = func_080DD4A4(payload->input, 0);
        payload->object = func_080DD47C(payload->input);
        if (!func_080D8858(payload->input, 0)) {
            descriptor->phase = 2;
            break;
        }
        payload->animation = func_080DF75C(payload->object,
                                          payload->coordinates,
                                          0xA0, 0x3E5, 6, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (!func_080DBA3C(payload->animation))
            break;
        if (func_080DD580(payload->entity)) {
            func_080DBDC8(payload->coordinates, &payload->x, &payload->y);
            func_080D49FC(0, 2, 0, payload->x, (s16)(payload->y - 16));
            payload->handle = func_080D4B64(0, (const void *)0x088EF35C,
                                           0x3E6, 6);
            {
                u32 mask = func_080035A8(2);
                g_control_flags_03000940 |= mask;
            }
            func_080E0608(&payload->interpolation,
                          (s16)(payload->y - 16),
                          (s16)(payload->y - 24), 32);
            payload->timeline = func_080D3E9C((const void *)0x0894D900, task);
            payload->child = func_080D4704((const void *)0x08949D30, task);
            payload->result = func_080DFD8C((const void *)0x0839ABDC,
                                           1, 4, 0, task);
        }
        payload->effect = func_080DCFE4(payload->entity,
                                       (const void *)0x0839ABC8,
                                       12, 32, 4, task, 0);
        descriptor->phase++;
        break;
    case 0x102:
        if (payload->handle) {
            func_080E064C(&payload->interpolation);
            func_0800BC08(0, payload->x, payload->interpolation.current);
        }
        payload->handle = func_080D4D2C(payload->handle, 0);
        if (payload->handle)
            break;
        {
            u32 mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
        }
        payload->timeline = func_080D3F08(payload->timeline);
        if (payload->timeline)
            break;
        payload->child = func_080D4774(payload->child);
        if (payload->child)
            break;
        descriptor->phase++;
        break;
    case 0x103:
        payload->effect = func_080DBA5C(payload->effect);
        if (payload->effect)
            break;
        func_080DF790(payload->animation);
        func_080DE328(payload->entity);
        descriptor->phase++;
        break;
    case 0x104:
        payload->animation = func_080DBA5C(payload->animation);
        if (payload->animation)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
