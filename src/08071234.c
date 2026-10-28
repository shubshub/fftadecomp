#include "ffta.h"

typedef struct {
    void *arena;
    u8 unknown_04[4];
    void *object;
    u8 unknown_0C[0x10];
    void *first_buffer;
    void *second_buffer;
} ResourceOwner;

typedef struct {
    u8 unknown_00[4];
    void *buffer;
} SharedResource;

extern ResourceOwner *data_03002818;
extern SharedResource data_03000E30;
extern void *data_03000E98;
extern void func_0800718C(void *object);
extern void func_08007170(void *arena, void *object);

/* Complete target: [0x08071234, 0x080712D0), 156 bytes, 53 instructions.
 * Both native mode paths release the same resource set.
 */
void func_08071234(u32 mode)
{
    if (mode == 0) {
        func_0800718C(data_03002818->object);
        func_08007170(data_03002818->arena, data_03002818->first_buffer);
        func_08007170(data_03002818->arena, data_03000E30.buffer);
        func_08007170(data_03002818->arena, data_03002818->second_buffer);
        func_08007170(data_03002818->arena, data_03002818);
        func_0800718C(data_03000E98);
    } else {
        func_0800718C(data_03002818->object);
        func_08007170(data_03002818->arena, data_03002818->first_buffer);
        func_08007170(data_03002818->arena, data_03000E30.buffer);
        func_08007170(data_03002818->arena, data_03002818->second_buffer);
        func_08007170(data_03002818->arena, data_03002818);
        func_0800718C(data_03000E98);
    }
}
