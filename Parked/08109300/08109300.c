#include "control_flags.h"

// Target 0x08109300, complete [0x08109300, 0x08109664), 868 bytes, 434 instructions.
typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *object;
    u8 unknown_08[0xe];
    u16 value;
} Descriptor08109300;

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *actor;
    u8 unknown_08[0xc];
    u16 mode;
    u8 unknown_16[6];
} ChildDescriptor08109300;

typedef struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} InterpolationState;

typedef struct {
    u16 timer;
    u8 index;
    u8 count;
    u8 flag;
    u8 unknown_05[7];
    void *children[4];
    void *selected;
    void *effect;
    void *screen;
    void *load;
    void *object;
    InterpolationState transition;
    void *overlay;
} Payload08109300;

extern const u8 data_083A12E4[];
extern const u8 data_088F63D8[];
extern const u8 data_0894DCD8[];
extern const u8 data_083A1700[];
extern const u8 data_0894DCCC[];
extern const u16 data_083A1314[];

extern u32 func_08109214(void *task, void *descriptor, void *payload);
extern void *func_08005B6C(u32 (*callback)(void *, void *, void *), u16 size,
                           void *descriptor, void *parent);
extern void *func_080E03F8(void *, const void *, u32, u32, u32, void *);
extern u8 func_080DD494(void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void func_0801E6F0(u16 *, u16 *);
extern u16 func_0801BB0C(s16, s16, u16);
extern void *func_080D3F08(void *);
extern u8 func_0801BDB0(void);
extern u32 func_080DD4B4(void *, u8);
extern void func_080DE268(u32);
extern void *func_080D9A24(u8, u8, u8, const void *, void *);
extern void func_080D9BA8(void *, int);
extern void func_080DBDEC(u8, void **, s16 *, s16 *, s16 *);
extern u16 func_0801BD68(s16, s16, s16, s16, u16);
extern void func_080E0608(InterpolationState *, s16, s16, s16);
extern void func_080E064C(InterpolationState *);
extern void *func_080D9B08(void *);
extern void func_0814186C(const void *, void *, u32);
extern u8 func_080E0690(InterpolationState *);
extern void *func_080DD4A4(void *, u8);
extern void func_080DD4C4(void);
extern void func_080DB838(void);
extern u8 func_080D8B4C(void);
extern u8 func_080E0570(void **, u32);
extern u16 func_080035A8(u8);
extern void *func_080D9B64(void *);

u32 func_08109300(void *task, Descriptor08109300 *descriptor,
                  Payload08109300 *payload)
{
    switch (descriptor->phase) {
    case 0: {
        u32 kind;
        void *object;

        payload->flag = descriptor->value;
        object = descriptor->object;
        payload->object = object;
        kind = 4;
        if (payload->flag)
            kind = 0;
        payload->load = func_080E03F8(object, data_083A12E4, kind, 7, 0, task);
        payload->count = func_080DD494(payload->object);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->load = func_080E05DC(payload->load);
        if (payload->load != 0)
            break;
        func_080D7220(data_088F63D8, 0, 2, 0, 0, 0);
        payload->effect = func_080D3E9C(data_0894DCD8, task);
        payload->overlay = func_080DFD8C(data_083A1700, 1, 4, 0, task);
        {
            u16 x;
            u16 y;

            func_0801E6F0(&x, &y);
            func_0801BB0C((s16)x, y - 0xa0, 0x3c);
        }
        descriptor->phase++;
        break;
    case 0x101:
        payload->effect = func_080D3F08(payload->effect);
        if (payload->effect != 0)
            break;
        if (func_0801BDB0() != 0)
            break;
        payload->timer = 0x14;
        descriptor->phase++;
        break;
    case 0x102:
        payload->timer--;
        if (payload->timer != 0)
            break;
        {
            s16 x;
            s16 y;
            s16 z;
            u8 i;

            for (i = 0; i < payload->count; i++)
                func_080DE268(func_080DD4B4(payload->object, i));
            payload->effect = func_080D3E9C(data_0894DCCC, task);
            payload->screen = func_080D9A24(0x10, 0, 0, 0, task);
            func_080D9BA8(payload->screen, 1);
            func_080DBDEC(0, 0, &x, &y, &z);
            x -= 0x78;
            y -= 0x50;
            func_0801BD68(x, y + 0x50 - 0xf0, x, y, 0x3c);
            func_080E0608(&payload->transition, 0, 0xa0, 0x3c);
        }
        descriptor->phase++;
        break;
    case 0x103: {
        void *buffer;

        func_080E064C(&payload->transition);
        buffer = func_080D9B08(payload->screen);
        func_0814186C(data_083A1314 + payload->transition.current, buffer, 0xa0);
        if (func_080E0690(&payload->transition) == 0)
            break;
        payload->timer = 0x14;
        descriptor->phase++;
        break;
    }
    case 0x104:
        payload->timer--;
        if (payload->timer != 0)
            break;
        payload->selected = func_080DD4A4(payload->object, payload->index);
        func_080DD4C4();
        func_080DB838();
        descriptor->phase++;
        /* fall through */
    case 0x105: {
        ChildDescriptor08109300 child;
        u32 slot;

        if (func_080D8B4C() != 0)
            break;
        func_080E0570(payload->children, 4);
        slot = payload->index & 3;
        child.mode = payload->index;
        child.actor = payload->selected;
        payload->children[slot] = func_08005B6C(func_08109214, 0x20, &child, task);
        payload->index++;
        if (payload->index == payload->count) {
            descriptor->phase++;
        } else {
            payload->timer = 0x28;
            descriptor->phase = 0x104;
        }
        break;
    }
    case 0x106:
        if (func_080E0570(payload->children, 4) == 0)
            break;
        func_080E0608(&payload->transition, 0xa0, 0x140, 0x3c);
        descriptor->phase++;
        break;
    case 0x107: {
        void *buffer;

        func_080E064C(&payload->transition);
        buffer = func_080D9B08(payload->screen);
        func_0814186C(data_083A1314 + payload->transition.current, buffer, 0xa0);
        if (func_080E0690(&payload->transition) == 0)
            break;
        descriptor->phase++;
        break;
    }
    case 0x108:
        payload->effect = func_080D3F08(payload->effect);
        if (payload->effect != 0)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        payload->screen = func_080D9B64(payload->screen);
        if (payload->screen != 0)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
