/* 0x080E4844, 464 target bytes:
 * f0b584b0071c0e1c151c31888020400081422bd0814202dc00290bd0d0e00448
 * 814259d00130814200d19de0c8e0000001010000b08a2870f08a68707068e860
 * 291daa1d0023f8f75dffa8600649287880004018006801210091062100220023
 * eff794feace00000dc6c39080421685e0622a95e012400942a1c10320192144a
 * 0292039700220123f1f7e4fb6861687804400221002c00d00421e86800910197
 * 3221029100210c220023f8f779fb686208492878800040180068391c1322eff7
 * 0fffe8610c2068803088013077e00000c46c3908ec6c39086888013868800004
 * 020c002a6cd11b49287880004018006804242b5f0624295f0091019200210222
 * f2f76cfc1448391ceff7dafea8611348391ceff7a1fa286202201ef723fe104a
 * 1188014311806978012008400822002800d010220b4928788000401800680421
 * 0a43009701210023fbf7fef9a8623088013034e0e46c3908388d9408d4d69408
 * 40090003046d39086869f1f7c1fb6861002825d1a86941420143cc0feff7d8fe
 * a86100281cd1002c06d002201ef7eafd0e4a118881431180286aeff793fa2862
 * 00280dd1e869eff7c3fee861002807d1686af7f731f86862002801d102203080
 * 002004b0f0bc02bc0847000040090003
 */
#include "ffta.h"

typedef struct E4844Descriptor {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[0xC];
    u16 selector;
    u16 flags;
} E4844Descriptor;

typedef struct E4844Payload {
    u8 selector;
    u8 flags;
    u16 countdown;
    s16 horizontal;
    s16 vertical;
    void *underlying_object;
    void *object;
    u8 unknown_10[4];
    void *coordinate_child;
    void *mask_child;
    void *selected_child;
    void *sequence_child;
    void *effect_child;
    void *sound_child;
} E4844Payload;

void *func_080DD748(void *object, s16 *horizontal, s16 *vertical, s32 mode);
void func_080D45D0(const void *record, u8 destination, u8 bank, u8 start, u8 count);
void *func_080D6098(s16 horizontal, s16 vertical, s16 depth, u8 mode,
                  u16 count, void *storage, const void *records, void *parent);
void *func_080DCFE4(void *object, const void *record, u8 mode, u16 duration,
                  u16 flags, void *parent, s16 fallback_duration);
void *func_080D4724(const void *record, void *parent, u16 flags);
void func_080D7220(const void *record, u8 bank, u8 layer, s16 horizontal,
                  s16 vertical, u16 flags);
void *func_080D4704(const void *record, void *parent);
void *func_080D3E9C(const void *record, void *parent);
u16 func_080035A8(u8 layer);
void *func_080DFD8C(const void *record, u8 count, u16 flags, s16 delay,
                  void *parent);
void *func_080D6134(void *task);
void *func_080D4774(void *task);
void *func_080D3F08(void *task);
void *func_080DBA5C(void *task);

u32 func_080E4844(void *task, void *descriptor_pointer, void *payload_pointer)
{
    E4844Descriptor *descriptor = descriptor_pointer;
    E4844Payload *payload = payload_pointer;
    const void *const *initial_records = (const void *const *)0x08396CDC;
    const void *const *selected_records = (const void *const *)0x08396CEC;
    const void *const *layer_records = (const void *const *)0x08396CE4;
    const void *const *sound_records = (const void *const *)0x08396D04;
    u16 *display_shadow = (u16 *)0x03000940;
    u16 flags;
    u16 mask;
    u32 had_mask_child;

    switch (descriptor->phase) {
    case 0:
        payload->selector = descriptor->selector;
        payload->flags = descriptor->flags;
        payload->object = descriptor->object;
        payload->underlying_object = func_080DD748(payload->object,
            &payload->horizontal, &payload->vertical, 0);
        func_080D45D0(initial_records[payload->selector], 6, 0, 0, 1);
        break;
    case 0x100:
        payload->coordinate_child = func_080D6098(payload->horizontal,
            payload->vertical, 0, 1, 1, payload->unknown_10,
            (const void *)0x08396CC4, task);
        flags = payload->flags & 1 ? 4 : 2;
        payload->effect_child = func_080DCFE4(payload->object, 0, 12, 0,
            flags, task, 50);
        payload->selected_child = func_080D4724(
            selected_records[payload->selector], task, 0x13);
        payload->countdown = 12;
        descriptor->phase++;
        break;
    case 0x101:
        payload->countdown--;
        if (payload->countdown == 0) {
            func_080D7220(layer_records[payload->selector], 0, 2,
                payload->horizontal, payload->vertical, 0);
            payload->mask_child = func_080D4704((const void *)0x08948D38, task);
            payload->sequence_child = func_080D3E9C((const void *)0x0894D6D4, task);
            mask = func_080035A8(2);
            *display_shadow |= mask;
            flags = payload->flags & 1 ? 0x10 : 8;
            payload->sound_child = func_080DFD8C(
                sound_records[payload->selector], 1, flags | 4, 0, task);
            descriptor->phase++;
        }
        break;
    case 0x102:
        payload->coordinate_child = func_080D6134(payload->coordinate_child);
        if (payload->coordinate_child != 0)
            break;
        had_mask_child = payload->mask_child != 0;
        payload->mask_child = func_080D4774(payload->mask_child);
        if (payload->mask_child != 0)
            break;
        if (had_mask_child) {
            mask = func_080035A8(2);
            *display_shadow &= ~mask;
        }
        payload->sequence_child = func_080D3F08(payload->sequence_child);
        if (payload->sequence_child != 0)
            break;
        payload->selected_child = func_080D4774(payload->selected_child);
        if (payload->selected_child != 0)
            break;
        payload->effect_child = func_080DBA5C(payload->effect_child);
        if (payload->effect_child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
