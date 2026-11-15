#include "ffta.h"

/* 0x08118D20: complete [0x08118D20, 0x08119066), 838 bytes, 419 instructions,
 * sha1 of the ROM bytes 74a678fd299de78f1e2d4db444a305a572ff14a1
 * (baserom.bin offset 0x118D20).
 */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[14];
    u16 unknown_16;
    u8 unknown_18[4];
} Descriptor08118D20;

typedef struct {
    u16 countdown;
    u8 index;
    u8 count;
    u8 unknown_04;
    u8 ready;
    u8 unknown_06[6];
    void *buffer;
    void *child_10;
    void *child_14;
    void *child_18;
    void *child_1c;
    void *unit;
    void *target;
    void *child_28;
    void *palette;
    u8 unknown_30[4];
    void *group;
    void *child_38;
    void *child_3c;
    void *children[4];
    void *child_50;
} Payload08118D20;

typedef u32 (*Callback08118D20)(void *, Descriptor08118D20 *, void *);

extern const u8 data_083A6254[];
extern const u8 data_083A624C[];
extern const u8 data_083A6238[];
extern const u8 data_0894C358[];

extern void *func_080D4774(void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080DF9AC(u8, void *, void *, u16, u16, void *);
extern void *func_080E051C(void *);
extern void *func_08005B6C(Callback08118D20, u16, Descriptor08118D20 *, void *);
extern u32 func_08118C4C(void *, Descriptor08118D20 *, void *);
extern u32 func_08118A08(void *, Descriptor08118D20 *, void *);
extern u32 func_08118AC0(void *, Descriptor08118D20 *, void *);
extern u32 func_08118B94(void *, Descriptor08118D20 *, void *);
extern u8 func_080DD494(void *);
extern void *func_080DD4B4(void *, u8);
extern void func_080DE268(void *);
extern void func_080D38B4(void);
extern void *func_080DD47C(void *);
extern void func_080DE10C(void *, u16);
extern void *func_080DE4B0(void *, u8 *, u8, s8, s8, u8, u16, void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080DBA5C(void *);
extern void func_080DE3BC(void *, u8);
extern void *func_080D3904(void);
extern void *func_0800A654(u32);
extern void func_08148318(const void *, void *, u16, u8);
extern void *func_08147D2C(u16, u16, u16, const void *);
extern void *func_081484CC(void *);
extern void func_0800A668(void *);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD4C4(void *);
extern u8 func_080DB838(void *);
extern u8 func_080D8B4C(void);
extern u8 func_080DBAB8(void **, u32);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);

u32 func_08118D20(void *task, Descriptor08118D20 *descriptor,
                  Payload08118D20 *payload)
{

    switch (descriptor->phase) {
    case 0:
        {
            u8 i;

            payload->unknown_04 = descriptor->unknown_16;
            payload->group = descriptor->object;
            payload->count = func_080DD494(payload->group);
            for (i = 0; i < payload->count; i++)
                func_080DE268(func_080DD4B4(payload->group, i));
        }
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->unit = func_080DD47C(payload->group);
        func_080DE10C(payload->unit, 0x3c);
        payload->child_38 = func_080DE4B0(payload->unit, &payload->ready,
                                          2, 2, 0, 0, 0, task);
        payload->child_50 = func_080DFD8C(data_083A624C, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->ready == 0)
            break;
        payload->child_28 = func_080D4704(data_0894C358, task);
        descriptor->phase++;
        break;
    case 0x102:
        payload->child_28 = func_080D4774(payload->child_28);
        if (payload->child_28 != 0)
            break;
        payload->child_50 = func_080DFD8C(data_083A6254, 1, 4, 0, task);
        payload->child_3c = func_080DF9AC(5, 0, payload->unit, 0x10, 6, task);
        descriptor->phase++;
        break;
    case 0x103:
        {
            Descriptor08118D20 d103;

            payload->child_3c = func_080DBA5C(payload->child_3c);
            if (payload->child_3c != 0)
                break;
            d103.object = payload->group;
            payload->child_10 = func_08005B6C(func_08118A08,
                                              0x10, &d103, task);
            descriptor->phase++;
        }
        break;
    case 0x104:
        {
            Descriptor08118D20 d104;

            payload->child_10 = func_080E051C(payload->child_10);
            if (payload->child_10 != 0)
                break;
            d104.object = payload->group;
            payload->child_14 = func_08005B6C(func_08118AC0,
                                              0x14, &d104, task);
            descriptor->phase++;
        }
        break;
    case 0x105:
        {
            Descriptor08118D20 d105;

            payload->child_14 = func_080E051C(payload->child_14);
            if (payload->child_14 != 0)
                break;
            d105.object = payload->group;
            payload->child_18 = func_08005B6C(func_08118B94,
                                              0x10, &d105, task);
            descriptor->phase++;
        }
        break;
    case 0x106:
        {
            Descriptor08118D20 d106;

            payload->child_18 = func_080E051C(payload->child_18);
            if (payload->child_18 != 0)
                break;
            d106.object = payload->group;
            payload->child_1c = func_08005B6C(func_08118C4C,
                                              0x10, &d106, task);
            descriptor->phase++;
        }
        break;
    case 0x107:
        payload->child_1c = func_080E051C(payload->child_1c);
        if (payload->child_1c != 0)
            break;
        descriptor->phase++;
        break;
    case 0x108:
        descriptor->phase++;
        break;
    case 0x109:
        {
            void *source;

            func_080DE3BC(payload->unit, 0);
            source = func_080D3904();
            payload->buffer = func_0800A654(0xc0);
            func_08148318(source, payload->buffer, 0x5f, 8);
            payload->palette = func_08147D2C(1, 0x5f, 0x1e, payload->buffer);
            descriptor->phase++;
        }
        break;
    case 0x10A:
        payload->palette = func_081484CC(payload->palette);
        if (payload->palette != 0)
            break;
        func_0800A668(payload->buffer);
        payload->countdown = 1;
        descriptor->phase++;
        break;
    case 0x10B:
        if (--payload->countdown != 0)
            break;
        payload->target = func_080DD4A4(payload->group, payload->index);
        func_080DB838(func_080DD4C4(payload->target));
        descriptor->phase++;
        /* fall through */
    case 0x10C:
        if (func_080D8B4C())
            break;
        func_080DBAB8(payload->children, 4);
        {
            u8 mode = (payload->index & 1) ? 4 : 2;
            payload->children[payload->index & 3] = func_080DCFE4(
                payload->target, data_083A6238,
                12 - (payload->index & 6), 10, mode | 8, task, 10);
        }
        payload->index++;
        if (payload->index == payload->count) {
            descriptor->phase++;
        } else {
            payload->countdown = 0x28;
            descriptor->phase = 0x10B;
        }
        break;
    case 0x10D:
        if (func_080DBAB8(payload->children, 4))
            descriptor->phase = 2;
        break;
    }
    return 0;
}
