#include "ffta.h"

typedef u32 (*TaskCallback0811896C)(void *, void *, void *);

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *field_04;
    u32 field_08;
    u8 unknown_0C[10];
    u16 field_16;
} Descriptor0811896C;

typedef struct {
    u8 index;
    u8 unknown_01;
    u16 field_02;
    u8 field_04;
    u8 unknown_05[3];
    void *child;
    void *field_0C;
} Payload0811896C;

typedef struct {
    u32 unknown_00;
    void *field_04;
    u32 field_08;
    u32 field_0C;
    u32 unknown_10;
    u16 field_14;
    u16 field_16;
    u32 unknown_18;
} Request0811896C;

extern const TaskCallback0811896C data_083A60C8[];
extern const u16 data_083A60DC[];
extern void func_080D38B4(void);
extern void *func_08005B6C(TaskCallback0811896C, u16, void *, void *);
extern void *func_080E051C(void *);

/* Complete target [0x0811896C, 0x08118A06): 154 bytes. */
u32 func_0811896C(void *task, Descriptor0811896C *descriptor,
                  Payload0811896C *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->field_02 = descriptor->field_08;
        payload->index = descriptor->field_08 - 0x33;
        payload->field_04 = descriptor->field_16;
        payload->field_0C = descriptor->field_04;
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        {
            Request0811896C request;

            request.field_14 = payload->field_02;
            request.field_16 = payload->field_04;
            request.field_04 = payload->field_0C;
            request.field_08 = 0;
            request.field_0C = 0;
            payload->child = func_08005B6C(data_083A60C8[payload->index],
                                          data_083A60DC[payload->index],
                                          &request, task);
            descriptor->phase++;
        }
        break;
    case 0x101:
        payload->child = func_080E051C(payload->child);
        if (payload->child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
