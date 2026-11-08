/* 0x080DF9AC: 56 target bytes, including the callback literal.
 * 70b58ab00e9d0f9e0006000e1b041b0c07ac20806160a260638068468582019404481c216a46
 * 331c26f7caf80ab070bc02bc084791ef0d08
 */
#include "ffta.h"

typedef struct SceneObject SceneObject;

typedef struct TaskParameters080DF9AC {
    s16 selector;
    u16 duration;
    SceneObject *object;
    void *argument;
} TaskParameters080DF9AC;

typedef struct SchedulerDescriptor080DF9AC {
    u16 phase;
    u16 unknown_02;
    TaskParameters080DF9AC *parameters;
    u8 unknown_08[12];
    u16 first;
    u8 unknown_16[6];
} SchedulerDescriptor080DF9AC;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080DEF90(void *task, void *descriptor, void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_080DF9AC(u8 selector, SceneObject *object, void *argument,
                    u16 duration, u16 first, void *parent)
{
    SchedulerDescriptor080DF9AC descriptor;
    TaskParameters080DF9AC parameters;

    parameters.selector = selector;
    parameters.object = object;
    parameters.argument = argument;
    parameters.duration = duration;
    descriptor.first = first;
    descriptor.parameters = &parameters;
    return func_08005B6C(func_080DEF90, 0x1C, &descriptor, parent);
}
