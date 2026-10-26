#include "ffta.h"

struct Object081336B8 {
    u8 unknown_00[8];
    void *data;
    u8 unknown_0c[0x1a];
    u16 flags;
};

extern u8 func_080CD8FC(const void *object);
extern void func_080CDD88(void *object, u8 enabled);
extern void func_081321B4(struct Object081336B8 *object);
extern void func_08132160(struct Object081336B8 *object);
extern void func_080CE470(void *object, u8 mode);
extern void func_080CE478(void *object, u8 mode);

/* Target: [0x081336B8, 0x08133722), 106 bytes, 47 instructions. */
void func_081336B8(struct Object081336B8 *object)
{
    if (object->flags & 0x10)
        return;
    if (func_080CD8FC(object->data)) {
        func_080CDD88(object->data, 0);
        object->flags |= 0x100;
    } else {
        func_081321B4(object);
        if (!(object->flags & 0x110))
            func_080CE470(object->data, 3);
        func_08132160(object);
        if (!(object->flags & 0x110))
            func_080CE478(object->data, 3);
    }
}
