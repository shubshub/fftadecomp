#include "effect_registry.h"

struct Request080D3508 {
    u8 unknown_00[4];
    void *object;
    u32 arg;
    u32 mode;
    u8 unknown_10[4];
    u16 id;
    u16 value;
    u16 extra;
};

extern void *data_0200F430;
extern void *data_020159C0;
extern u8 func_080D3B98(void *object, u16 entry_index);
extern u8 func_080D3B38(void *object);
extern u32 func_080E2398(void *task, void *request, void *payload);
extern void *func_08005954(void *manager, EffectRegistryCallback callback, u16 size,
                           void *request, void *parent);

// Complete target [0x080D3508, 0x080D35D8): 208 bytes, 81 instructions.
void *func_080D3508(u16 id, void *object, u32 arg)
{
    struct Request080D3508 request;
    EffectRegistryCallback callback;
    u16 size;
    u8 value;
    void *task = 0;

    request.id = id;
    request.object = object;
    request.arg = arg;
    request.mode = 0;
    if (id <= 0x155) {
        if (func_080D3B98(object, id))
            request.mode = 2;
        value = func_080D3B38(object);
        request.value = value;
        request.extra = 0;
        callback = data_083947D8[id - 1].callback;
        size = data_083947D8[id - 1].size;
    } else {
        callback = data_08395280[id - 0x156].callback;
        size = data_08395280[id - 0x156].size;
        if (id == 0x159) {
            if (func_080D3B98(object, (u16)arg))
                request.mode = 2;
            request.value = data_083947D8[arg - 1].metadata;
            request.extra = arg;
            callback = func_080E2398;
            size = 0x28;
        }
    }
    task = func_08005954(data_0200F430, callback, size, &request,
                         data_020159C0);
    return task;
}
