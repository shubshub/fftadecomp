/* Complete target: [0x080DDF68, 0x080DE074), 268 bytes, 117 instructions. */
#include "ffta.h"

typedef struct Object {
    u8 unknown_00[0x1F];
    s8 value;
    u8 unknown_20[0x10];
    u32 flags;
} Object;

typedef struct ObjectRecord {
    u32 owner;
    u8 unknown_04[4];
    s8 parameter;
    u8 unknown_09[9];
    u16 duration;
} ObjectRecord;

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

extern Object *func_080DD47C(void *group);
extern void func_080DD720(Object *object, u32 mask);
extern ObjectRecord *func_080A880C(void *group);
extern void func_0809836C(u32 owner, u16 command, int value, u16 duration);
extern Object *func_080DD350(Object *object);
extern void func_080DE12C(Object *object, u16 command, s8 value);
extern u32 func_080DDE1C(void *group, u16 entry, u16 flags);
extern u32 func_080DDC18(void *task, void *descriptor, void *payload);
extern void *func_08005B6C(TaskCallback callback, u16 payload_size,
                           void *descriptor, void *parent);

/* Sends a command to the group's object and reports the record's duration.
 * func_080DE524 repeats this block instruction for instruction
 * (0x080DE560..0x080DE5CE against 0x080DDF90..0x080DDFFE here), with the
 * duration pointer held in r7 (sp+0x34 here, sp there; 080DE524 never reads
 * its slot back). */
static inline Object *send_object_command(void *group, u16 command,
                                          u16 *duration)
{
    Object *object;

    *duration = 0;
    object = func_080DD47C(group);

    if (!(command & 0x4000))
        func_080DD720(object, 2);
    else
        command &= 0xBFFF;

    if (command & 0x8000) {
        ObjectRecord *record = func_080A880C(group);

        command &= 0x7FFF;
        func_0809836C(record->owner, command, record->parameter,
                      record->duration);
        *duration = record->duration;
    } else {
        func_080DE12C(object, command, func_080DD350(object)->value);
    }
    return object;
}

void *func_080DDF68(void *group, Object **out, u16 command, u8 count,
                    u8 *finished, const void *entries, u16 flags, u16 delay,
                    void *parent)
{
    EffectSpawnCommand descriptor;
    EffectSpawnConfig config;
    u16 duration;
    Object *object;

    object = send_object_command(group, command, &duration);
    if (out)
        *out = object;
    config.owner = (u32)object;
    config.count = count;
    config.finished = finished;
    config.entries = entries;
    config.delay = delay;
    config.flags = flags;
    if (flags & 1) {
        config.special_parameter = 0;
        config.sound = func_080DDE1C(group, duration, config.flags);
        if (config.sound == 0)
            config.flags &= 0xFFFE;
    }
    descriptor.config = &config;
    return func_08005B6C(func_080DDC18, 0x2C, &descriptor, parent);
}
