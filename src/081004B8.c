#include "ffta.h"

// Target 0x081004B8, complete [0x081004B8, 0x081007EE), 822 bytes.

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[0xE];
    u16 variant;
} Descriptor081004B8;

typedef struct {
    s16 x;
    s16 y;
    u16 countdown;
    u8 variant;
    u8 mode;
    u8 relative_mode;
    u8 unknown_09[3];
    void *object;
    void *source;
    void *target;
    void *actor;
    void *initial_child;
    void *children[3];
    void *coordinate_child;
    void *effect_child;
    void *record_child;
} Payload081004B8;

extern const u8 data_0839E7C4[];
extern const u8 data_0839E7F4[];
extern const u8 data_0839E880[];
extern const u8 data_0839E83C[];
extern const u8 data_0839E888[];
extern const u8 data_0839E86C[];

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DD47C(void *);
extern void func_080DE10C(void *, u16);
extern s8 func_080DBC88(void *);
extern void func_080DBDC8(void *, s16 *, s16 *);
/* x and y are s16 here because the target loads them with ldrsh; the matched
 * definition declares them u16. */
extern void *func_080D6098(s16, s16, u16, u8, u16, void **, const void *,
                           void *);
extern void func_080D6194(void *, u8);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D6134(void *);
extern void func_080DE33C(void *, s8, u8);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD4C4(void *);
extern u8 func_080DBCD4(void *, void *);
extern u32 func_080DD71C(void *);
extern u8 func_080DD580(void *);
extern void func_080D6180(void *);
extern void func_0801115C(void *, u8);
extern void func_080D5F74(void **, u16);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern u8 func_080DE1F0(void *);
extern void *func_080DBA5C(void *);

static inline void SetChildrenVisible081004B8(void **children, u8 visible)
{
    u8 i;

    for (i = 0; i < 2; i++) {
        if (children[i] != 0)
            func_0801115C(children[i], visible);
    }
}

u32 func_081004B8(void *task, Descriptor081004B8 *descriptor,
                  Payload081004B8 *payload)
{
    u8 animation;
    s16 x;
    s16 y;

    switch (descriptor->phase) {
    case 0:
        payload->variant = descriptor->variant;
        payload->actor = descriptor->actor;
        animation = 4;
        if (payload->variant != 0)
            animation = 0;
        payload->initial_child = func_080E03F8(payload->actor, data_0839E7C4,
            animation, 0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_child = func_080E05DC(payload->initial_child);
        if (payload->initial_child != 0)
            break;
        if (func_080D3B54(payload->actor)) {
            descriptor->phase = 2;
            break;
        }
        payload->object = func_080DD47C(payload->actor);
        func_080DE10C(payload->object, 0x8c);
        payload->mode = func_080DBC88(payload->object);
        func_080DBDC8(payload->object, &x, &y);
        payload->coordinate_child = func_080D6098(x, y, 0, 1, 3,
            payload->children, data_0839E7F4, task);
        if (payload->mode > 1)
            func_080D6194(payload->coordinate_child, 1);
        payload->record_child = func_080DFD8C(data_0839E880, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        payload->coordinate_child = func_080D6134(payload->coordinate_child);
        if (payload->coordinate_child != 0)
            break;
        func_080DE33C(payload->object, payload->mode, 1);
        payload->countdown = 10;
        descriptor->phase++;
        break;
    case 0x102:
        payload->countdown--;
        if (payload->countdown != 0)
            break;
        payload->target = func_080DD4A4(payload->actor, 0);
        payload->source = func_080DD4C4(payload->target);
        payload->mode = func_080DBC88(payload->source);
        payload->relative_mode = func_080DBCD4(payload->object,
            payload->source);
        func_080DD71C(payload->source);
        func_080DBDC8(payload->source, &payload->x, &payload->y);
        payload->countdown = 20;
        descriptor->phase++;
        break;
    case 0x103:
        payload->countdown--;
        if (payload->countdown != 0)
            break;
        if (func_080DD580(payload->target) == 0) {
            descriptor->phase = 0x107;
            break;
        }
        payload->coordinate_child = func_080D6098(payload->x, payload->y,
            0, 1, 2, payload->children, data_0839E83C, task);
        if (payload->relative_mode > 1)
            func_080D6194(payload->coordinate_child, 1);
        func_080D6180(payload->coordinate_child);
        payload->countdown = 6;
        payload->record_child = func_080DFD8C(data_0839E888, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x104:
        payload->countdown--;
        SetChildrenVisible081004B8(payload->children,
            !(payload->countdown & 1));
        if (payload->countdown != 0)
            break;
        payload->countdown = 18;
        descriptor->phase++;
        break;
    case 0x105:
        payload->countdown--;
        if (payload->countdown != 0)
            break;
        payload->countdown = 6;
        descriptor->phase++;
        break;
    case 0x106:
        payload->countdown--;
        SetChildrenVisible081004B8(payload->children,
            payload->countdown & 1);
        if (payload->countdown != 0)
            break;
        func_080D5F74(payload->children, 2);
        descriptor->phase++;
        break;
    case 0x107:
        payload->effect_child = func_080DCFE4(payload->target,
            data_0839E86C, 12, 0, 4, task, 0);
        payload->countdown = 80;
        descriptor->phase++;
        break;
    case 0x108:
        payload->countdown--;
        if (payload->countdown != 0)
            break;
        func_080DD71C(payload->source);
        descriptor->phase++;
        break;
    case 0x109:
        if (func_080DE1F0(payload->object) == 0)
            break;
        payload->effect_child = func_080DBA5C(payload->effect_child);
        if (payload->effect_child != 0)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
