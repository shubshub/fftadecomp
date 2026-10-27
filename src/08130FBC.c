#include "ffta.h"

/* 08130FBC .. 08131024: 104 bytes. */
typedef struct {
    void *entry;
    void *unit;
    u8 unknown_08[0x28];
    const u8 *attributes;
} Object;

typedef struct {
    u8 unknown_00[0x60];
    Object object;
} State;

extern Object data_0200F3F0;
extern State g_state_0200F390;
extern u8 (*data_083A8604[])(Object *);
extern u8 func_080C8298(void *);
extern u8 func_080CDCEC(void *);

static inline u8 dispatch_object(Object *object)
{
    if (!object->entry || !object->unit)
        return 0;
    return data_083A8604[object->attributes[0]](object);
}

u8 func_08130FBC(void)
{
    Object *object = &data_0200F3F0;
    State *state;

    if (object->attributes[0] != 28 && func_080C8298(object->unit))
        return 0;
    state = &g_state_0200F390;
    if (func_080CDCEC(state->object.unit))
        return 0;
    return dispatch_object(&state->object);
}
