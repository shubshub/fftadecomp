#include "ffta.h"

typedef struct {
    u8 unknown_00[0x30];
    u32 flags_30;
} Struct080DE278;

extern void *func_080DD350(void *object);
extern void func_0809A2D8(void *object, u16 action, s8 value);
extern void func_0809836C(void *object, u16 action, s8 value, u16 option);
extern void func_0809A570(void *object, u32 clear, u32 set);
extern void func_0809A530(void *object, u32 value);

static inline void dispatch_object_action(void *object, u16 action, s8 value)
{
    func_0809A2D8(func_080DD350(object), action, value);
}

/* 0x080DE278 - 88 bytes.
 * Target: 30b5051c0906090e0a1c2b6b1020184000281ed108200340002b09d00c062416281c
 *         fff759f80c21221cbcf719f810e012061216281c01210023baf75bf880225200281c
 *         0021bcf757f9281c0121bcf733f930bc01bc0047
 */
void func_080DE278(Struct080DE278 *object, s8 value)
{
    if (object->flags_30 & 0x10)
        return;
    if (object->flags_30 & 0x08) {
        dispatch_object_action(object, 12, value);
    } else {
        func_0809836C(object, 1, value, 0);
        func_0809A570(object, 0, 0x100);
        func_0809A530(object, 1);
    }
}
