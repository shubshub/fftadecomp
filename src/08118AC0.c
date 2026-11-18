#include "ffta.h"

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *field_04;
} Descriptor08118AC0;

typedef struct {
    u32 unknown_00;
    void *field_04;
    void *field_08;
    void *field_0C;
    void *field_10;
} Payload08118AC0;

extern const u8 data_083A616C[];
extern const u8 data_0894AB00[];
extern u8 data_03003920[];

extern void func_0814186C(const void *, void *, u32);
extern void *func_080E03F8(void *, const void *, u8, u8, void *, void *);
extern void *func_080E05DC(void *);
extern void *func_080F2E40(u8, void *, void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080D4774(void *);
extern void *func_080F1210(void *);

// Complete target [0x08118AC0, 0x08118B92): 210 bytes.
u32 func_08118AC0(void *task, Descriptor08118AC0 *descriptor,
                  Payload08118AC0 *payload)
{
    switch (descriptor->phase) {
    case 0:
    {
        u32 params;
        u16 fill0;
        u16 fill1;

        payload->field_0C = descriptor->field_04;
        params = 0x00F800D8;
        fill0 = 0;
        func_0814186C(&fill0, data_03003920, 0x01000040);
        fill1 = 0;
        func_0814186C(&fill1, data_03003920 + 0x200, 0x01000070);
        payload->field_10 = func_080E03F8(payload->field_0C, data_083A616C,
                                          5, 6, &params, task);
        break;
    }
    case 1:
        break;
    case 0x100:
        payload->field_10 = func_080E05DC(payload->field_10);
        if (payload->field_10 == 0) {
            payload->field_04 = func_080F2E40(3, payload->field_0C, task);
            payload->field_08 = func_080D4704(data_0894AB00, task);
            descriptor->phase++;
        }
        break;
    case 0x101:
        payload->field_08 = func_080D4774(payload->field_08);
        if (payload->field_08 == 0) {
            payload->field_04 = func_080F1210(payload->field_04);
            if (payload->field_04 == 0)
                descriptor->phase = 2;
        }
        break;
    }
    return 0;
}
