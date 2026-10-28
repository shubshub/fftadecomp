#include "ffta.h"

typedef void (*ObjectCallback0808F7CC)(void *object, u32 size);

extern ObjectCallback0808F7CC g_callbacks_0836D4B8[];
extern void *data_0200F458;
extern void func_08007170(void *context, void *object);

/* 0x0808F7CC: 44 bytes; initialize the object and attach its context. */
void func_0808F7CC(void *object)
{
    g_callbacks_0836D4B8[0](object, 0x16C);
    func_08007170(data_0200F458, object);
}
