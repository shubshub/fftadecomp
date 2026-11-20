#include "ffta.h"

typedef struct {
    void *context;
    u8 unknown_04[0x40];
    void *child;
    u8 unknown_48[0x80];
    u8 active;
    u8 unknown_C9[7];
    u32 flags;
    u8 unknown_D4[8];
    u16 count;
    u8 unknown_DE[0xDA];
} SceneState;

struct ListSource;
struct SceneObject;

typedef struct {
    void *handle;
    u8 unknown_04[12];
} SceneChild;

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
    SceneChild children[2];
} SceneContext;

typedef void (*BufferInitializer)(void *destination, u32 bytes);

extern SceneState *data_0200F4A8;
extern void *data_0200F4AC;
extern void *data_0200F4B0;
extern u8 *data_0200F4B8;
extern BufferInitializer g_callbacks_0836D4B8[];

extern void func_0809D458(void *child);
extern void *func_08096D7C(void);
extern u32 func_08099CDC(struct ListSource *context, void **out);
extern u32 func_080995C0(struct SceneObject *object);
extern void *func_080993F4(SceneContext *context);
extern void func_0800718C(void *owner);
extern void *func_0808F77C(void);
extern void func_08022854(u8 *allocation);
extern u32 func_08022080(u32 count);
extern u32 func_0814913C(u8 count);
extern void func_080BD054(void);

/* Complete [0x08096CB8, 0x08096D7C), 196 bytes. */
void func_08096CB8(void)
{
    void *entries[13];
    s32 count;
    s32 i;

    func_0809D458(data_0200F4A8->child);
    data_0200F4A8 = 0;
    count = func_08099CDC(func_08096D7C(), entries);
    for (i = 0; i < count; ++i)
        func_080995C0(entries[i]);
    func_0800718C(func_080993F4(func_08096D7C()));
    func_0800718C(func_0808F77C());
    g_callbacks_0836D4B8[0](data_0200F4AC, 0x4400);
    func_08022854(data_0200F4AC);
    {
        u8 *storage = data_0200F4B8;
        u32 context_size = func_08022080(0x34);

        g_callbacks_0836D4B8[0](storage,
            ((func_0814913C(1) + context_size + 0x1668) & ~0x1F) + 0x20);
    }
    func_08022854(data_0200F4B8);
    func_080BD054();
    data_0200F4B0 = 0;
}
