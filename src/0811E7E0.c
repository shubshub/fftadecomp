#include "ffta.h"

/* Target: complete [0x0811E7E0, 0x0811E88E), 174 bytes including literals. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *value;
} Descriptor0811E7E0;

typedef struct {
    u8 unknown_00[0x34];
    u16 field_34;
} Object0811E7E0;

typedef struct {
    u16 delay;
    u16 unknown_02;
    u32 unknown_04;
    void *value;
    Object0811E7E0 *object;
    void *child;
    void *record_task;
} Payload0811E7E0;

extern const u8 data_0894C898[];
extern const u8 data_083A736C[];
extern Object0811E7E0 *func_080DD350(void *);
extern void func_080D35D8(void);
extern void *func_080D4704(const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void func_080DE10C(void *, u16);
extern void *func_080D4774(void *);

u32 func_0811E7E0(void *task, Descriptor0811E7E0 *descriptor,
                  Payload0811E7E0 *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->value = descriptor->value;
        payload->object = func_080DD350(payload->value);
        break;
    case 1:
        func_080D35D8();
        break;
    case 0x100:
        payload->child = func_080D4704(data_0894C898, task);
        payload->record_task = func_080DFD8C(data_083A736C, 1, 4, 0, task);
        payload->delay = 10;
        descriptor->phase++;
        break;
    case 0x101:
        if (--payload->delay == 0) {
            payload->object->field_34 = 43;
            func_080DE10C(payload->value, 16);
            descriptor->phase++;
        }
        break;
    case 0x102:
        payload->child = func_080D4774(payload->child);
        if (payload->child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
