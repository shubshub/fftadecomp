/* 0x080DE4F4: 48 target bytes, including the callback literal.
 * 70b58db0129d139e07ac07902171a260e3602582019405482c216a46331c27f72bfb0db070bc02bc0847000019dc0d08
 */
#include "ffta.h"

typedef struct EffectSpawnConfig {
    u32 owner;
    u8 count;
    u8 unknown_05[3];
    u8 *finished;
    const void *entries;
    u16 delay;
    u16 flags;
    s8 special_parameter;
    u8 unknown_15;
    u16 sound;
} EffectSpawnConfig;

typedef struct EffectSpawnCommand {
    u16 state;
    u16 unknown_02;
    const EffectSpawnConfig *config;
    u8 unknown_08[0x14];
} EffectSpawnCommand;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080DDC18(void *task, void *descriptor, void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_080DE4F4(u32 owner, u32 count, u8 *finished, const void *entries,
                    u32 unused, u32 delay, void *parent)
{
    EffectSpawnCommand descriptor;
    EffectSpawnConfig config;

    config.owner = owner;
    config.count = count;
    config.finished = finished;
    config.entries = entries;
    config.delay = delay;
    descriptor.config = &config;
    return func_08005B6C(func_080DDC18, 0x2C, &descriptor, parent);
}
