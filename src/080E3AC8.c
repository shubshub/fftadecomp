/* 0x080E3AC8, 322 target bytes:
 * f0b54f464646c0b484b080460f1c151c
 * 39888020400081421bd0814202dc0029
 * 0ad086e00348814272d00130814278d0
 * 7fe0000001010000b88a2870f88a6870
 * 7868e860a91c2a1d0023f9f719fea860
 * 6fe00221685e0422a95e284b2a78d218
 * 127800922a1c10320192254b2a789200
 * d218126802924246039200220123f2f7
 * a7fa6862e868f9f72bfd000600164142
 * 0143ca0f697801208146084002260028
 * 00d00426e868910089188900154a8918
 * 154c2a78121913780096424601922a78
 * 1219127802920c22f9f728faa8626978
 * 484608400822002800d010222878c000
 * 0a49401804210a434146009101210023
 * fcf7e8f8e8623888013019e0db673908
 * cc673908f8673908206839083c683908
 * 686af2f7abfa686200280ad138880130
 * 06e0a86af7f736ffa862002801d10220
 * 3880002004b018bc9846a146f0bc02bc
 * 0847
 */
#include "ffta.h"
#include "effect_task.h"

typedef struct E3AC8Descriptor {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[0xC];
    u16 selector;
    u16 flags;
} E3AC8Descriptor;

typedef struct E3AC8Payload {
    u8 selector;
    u8 flags;
    s16 horizontal;
    s16 vertical;
    u16 unknown_06;
    void *underlying_object;
    void *object;
    u8 unknown_10[0x14];
    void *coordinate_child;
    void *effect_child;
    void *sound_child;
} E3AC8Payload;

extern void *func_080DD748(void *source, s16 *first, s16 *second, s16 *third);
extern void *func_080D6098(s16 x, s16 y, u16 depth, u8 mode, u16 count,
                  void *outputs, const void *entries, void *parent);
extern s8 func_080DD5A8(void *object);

extern void *func_080DFD8C(const void *events, u8 count, u16 flags, u16 delay,
                  void *parent);
extern void *func_080D6134(void *task);
extern void *func_080DBA5C(void *object);

extern const u8 data_083967DB[];
extern const void *const data_083967CC[];
extern const u8 data_083967F8[][20];
extern const u8 data_08396820[];
extern const u8 data_0839683C[][8];

u32 func_080E3AC8(void *task, E3AC8Descriptor *descriptor,
                  E3AC8Payload *payload)
{
    u32 active;
    u16 flags;

    switch (descriptor->phase) {
    case 0:
        payload->selector = descriptor->selector;
        payload->flags = descriptor->flags;
        payload->object = descriptor->object;
        payload->underlying_object = func_080DD748(payload->object,
            &payload->horizontal, &payload->vertical, 0);
        break;
    case 0x100:
        payload->coordinate_child = func_080D6098(payload->horizontal,
            payload->vertical, 0, 1, data_083967DB[payload->selector],
            payload->unknown_10, data_083967CC[payload->selector], task);
        active = func_080DD5A8(payload->object) != 0;
        flags = payload->flags & 1 ? 4 : 2;
        payload->effect_child = func_080DCFE4(payload->object,
            data_083967F8[active], 12, data_08396820[payload->selector],
            flags, task, data_08396820[payload->selector]);
        flags = payload->flags & 1 ? 0x10 : 8;
        payload->sound_child = func_080DFD8C(
            data_0839683C[payload->selector], 1, flags | 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        payload->coordinate_child = func_080D6134(payload->coordinate_child);
        if (payload->coordinate_child == 0)
            descriptor->phase++;
        break;
    case 0x102:
        payload->effect_child = func_080DBA5C(payload->effect_child);
        if (payload->effect_child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
