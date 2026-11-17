#include "ffta.h"

// Complete target: 0x080E54C8..0x080E5694, 460 bytes.

typedef struct StagedEffectEvent {
    u16 phase;
    u8 unknown_02[2];
    void *object;
    u8 unknown_08[14];
    u16 flag;
    u8 unknown_18[4];
} StagedEffectEvent;

typedef struct StagedEffectWork {
    u8 count;
    u8 index;
    u8 timer;
    u8 flag;
    void *first_child;
    void *second_child;
    void *slots[4];
    void *effect;
    void *object;
    void *load_handle;
} StagedEffectWork;

typedef struct SpawnDescriptor {
    u8 unknown_00[4];
    void *object;
    u8 unknown_08[12];
    u16 index;
    u8 unknown_16[6];
} SpawnDescriptor;

typedef struct BlankDescriptor {
    u8 unknown_00[28];
} BlankDescriptor;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

extern const u8 data_08396DDC[];
extern const u8 data_0894ADAC[];

extern u32 func_080E4EB0(void *task, void *descriptor, void *payload);
extern u32 func_080E5310(void *task, void *descriptor, void *payload);
extern u32 func_080E5438(void *task, void *descriptor, void *payload);
extern void *func_08005B6C(TaskCallback callback, u16 payload_size,
                           void *descriptor, void *parent);
extern void *func_080E03F8(void *object, const void *resource, u32 type,
                           u32 enabled, u32 flags, void *context);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *object);
extern void *func_080E051C(void *object);
extern u8 func_080D8858(void *object, u32 index);
extern void *func_080D4704(const void *resource, void *context);
extern void *func_080D4774(void *object);
extern u8 func_080E0570(void **slots, u16 count);
extern void *func_080DD4A4(void *object, u32 index);

u32 func_080E54C8(void *task, StagedEffectEvent *event, StagedEffectWork *work)
{
    BlankDescriptor first;
    BlankDescriptor second;
    SpawnDescriptor spawn;

    switch (event->phase) {
    case 0: {
        u32 type;

        work->flag = event->flag;
        work->object = event->object;
        type = 5;
        if (work->flag)
            type = 0;
        work->load_handle = func_080E03F8(work->object, data_08396DDC, type,
                                          1, 0, task);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        work->load_handle = func_080E05DC(work->load_handle);
        if (work->load_handle)
            break;
        work->timer = 1;
        if (work->flag) {
            work->count = func_080D8858(work->object, 0);
            event->phase = 0x103;
        } else {
            work->first_child = func_08005B6C(func_080E4EB0, 0x74, &first, task);
            work->effect = func_080D4704(data_0894ADAC, task);
            event->phase++;
        }
        break;
    case 0x101:
        work->first_child = func_080E051C(work->first_child);
        if (work->first_child)
            break;
        work->second_child = func_08005B6C(func_080E5310, 0x2c, &second, task);
        event->phase++;
        break;
    case 0x102:
        work->second_child = func_080E051C(work->second_child);
        if (work->second_child)
            break;
        work->effect = func_080D4774(work->effect);
        if (work->effect)
            break;
        work->index = 0;
        work->count = func_080D8858(work->object, 0);
        if (work->count)
            event->phase++;
        else
            event->phase = 2;
        break;
    case 0x103: {
        u8 slot;

        func_080E0570(work->slots, 4);
        work->timer--;
        if (work->timer)
            break;
        slot = 0;
        if (work->slots[0]) {
            do {
                slot++;
                if (slot > 3)
                    break;
            } while (work->slots[slot]);
        }
        spawn.index = work->index;
        spawn.object = func_080DD4A4(work->object, work->index);
        work->slots[slot] = func_08005B6C(func_080E5438, 0x14, &spawn, task);
        work->timer = 30;
        work->index++;
        if (work->index != work->count)
            break;
        event->phase++;
        break;
    }
    case 0x104:
        if (func_080E0570(work->slots, 4))
            event->phase = 2;
        break;
    }
    return 0;
}
