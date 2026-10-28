#include "ffta.h"

typedef struct {
    void *resource;
} Object080247FC;

extern void func_0808F7CC(void *resource);

/* 0x080247FC - 24 bytes.
 * Target: 10b5041c2068002803d06af0e1ff0020206010bc01bc0047
 */
void func_080247FC(Object080247FC *object)
{
    if (object->resource != 0) {
        func_0808F7CC(object->resource);
        object->resource = 0;
    }
}
