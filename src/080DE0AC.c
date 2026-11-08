/* 0x080DE0AC: 52 target bytes, including the callback literal.
 * 70b58ab00e9d0f9c109e0090684602714171c38004814581049005480c2103aa331c27f74dfd0ab070bc02bc0847000001d90d08
 */
#include "ffta.h"

typedef struct Parameters080DE0AC {
    void *object;
    u8 kind;
    u8 value;
    u16 action;
    u16 option;
    u16 delay;
} Parameters080DE0AC;

typedef struct SchedulerDescriptor080DE0AC {
    u16 state;
    u16 unknown_02;
    const Parameters080DE0AC *parameters;
    u8 unknown_08[0x14];
} SchedulerDescriptor080DE0AC;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080DD900(void *task, void *descriptor, void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

static inline void *start_task(const Parameters080DE0AC *parameters,
                               void *parent)
{
    SchedulerDescriptor080DE0AC descriptor;

    descriptor.parameters = parameters;
    return func_08005B6C(func_080DD900, 0xC, &descriptor, parent);
}

void *func_080DE0AC(void *object, u32 value, u32 kind, u32 action, u32 delay,
                    u32 option, void *parent)
{
    Parameters080DE0AC parameters;

    parameters.object = object;
    parameters.kind = kind;
    parameters.value = value;
    parameters.action = action;
    parameters.option = option;
    parameters.delay = delay;
    return start_task(&parameters, parent);
}
