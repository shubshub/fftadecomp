#include "ffta.h"

// Target: complete [0x080FADA8, 0x080FB0B4), 780 bytes.

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[14];
    u16 flag;
} Descriptor080FADA8;

typedef struct {
    s16 x;
    s16 y;
    u8 flag;
    u8 ready;
    u8 kind;
    u8 shown;
    u8 count;
    u8 index;
    u8 timer;
    u8 unknown_0b[5];
    void *sound;
    void *children[4];
    void *visual;
    u8 unknown_28[12];
    void *effect;
    void *actor;
    void *stage;
    void *animation;
    void *sprites[4];
    void *result;
} Payload080FADA8;

typedef struct {
    u16 unknown_00;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    u16 selector;
    u16 delay;
    u32 unknown_18;
} Params080FADA8;

extern const u8 data_0839CA84[], data_0839CB88[], data_0839CAB4[], data_0839CAFC[];
extern const u8 data_0839CB8C[], data_0839CB74[], data_0894ABF0[];
extern const u8 data_08149D70[];
extern void *func_081443FC(void *destination, const void *source, u32 bytes);
extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080DD494(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *, u16, u16, void *);
extern s8 func_080DBC88(void *);
extern void func_080DBDC8(void *, s16 *, s16 *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void func_080D6194(void *, u8);
extern void *func_080D4724(const void *, void *, u16);
extern u8 func_080D8924(void *, u8, u16, void *);
extern void *func_080DD4A4(void *, u8);
extern u32 func_080FACF8();
extern void *func_08005B6C(u32 (*)(), u16, Params080FADA8 *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D6134(void *);
extern void *func_080D4774(void *);
extern u8 func_080E0570(void **, u8);
extern void func_080DBFFC(void *, u8);
extern u8 func_080D8B4C(void);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, s16);
extern u8 func_080DE1F0(void *);
extern void *func_080DBA5C(void *);

u32 func_080FADA8(void *task, Descriptor080FADA8 *descriptor,
                  Payload080FADA8 *payload)
{
    void *actor;
    u8 mode;
    Params080FADA8 params;
    u8 delays[5];
    const u8 *table;
    u16 delay;
    u8 i;
    u32 odd;
    u16 flags;
    void *object;
    u8 done;

    switch (descriptor->phase) {
    case 0:
        payload->flag = descriptor->flag;
        actor = descriptor->actor;
        payload->actor = actor;
        mode = 4;
        if (payload->flag)
            mode = 0;
        payload->stage = func_080E03F8(actor, data_0839CA84, mode, 1, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->stage = func_080E05DC(payload->stage);
        if (payload->stage)
            break;
        if (payload->flag) {
            payload->count = func_080DD494(payload->actor);
            payload->timer = 1;
            descriptor->phase = 0x103;
            break;
        }
        payload->animation = func_080DDF68(payload->actor, &payload->visual,
            0x98, 1, &payload->ready, data_0839CB88, 0, 0, task);
        payload->kind = func_080DBC88(payload->visual);
        if (payload->kind == 0 || payload->kind == 3)
            payload->shown = 0;
        else
            payload->shown = 1;
        descriptor->phase++;
        break;
    case 0x101:
        func_081443FC(delays, data_08149D70, sizeof(delays));
        if (!payload->ready)
            break;
        func_080DBDC8(payload->visual, &payload->x, &payload->y);
        table = data_0839CAB4;
        if ((u8)(payload->kind - 1) <= 1)
            table = data_0839CAFC;
        payload->effect = func_080D6098(payload->x, payload->y, 0, 1, 3,
            payload->unknown_28, table, task);
        if (payload->kind > 1)
            func_080D6194(payload->effect, 1);
        payload->sound = func_080D4724(data_0894ABF0, task, 0x14);
        payload->count = func_080D8924(payload->actor, 0, 0x1e, task);
        delay = delays[payload->count];
        for (i = 0; i < payload->count; i++) {
            params.selector = i;
            params.delay = delay;
            params.object = func_080DD4A4(payload->actor, i);
            payload->children[i] = func_08005B6C(func_080FACF8, 0x20, &params, task);
            delay += 10;
        }
        payload->result = func_080DFD8C(data_0839CB8C, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x102:
        payload->effect = func_080D6134(payload->effect);
        if (payload->effect)
            break;
        payload->sound = func_080D4774(payload->sound);
        if (payload->sound)
            break;
        if (!func_080E0570(payload->children, 4))
            break;
        payload->count = func_080DD494(payload->actor);
        if (!payload->count) {
            descriptor->phase = 2;
            break;
        }
        payload->timer = 1;
        descriptor->phase++;
        break;
    case 0x103:
        func_080DBFFC(payload->actor, payload->index);
        descriptor->phase++;
    case 0x104:
        if (func_080D8B4C())
            break;
        if (--payload->timer)
            break;
        object = func_080DD4A4(payload->actor, payload->index);
        odd = payload->index & 1;
        flags = 2;
        if (odd)
            flags = 4;
        payload->sprites[payload->index] = func_080DCFE4(object, data_0839CB74,
            12 - odd, 0, flags | 8, task, 0);
        payload->timer = 0x1e;
        payload->index++;
        if (payload->index != payload->count)
            descriptor->phase = 0x103;
        else
            descriptor->phase++;
        break;
    case 0x105:
        if (!func_080DE1F0(payload->visual))
            break;
        done = 1;
        for (i = 0; i <= 3; i++) {
            payload->sprites[i] = func_080DBA5C(payload->sprites[i]);
            if (payload->sprites[i])
                done = 0;
        }
        if (done)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
