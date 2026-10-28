#include "ffta.h"

typedef void (*Callback)(void *object);

typedef struct {
    s16 state;
} State;

extern Callback func_08005C00(void *object);
extern State *func_08005BFC(void *object);
extern u16 func_08005BAC(void *object);
extern void func_08005B58(void *object);
extern void func_080D5128(void *object);
extern void func_080D5594(void *object);
extern void func_080D5A60(void *object);

static inline u8 object_finished(void *object)
{
    Callback callback = func_08005C00(object);

    if (callback == func_080D5128 || callback == func_080D5594) {
        State *state = func_08005BFC(object);
        if (state->state == 4)
            return 1;
    } else if (callback == func_080D5A60) {
        if (func_08005BAC(object) == 0x104)
            return 1;
    }
    return 0;
}

void *func_080D6530(void *object)
{
    if (object && object_finished(object)) {
        func_08005B58(object);
        return 0;
    }
    return object;
}
