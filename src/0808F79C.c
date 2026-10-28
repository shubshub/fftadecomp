#include "ffta.h"

typedef void (*ObjectCallback0808F79C)(void *object, u32 size);

extern ObjectCallback0808F79C g_callbacks_0836D4B8[];
extern void *data_0200F458;
extern void *func_08007138(void *context, u32 size);

/* 0x0808F79C: 48 bytes; allocate and initialize the object. */
void *func_0808F79C(void)
{
    void *object = func_08007138(data_0200F458, 0x16C);
    g_callbacks_0836D4B8[0](object, 0x16C);
    return object;
}
