#include "ffta.h"

/* Complete [0x0812B980, 0x0812BA06): 134 bytes, 53 instructions. */
typedef struct {
    u8 unknown_00[6];
    u8 enabled;
} ScriptOwner;

typedef struct {
    u16 state;
    u16 unknown_02;
    ScriptOwner *owner;
} ContextScript;

struct Context;

typedef struct {
    ScriptOwner *owner;
    struct Context *context;
} ContextPayload;

typedef struct {
    u16 held;
    u16 pressed;
} InputState;

extern InputState data_03000000;
extern void *func_08096D7C(void);
extern struct Context *func_080BCA24(void *argument);
extern u8 func_080BCA40(void *context, u16 parameter);
extern void func_080BCA54(struct Context *context);

u32 func_0812B980(void *object, ContextScript *script, ContextPayload *payload)
{
    switch (script->state) {
    case 0:
        payload->owner = script->owner;
        break;
    case 1:
        break;
    case 0x100:
        payload->context = func_080BCA24(func_08096D7C());
        script->state = 0x101;
        break;
    case 0x101:
        if (func_080BCA40(payload->context, data_03000000.pressed) == 0) {
            func_080BCA54(payload->context);
            script->state = 0x102;
        }
        break;
    case 0x102:
        script->state = 0x103;
        break;
    case 0x103:
        payload->owner->enabled = 1;
        script->state = 3;
        break;
    }
    return 0;
}
