/* 0x080DC31C: 48 target bytes, including the callback literal.
 * 10b587b0099c0906090e1b061b0e019068468182c2820383044810216a46231c29f716fc07b010bc02bc0847d1b60d08
 */
#include "ffta.h"

typedef struct DcRequest {
    u16 state;
    u8 unknown_02[2];
    u32 identifier;
    u8 unknown_08[0x0C];
    s16 enabled;
    u16 parameter;
    u16 mode;
    u8 unknown_1A[2];
} DcRequest;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080DB6D0(void *task, void *descriptor, void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_080DC31C(u32 identifier, u8 enabled, u16 parameter, u8 mode,
                    void *parent)
{
    DcRequest descriptor;

    descriptor.identifier = identifier;
    descriptor.enabled = enabled;
    descriptor.parameter = parameter;
    descriptor.mode = mode;
    return func_08005B6C(func_080DB6D0, 0x10, &descriptor, parent);
}
