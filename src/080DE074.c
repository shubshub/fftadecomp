/* 0x080DE074: complete 56-byte caller, including the callback literal.
 * 30b58ab00d9d00906846002401716946ff2048716846c28004814381049005480c2103aa
 * 2b1c27f767fd0ab030bc02bc0847000001d90d08
 */
#include "ffta.h"

typedef struct Parameters080DE074 {
    void *object;
    u8 kind;
    s8 value;
    u16 action;
    s16 option;
    u16 delay;
} Parameters080DE074;

typedef struct SchedulerDescriptor080DE074 {
    u16 state;
    u8 unknown_02[2];
    const Parameters080DE074 *parameters;
    u8 unknown_08[0x14];
} SchedulerDescriptor080DE074;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080DD900(void *task, void *descriptor, void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

static inline void *start_task(const Parameters080DE074 *parameters,
                               void *parent)
{
    SchedulerDescriptor080DE074 descriptor;

    descriptor.parameters = parameters;
    return func_08005B6C(func_080DD900, 0xC, &descriptor, parent);
}

void *func_080DE074(void *object, u8 kind, u16 action, u16 delay,
                    void *parent)
{
    Parameters080DE074 parameters;

    parameters.object = object;
    parameters.kind = kind;
    parameters.value = -1;
    parameters.action = action;
    parameters.option = 0;
    parameters.delay = delay;
    return start_task(&parameters, parent);
}
