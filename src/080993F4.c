#include "ffta.h"

typedef struct {
    void *handle;
    u8 unknown_04[12];
} Child080993F4;

typedef struct {
    void *owner;
    void *allocation;
    void *process;
    void *second_allocation;
    void *main_context;
    void *second_context;
    void *third_context;
    u8 *graphics;
    void *third_allocation;
    u8 unknown_24[0x370];
    Child080993F4 children[2];
} Object080993F4;

typedef u32 (*Callback080993F4)(void *node, void *payload);

extern void func_0808F7CC(void *handle);
extern void func_08007170(void *owner, void *allocation);
extern void *func_08021AD0(void *process);
extern void func_0800718C(void *owner);
extern void *func_080C7908(void *context);
extern void func_080C7CC0(void *context, Callback080993F4 callback, void *payload);
extern u32 func_0809AB24(void *node, void *payload);
extern void func_0814941C(u8 *graphics);

/* 0x080993F4..0x08099470: 124 bytes, 47 instructions. */
void *func_080993F4(Object080993F4 *object)
{
    void *owner;
    s32 i;

    for (i = 0; i < 2; i++) {
        func_0808F7CC(object->children[i].handle);
    }
    func_08007170(object->owner, object->third_allocation);
    owner = func_08021AD0(object->process);
    func_0800718C(owner);
    func_08007170(object->owner, object->allocation);
    func_080C7908(object->third_context);
    func_080C7908(object->second_context);
    func_080C7CC0(object->main_context, func_0809AB24, object);
    owner = func_080C7908(object->main_context);
    func_0800718C(owner);
    func_08007170(object->owner, object->second_allocation);
    func_0814941C(object->graphics);
    owner = object->owner;
    func_08007170(owner, object);
    return owner;
}
