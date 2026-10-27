#include "ffta.h"

typedef struct Workspace080C5398 Workspace080C5398;

typedef struct Object080C5398 {
    void *owner;
    void *context;
    void *resource;
    void *user_data;
    u16 width;
    u16 height;
    Workspace080C5398 *workspace;
    u8 unknown_18[0x50];
} Object080C5398;

typedef void (*ObjectInitializer080C5398)(void *destination, u32 size);

extern ObjectInitializer080C5398 const g_callbacks_0836D4B8[];
extern void *func_08022840(u32 size);
extern Workspace080C5398 *func_080BDAFC(void);

/* Complete [0x080C5398, 0x080C53F8): 96 bytes, 42 instructions. */
Object080C5398 *func_080C5398(void *owner, void *context, void *resource,
                           u16 width, void *user_data, u16 height)
{
    Object080C5398 *object = func_08022840(sizeof(*object));

    g_callbacks_0836D4B8[0](object, sizeof(*object));
    object->owner = owner;
    object->context = context;
    object->resource = resource;
    object->user_data = user_data;
    object->width = width;
    object->height = height;
    object->workspace = func_080BDAFC();
    return object;
}
