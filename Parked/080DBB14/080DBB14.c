#include "ffta.h"

typedef struct {
    void *resource;
    u8 type;
    u8 palette;
    u16 value;
} TransitionDefinition;

typedef struct {
    s16 opening_speed;
    s16 delay;
    s16 closing_speed;
    u16 initial_delay;
} TransitionOptions;

typedef struct {
    u16 state;
    u16 unknown_2;
    const TransitionDefinition *definition;
    const TransitionOptions *options;
    u32 unknown_C[4];
} TransitionTask;

typedef u32 (*TaskCallback)(void *, void *, void *);
extern u32 func_080DAE7C(void *task, void *control, void *state);
extern void *func_08005B6C(TaskCallback callback, u16 payload_size,
                          void *descriptor, void *parent);

/* Complete [0x080DBB14, 0x080DBB74): 96 bytes including literal pool.
 * 70b58bb00f9e0906090e12060790104c07ad686820400843120c0e4908401043
 * 0d4a1040686009981043ff390843099009a81b041343436001950290074814216a46
 * 331c2af708f80bb070bc02bc084700ffffffff00ffffffff00007dae0d08
 */
void *func_080DBB14(void *resource, u8 type, u8 palette, u16 initial_delay,
                    void *parent)
{
    TransitionTask request;
    TransitionDefinition definition;
    TransitionOptions options;

    definition.resource = resource;
    definition.type = type;
    definition.palette = palette;
    definition.value = 0;
    options.opening_speed = -1;
    options.delay = -1;
    options.closing_speed = -1;
    options.initial_delay = initial_delay;
    request.definition = &definition;
    request.options = &options;
    return func_08005B6C(func_080DAE7C, 0x14, &request, parent);
}
