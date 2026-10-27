#include "ffta.h"

typedef struct SceneRecord08125624 {
    u8 unknown_00[0x28];
    u16 flags;
    u8 unknown_2A[0xDE];
} SceneRecord08125624;

typedef struct Binding08125624 {
    u32 unknown_00;
    SceneRecord08125624 *record;
} Binding08125624;

typedef struct SceneObject08125624 SceneObject08125624;
typedef void (*RecordInitializer08125624)(void *destination, u32 size);

extern SceneRecord08125624 g_state_02000080[24];
extern SceneRecord08125624 g_state_02002FC4[12];
extern RecordInitializer08125624 const g_callbacks_0836D4B8[];
extern SceneRecord08125624 *func_08121CB4(u8 selector);
extern SceneRecord08125624 *func_080C83CC(u8 category);
extern Binding08125624 *func_08121C70(u8 selector);
extern void *func_08096D7C(void);
extern SceneObject08125624 *func_08099560(void *manager,
                                       SceneRecord08125624 *record);
extern u32 func_080995C0(SceneObject08125624 *object);

static inline SceneRecord08125624 *resolve_record(u8 selector)
{
    SceneRecord08125624 *record;
    s32 index;

    if (selector == 255) {
        record = g_state_02000080;
        for (index = 0; index < 24; index++, record++) {
            if (record->flags & 0x400)
                return record;
        }
        return 0;
    } else if ((s8)selector < 0) {
        return func_08121CB4(selector);
    } else {
        return func_080C83CC(selector);
    }
}

/* Complete [0x08125624, 0x081256BC): 152 bytes, 61 instructions. */
void func_08125624(u8 selector)
{
    SceneRecord08125624 *record = resolve_record(selector);

    func_080995C0(func_08099560(func_08096D7C(), record));
    if ((s8)selector < 0) {
        Binding08125624 *binding = func_08121C70(selector);

        if (binding->record == record)
            binding->record = 0;
    }
    if ((u32)record >= (u32)g_state_02002FC4)
        g_callbacks_0836D4B8[0](record, sizeof(*record));
}
