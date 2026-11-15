#include "ffta.h"

/* Target: complete [0x080F7F70, 0x080F830C), 924 bytes. */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u32 unknown_08[3];
    u16 selector;
    u16 flag;
    u32 unknown_18;
} Descriptor080F7F70;

typedef struct {
    s16 x;
    s16 y;
    u8 flag;
    u8 ready;
    u8 kind;
    u8 variant;
    u8 count;
    u8 index;
    u8 delay;
    u8 unknown_0b[5];
    void *first_child;
    void *second_child;
    void *effect_object;
    void *script_child;
    void *tasks[4];
    void *output;
    void *object;
    void *setup_child;
    void *output_child;
    void *children[4];
    void *record_child;
} Payload080F7F70;

extern const u8 data_08149D5C[];
extern const u8 data_0839BE7C[];
extern const void *const data_0839BE74[];
extern const u8 data_0839BED0[];
extern const void *const data_0839BEB0[];
extern const u16 data_0839BEB8[];
extern const u8 data_0894A370[];
extern const u8 data_0894ACE0[];
extern const u8 data_0894D69C[];
extern const u8 data_0839BED4[];
extern const u8 data_0839BEBC[];
extern u16 g_control_flags_03000940;
extern void *func_081443FC(void *destination, const void *source, u32 bytes);
extern void *func_080DD47C(void *);
extern u8 func_080DBC88(void *);
extern void *func_080E03F8(void *, const void *, u8, u8, const s16 *, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080DD494(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *, u16, u16, void *);
extern void func_080DBDC8(void *, s16 *, s16 *);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern void func_0800BE10(void *, u8);
extern u32 func_080035A8(u8);
extern void *func_080D4704(const void *, void *);
extern void *func_080D4724(const void *, void *, u16);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_080D8924(void *, u8, u16, void *);
extern void *func_080DD4A4(void *, u8);
extern u32 func_080F7EC0(void *, Descriptor080F7F70 *, void *);
extern void *func_08005B6C(void *callback, int size, Descriptor080F7F70 *descriptor, void *owner);
extern void *func_080D4D2C(void *, u8);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern u8 func_080E0570(void **, int);
extern void func_080DBFFC(void *, u8);
extern u8 func_080D8B4C(void);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, s16);
extern u8 func_080DE1F0(void *);
extern void *func_080DBA5C(void *);

u32 func_080F7F70(void *task, Descriptor080F7F70 *descriptor,
                  Payload080F7F70 *payload)
{
    Descriptor080F7F70 child;
    u8 delays[5];
    u8 mode;
    u8 i;
    u16 delay;

    switch (descriptor->phase) {
    case 0:
        payload->flag = descriptor->flag;
        payload->object = descriptor->object;
        payload->kind = func_080DBC88(func_080DD47C(payload->object));
        if (payload->kind == 0 || payload->kind == 3)
            payload->variant = 0;
        else
            payload->variant = 1;
        mode = data_0839BE7C[payload->variant];
        if (payload->flag)
            mode = 0;
        payload->setup_child = func_080E03F8(payload->object,
            data_0839BE74[payload->variant], mode, 1, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->setup_child = func_080E05DC(payload->setup_child);
        if (payload->setup_child)
            break;
        if (payload->flag) {
            payload->count = func_080DD494(payload->object);
            payload->delay = 1;
            descriptor->phase = 0x103;
        } else {
            payload->output_child = func_080DDF68(payload->object,
                &payload->output, 0x34, 1, &payload->ready, data_0839BED0,
                0, 0, task);
            descriptor->phase++;
        }
        break;
    case 0x101:
        func_081443FC(delays, data_08149D5C, sizeof(delays));
        if (!payload->ready)
            break;
        func_080DBDC8(payload->output, &payload->x, &payload->y);
        func_080D49FC(0, 2, 0, payload->x, payload->y);
        payload->effect_object = func_080D4B64(0,
            data_0839BEB0[payload->variant], data_0839BEB8[payload->variant], 6);
        if (payload->kind > 1)
            func_0800BE10(payload->effect_object, 1);
        {
            u32 mask = func_080035A8(2);
            u16 display = g_control_flags_03000940;
            display |= mask;
            g_control_flags_03000940 = display;
        }
        payload->first_child = func_080D4704(data_0894A370, task);
        payload->second_child = func_080D4724(data_0894ACE0, task, 16);
        payload->script_child = func_080D3E9C(data_0894D69C, task);
        payload->record_child = func_080DFD8C(data_0839BED4, 1, 4, 0, task);
        payload->count = func_080D8924(payload->object, 0, 30, task);
        delay = delays[payload->count];
        for (i = 0; i < payload->count; i++) {
            child.selector = i;
            child.flag = delay;
            child.object = func_080DD4A4(payload->object, i);
            payload->tasks[i] = func_08005B6C(func_080F7EC0, 0x20, &child, task);
            delay += 10;
        }
        descriptor->phase++;
        break;
    case 0x102:
        payload->effect_object = func_080D4D2C(payload->effect_object, 0);
        if (payload->effect_object)
            break;
        {
            u32 mask = func_080035A8(2);
            u16 display = g_control_flags_03000940;
            display &= ~mask;
            g_control_flags_03000940 = display;
        }
        payload->script_child = func_080D3F08(payload->script_child);
        if (payload->script_child)
            break;
        payload->first_child = func_080D4774(payload->first_child);
        if (payload->first_child)
            break;
        payload->second_child = func_080D4774(payload->second_child);
        if (payload->second_child)
            break;
        if (!func_080E0570(payload->tasks, 4))
            break;
        payload->count = func_080DD494(payload->object);
        if (!payload->count) {
            descriptor->phase = 2;
        } else {
            payload->delay = 1;
            descriptor->phase++;
        }
        break;
    case 0x103:
        func_080DBFFC(payload->object, payload->index);
        descriptor->phase++;
    case 0x104: {
        void *object;
        u32 parity;
        u16 flags;
        if (func_080D8B4C())
            break;
        if (--payload->delay)
            break;
        object = func_080DD4A4(payload->object, payload->index);
        parity = payload->index & 1;
        flags = parity ? 4 : 2;
        payload->children[payload->index] = func_080DCFE4(object, data_0839BEBC,
            12 - parity, 0, flags | 8, task, 0);
        payload->delay = 30;
        payload->index++;
        if (payload->index != payload->count)
            descriptor->phase = 0x103;
        else
            descriptor->phase++;
        break;
    }
    case 0x105: {
        u8 complete;
        if (!func_080DE1F0(payload->output))
            break;
        complete = 1;
        for (i = 0; i < 4; i++) {
            payload->children[i] = func_080DBA5C(payload->children[i]);
            if (payload->children[i])
                complete = 0;
        }
        if (complete)
            descriptor->phase = 2;
        break;
    }
    }
    return 0;
}
