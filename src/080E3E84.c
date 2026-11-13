#include "ffta.h"

// 0x080E3E84 .. 0x080E4052: 462 bytes.
typedef struct E3E84Descriptor {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[0xC];
    u16 flags;
    u16 selector;
} E3E84Descriptor;

typedef struct E3E84Payload {
    u8 flags;
    u8 selector;
    u16 countdown;
    s16 horizontal;
    s16 vertical;
    void *underlying_object;
    void *object;
    u8 unknown_10[0xC];
    void *coordinate_child;
    void *mask_child;
    void *selected_child;
    void *effect_child;
    void *sound_child;
} E3E84Payload;

typedef struct E3E84Triple {
    const void *word[3];
} E3E84Triple;

extern void *func_080DD748(void *source, s16 *first, s16 *second, s16 *third);
extern void func_080DE10C(void *object, int value);
extern void func_080DE3BC(void *object, int value);
extern void func_080DF8CC(void *object);
extern void *func_080D6098(s16 horizontal, s16 vertical, s16 depth, u8 mode,
                  u16 count, void *storage, const void *records, void *parent);
extern void *func_080DCFE4(void *object, const void *record, u8 mode, u16 duration,
                  u16 flags, void *parent, s16 fallback_duration);
extern void *func_080DFD8C(const void *record, u8 count, u16 flags, s16 delay,
                  void *parent);
extern void func_080D7220(const void *record, u8 bank, u8 layer, s16 horizontal,
                  s16 vertical, u16 flags);
extern void *func_080D4704(const void *record, void *parent);
extern void *func_080D4724(const void *record, void *parent, u16 flags);
extern void *func_080D6134(void *task);
extern void *func_080D4774(void *task);
extern void *func_080DBA5C(void *task);

extern const u8 data_083968C0[];
extern const u8 data_08396908[];
extern const u8 data_08396944[];
extern const E3E84Triple data_08149C88;
extern const E3E84Triple data_08149C94;
extern const u8 data_088F4680[];

u32 func_080E3E84(void *task, void *descriptor_pointer, void *payload_pointer)
{
    E3E84Descriptor *descriptor = descriptor_pointer;
    E3E84Payload *payload = payload_pointer;
    E3E84Triple first;
    E3E84Triple second;
    u16 flags;

    switch (descriptor->phase) {
    case 0:
        payload->flags = descriptor->flags;
        payload->selector = descriptor->selector;
        payload->object = descriptor->object;
        payload->underlying_object = func_080DD748(payload->object,
            &payload->horizontal, &payload->vertical, 0);
        if (payload->selector == 1) {
            func_080DE10C(payload->underlying_object, 0x24);
            func_080DE3BC(payload->underlying_object, 1);
        }
        break;
    case 1:
        break;
    case 0x100:
        payload->coordinate_child = func_080D6098(payload->horizontal,
            payload->vertical, 0, 1, 3, payload->unknown_10,
            data_083968C0, task);
        flags = payload->flags & 1 ? 4 : 2;
        payload->effect_child = func_080DCFE4(payload->object,
            data_08396908 + payload->selector * 20, 12, 0, flags, task, 60);
        flags = payload->flags & 1 ? 0x10 : 8;
        payload->sound_child = func_080DFD8C(data_08396944, 1, flags | 4, 0,
            task);
        payload->countdown = 12;
        descriptor->phase++;
        break;
    case 0x101:
        first = data_08149C88;
        second = data_08149C94;
        payload->countdown--;
        if (payload->countdown == 0) {
            if (payload->selector != 2) {
                func_080D7220(data_088F4680, 0, 2, payload->horizontal,
                    payload->vertical, 0);
                payload->mask_child = func_080D4704(
                    first.word[payload->selector], task);
            }
            payload->selected_child = func_080D4724(
                second.word[payload->selector], task, 7);
            payload->countdown = 3;
            descriptor->phase++;
        }
        break;
    case 0x102:
        if (payload->countdown != 0) {
            payload->countdown--;
            if (payload->countdown != 0)
                break;
            func_080DF8CC(payload->underlying_object);
        }
        payload->coordinate_child = func_080D6134(payload->coordinate_child);
        if (payload->coordinate_child != 0)
            break;
        payload->mask_child = func_080D4774(payload->mask_child);
        if (payload->mask_child != 0)
            break;
        payload->selected_child = func_080D4774(payload->selected_child);
        if (payload->selected_child != 0)
            break;
        descriptor->phase++;
        break;
    case 0x103:
        payload->effect_child = func_080DBA5C(payload->effect_child);
        if (payload->effect_child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
