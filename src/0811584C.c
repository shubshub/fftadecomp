#include "ffta.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[0xC];
    u16 variant;
} Descriptor0811584C;

typedef struct {
    u16 flags;
    u16 variant;
    u8 unknown_04[5];
    u8 mode;
    u8 unknown_0a[10];
} EffectSettings0811584C;

typedef struct {
    u8 variant;
    u8 delay;
    u8 count;
    u8 index;
    void *actor;
    void *object;
    void *children[4];
    EffectSettings0811584C settings;
} Payload0811584C;

typedef void (*CopyBuffer0811584C)(void *destination, const void *source,
                                 u32 size);

extern CopyBuffer0811584C const data_0836D4BC[];
extern const EffectSettings0811584C data_083A3D20;
extern u8 func_080D8858(void *actor, u16 index);
extern void *func_080DD4B4(void *actor, u8 index);
extern void func_080DB838(void *object);
extern u8 func_080D8B4C(void);
extern void *func_080DBA5C(void *child);
extern void *func_080DD4A4(void *actor, u8 index);
extern void *func_080DCFE4(void *object, const void *settings, u8 position,
                          u16 duration, u16 flags, void *task, u16 delay);

/* Target [0x0811584C, 0x08115A1C), 464 bytes. */
u32 func_0811584C(void *task, Descriptor0811584C *descriptor,
                  Payload0811584C *payload)
{
    u8 index;

    switch (descriptor->phase) {
    case 0:
        payload->variant = descriptor->variant;
        payload->actor = descriptor->actor;
        payload->count = func_080D8858(payload->actor, 0);
        if (!payload->count)
            break;
        data_0836D4BC[0](&payload->settings, &data_083A3D20,
                         sizeof(payload->settings));
        switch (payload->variant) {
        case 0:
            break;
        case 1:
            payload->settings.variant = 7;
            break;
        case 2:
            payload->settings.variant = 6;
            payload->settings.mode = 1;
            break;
        case 3:
            payload->settings.variant = 2;
            payload->settings.mode = 1;
            break;
        case 4:
            payload->settings.variant = 4;
            break;
        }
        payload->object = func_080DD4B4(payload->actor, payload->index);
        func_080DB838(payload->object);
        break;
    case 1:
        break;
    case 0x100:
        if (!payload->count) {
            descriptor->phase = 0x103;
            break;
        }
        if (func_080D8B4C())
            break;
        {
            void *object;
            void *child;
            s32 parity;
            u16 flags;

            for (index = 0; index < 4; index++)
                payload->children[index] = func_080DBA5C(payload->children[index]);
            object = func_080DD4A4(payload->actor, payload->index);
            parity = payload->index & 1;
            flags = 2;
            if (parity != 0)
                flags = 4;
            child = func_080DCFE4(object, &payload->settings,
                12 - (payload->index & 6), 0, flags | 8, task, 0);
            payload->children[payload->index & 3] = child;
        }
        payload->index++;
        if (payload->index == payload->count) {
            descriptor->phase = 0x103;
        } else {
            payload->delay = 30;
            descriptor->phase++;
        }
        break;
    case 0x101:
        if (--payload->delay == 0) {
            payload->object = func_080DD4B4(payload->actor, payload->index);
            func_080DB838(payload->object);
            descriptor->phase = 0x100;
        }
        break;
    case 0x102:
        descriptor->phase++;
        break;
    case 0x103:
        {
            u8 done = 1;

            for (index = 0; index < 4; index++) {
                payload->children[index] = func_080DBA5C(payload->children[index]);
                if (payload->children[index] != 0)
                    done = 0;
            }
            if (done)
                descriptor->phase = 2;
        }
        break;
    }
    return 0;
}
