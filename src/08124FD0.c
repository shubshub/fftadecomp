#include "ffta.h"

/* Complete [0x08124FD0, 0x081253CC): 1020 bytes, 422 instructions plus
 * literal pools and the six-entry jump table at 0x0812502C. */

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
    u8 unknown_2A[0xDE];
} SceneRecord08124FD0;

typedef struct {
    SceneRecord08124FD0 *record;
} SceneObject08124FD0;

typedef struct {
    u8 kind;
    u8 selectors[3];
} Cue08124FD0;

typedef void (*BufferInitializer08124FD0)(void *destination, u32 size);

extern SceneRecord08124FD0 g_state_02000080[24];
extern const Cue08124FD0 data_083A8194[];
extern BufferInitializer08124FD0 const g_callbacks_0836D4B8[];
extern SceneObject08124FD0 **func_08121DF8(void);
extern SceneRecord08124FD0 *func_08121CB4(u8 selector);
extern SceneRecord08124FD0 *func_080C83CC(u8 category);
extern void *func_08096D7C(void);
extern SceneObject08124FD0 *func_08099560(void *manager,
                                       SceneRecord08124FD0 *record);
extern s32 func_08099CDC(void *context, SceneObject08124FD0 **objects);
extern u8 func_080C8240(SceneRecord08124FD0 *record);
extern u8 func_080C8260(SceneRecord08124FD0 *record);
extern u8 func_080C8298(SceneRecord08124FD0 *record);
extern void *func_08121B64(u32 size);
extern void func_08121B78(void *object);
extern void *func_08121DE4(void);
extern void *func_080D3818(u16 id, void *first, void *second);
extern void func_08121DA8(void *task);

/* The selector lookup of src/08125444.c and src/08125624.c, same text. */
static inline SceneRecord08124FD0 *resolve_record(u8 selector)
{
    SceneRecord08124FD0 *record;
    s32 index;

    if (selector == 255) {
        record = g_state_02000080;
        for (index = 0; index < 24; index++, record++) {
            if (record->flags & 0x400)
                return record;
        }
        return 0;
    } else if ((s8)selector < 0) {
        return func_08121CB4(selector);
    } else {
        return func_080C83CC(selector);
    }
}

void func_08124FD0(u16 index)
{
    void *task = 0;
    const Cue08124FD0 *cue = &data_083A8194[index];
    SceneObject08124FD0 **objects = func_08121DF8();
    SceneObject08124FD0 **list;
    SceneRecord08124FD0 *record;
    s32 count;
    s32 total;
    s32 i;

    g_callbacks_0836D4B8[0](objects, 0x34);
    index += 0x16B;
    switch (cue->kind) {
    case 0:
        task = func_080D3818(index, 0, 0);
        break;
    case 1:
        if (cue->selectors[0]) {
            record = resolve_record(cue->selectors[0]);
            objects[0] = func_08099560(func_08096D7C(), record);
        }
        if (cue->selectors[1]) {
            record = resolve_record(cue->selectors[1]);
            objects[1] = func_08099560(func_08096D7C(), record);
        }
        task = func_080D3818(index, objects[0], objects[1]);
        break;
    case 2:
        /* count is 0 at the first store and still indexes it: movs r6,#0
         * (0x08125114, 0x08125156), adds r1,r6,r2 (0x08125166). */
        count = 0;
        record = resolve_record(cue->selectors[0]);
        objects[count++] = func_08099560(func_08096D7C(), record);
        list = func_08121B64(0x34);
        g_callbacks_0836D4B8[0](list, 0x34);
        total = func_08099CDC(func_08096D7C(), list);
        for (i = 0; i < total; i++) {
            if (list[i] == 0 || list[i] == objects[0])
                continue;
            record = list[i]->record;
            if (func_080C8240(record) && !func_080C8260(record) &&
                !func_080C8298(record))
                objects[count++] = list[i];
        }
        task = func_080D3818(index, objects, (void *)count);
        func_08121B78(list);
        break;
    case 3:
        /* Each arm stores objects[0]: the ROM has one copy of that call and
         * store (0x0812528E-0x0812529A), reached from both selector paths,
         * and reloads objects[0] after it (0x0812529C-0x0812529E). */
        record = resolve_record(cue->selectors[0]);
        if (record != 0) {
            objects[0] = func_08099560(func_08096D7C(), record);
        } else {
            record = resolve_record(cue->selectors[1]);
            objects[0] = func_08099560(func_08096D7C(), record);
        }
        task = func_080D3818(index, objects[0], 0);
        break;
    case 4:
        record = resolve_record(cue->selectors[0]);
        objects[0] = func_08099560(func_08096D7C(), record);
        record = resolve_record(cue->selectors[1]);
        objects[1] = func_08099560(func_08096D7C(), record);
        record = resolve_record(cue->selectors[2]);
        objects[2] = func_08099560(func_08096D7C(), record);
        task = func_080D3818(index, objects, (void *)3);
        break;
    case 5:
        task = func_080D3818(index, func_08121DE4(), 0);
        break;
    }
    func_08121DA8(task);
}
