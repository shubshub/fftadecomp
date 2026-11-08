#include "ffta.h"

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

typedef struct TaskParameters {
    u16 x;
    u16 y;
    u16 depth;
    u16 count;
    u8 mode;
    void **outputs;
    const void *entries;
} TaskParameters;

typedef struct TaskRequest {
    u16 state;
    u16 unknown_02;
    TaskParameters *parameters;
    u32 unknown_08[5];
} TaskRequest;

void func_0801E6F0(u16 *x, u16 *y);
u32 func_080D4DEC(void *task, void *descriptor, void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_080D6098(u16 x, u16 y, u16 depth, u8 mode, u16 count,
                    void **outputs, const void *entries, void *parent)
{
    TaskParameters parameters;
    TaskRequest request;
    u16 offset_x;
    u16 offset_y;

    parameters.x = x;
    parameters.y = y;
    parameters.depth = depth;
    parameters.mode = mode & 0x7F;
    parameters.count = count;
    parameters.outputs = outputs;
    parameters.entries = entries;
    if (parameters.mode == 1 && !(mode & 0x80)) {
        func_0801E6F0(&offset_x, &offset_y);
        parameters.x += offset_x;
        parameters.y += offset_y;
    }
    request.parameters = &parameters;
    return func_08005B6C(func_080D4DEC, 0x1C, &request, parent);
}
