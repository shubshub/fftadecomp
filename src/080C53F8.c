#include "ffta.h"

typedef struct Workspace080C53F8 Workspace080C53F8;

typedef struct Object080C53F8 {
    void *owner;
    void *context;
    void *resource;
    void *user_data;
    u16 width;
    u16 height;
    Workspace080C53F8 *workspace;
    u8 unknown_18[0x50];
} Object080C53F8;

typedef void (*ObjectInitializer080C53F8)(void *destination, u32 size);

extern ObjectInitializer080C53F8 const g_callbacks_0836D4B8[];
extern void func_080BDB18(void *context);
extern void func_08022854(u8 *object);

/* Target [0x080C53F8, 0x080C5420), 40 bytes:
 * 10b5041c6069f8f78bfb06480268201c68217cf01fff201c5df720fa10bc01bc0047
 * 0000b8d43608
 */
void func_080C53F8(Object080C53F8 *object)
{
    func_080BDB18(object->workspace);
    g_callbacks_0836D4B8[0](object, sizeof(*object));
    func_08022854((u8 *)object);
}
