#include "ffta.h"
#include "control_flags.h"

/* Complete [0x081204A8, 0x08120722): 634 bytes, 264 reachable instructions. */

typedef struct {
    u16 state;
    u16 unknown_02;
    void *output;
    u8 unknown_08[0xC];
    u16 category;
    u16 variant;
    u16 delay;
    u16 unknown_1a;
} ObjectScript;

typedef struct {
    u16 flags;
    u8 unknown_02[6];
    u8 index;
    u8 pending;
    u8 unknown_0a[2];
    void *sprite;
    void *objects[4];
    void *loader;
    void *children[4];
    void *group;
    void *fade;
    void *startup;
} Payload081204A8;

extern const u8 data_083A7498[];
extern const void *const data_083A7A20[];
extern const u8 data_083A7A0C[][4];
extern const u8 data_0894DF44[];
extern const u8 data_088F3D90[];

typedef u32 (*ObjectCallback)(void *, ObjectScript *, void *);
extern void *func_08005B6C(ObjectCallback callback, u16 size,
                           ObjectScript *script, void *parent);
extern u32 func_0811F95C(void *, ObjectScript *, void *);
extern u32 func_0811FFD8(void *, ObjectScript *, void *);
extern u32 func_08120398(void *, ObjectScript *, void *);
extern void *func_080D7A70(const void *data, u8 mode, void *parent);
extern void *func_080D7ABC(void *startup);
extern void func_080D45D0(const void *, u8, u8, u8, u8);
extern void func_080D5F74(void **objects, u16 count);
extern void *func_080E051C(void *task);
extern u8 func_080E0570(void **children, u16 count);
extern void *func_080D3E9C(const void *data, void *parent);
extern void *func_080D3F08(void *task);
extern void func_080D4A28(u8 first, u8 second, u16 third, s16 fourth, s16 fifth, u32 mode);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern void func_0800BD7C(void *sprite);
extern void func_0800BDF8(void *sprite, u16 value);
extern void func_080D4D14(void *sprite, u8 mode);
extern u16 func_080035A8(u8 layer);

u32 func_081204A8(void *parent, ObjectScript *script, Payload081204A8 *payload)
{
    ObjectScript loader;
    ObjectScript child;
    u8 i;

    if (payload->flags & 0x8000)
        return 0;

    switch (script->state) {
    case 0:
        payload->startup = func_080D7A70(data_083A7498, 9, parent);
        break;
    case 1:
        break;
    case 0x100:
        payload->startup = func_080D7ABC(payload->startup);
        if (payload->startup != 0)
            break;
        payload->flags |= 1;
        g_control_flags_03000940.winout_lo = 0x3F;
        g_control_flags_03000940.winout_hi = 0x2F;
        g_control_flags_03000940.display |= 0x8000;
        script->state++;
        break;
    case 0x101:
        loader.category = payload->index;
        loader.output = &payload->pending;
        payload->loader = func_08005B6C(func_0811F95C, 0x103C, &loader, parent);
        script->state++;
        break;
    case 0x102:
        if (payload->pending) {
            func_080D45D0(data_083A7A20[payload->index], 6, 1, 0, 1);
            func_080D5F74(payload->objects, 4);
            payload->pending = 0;
        }
        payload->loader = func_080E051C(payload->loader);
        if (payload->loader != 0)
            break;
        child.category = payload->index;
        payload->group = func_08005B6C(func_0811FFD8, 0x44, &child, parent);
        for (i = 0; i < 4; i++) {
            child.category = payload->index;
            child.variant = i;
            child.delay = data_083A7A0C[payload->index][i] + 0x50;
            child.output = &payload->objects[i];
            payload->children[i] = func_08005B6C(func_08120398, 0x18, &child, parent);
        }
        script->state++;
        break;
    case 0x103:
        payload->group = func_080E051C(payload->group);
        if (payload->group != 0)
            break;
        if (!func_080E0570(payload->children, 4))
            break;
        if (++payload->index <= 4) {
            script->state = 0x101;
            break;
        }
        g_control_flags_03000940.display &= 0x7FFF;
        payload->fade = func_080D3E9C(data_0894DF44, parent);
        script->state++;
        break;
    case 0x104:
        payload->fade = func_080D3F08(payload->fade);
        if (payload->fade != 0)
            break;
        func_080D5F74(payload->objects, 4);
        func_080D4A28(0, 2, 0, 0, 0, 1);
        payload->sprite = func_080D4B64(0, data_088F3D90, 0x19C, 8);
        func_0800BD7C(payload->sprite);
        func_0800BDF8(payload->sprite, 5);
        g_control_flags_03000940.display |= func_080035A8(2);
        script->state++;
        break;
    case 0x105:
        func_080D4D14(payload->sprite, 0);
        payload->sprite = 0;
        script->state = 2;
        break;
    }
    return 0;
}
