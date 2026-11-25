#include "ffta.h"

typedef struct Unit Unit;
typedef struct ListOwner ListOwner;
typedef struct ListObject ListObject;

typedef struct {
    u8 unknown_00[8];
    Unit *unit;
    u8 unknown_0C[0x3A5 - 0x0C];
    u8 mode;
} PanelState;

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
} TaskRequest;

typedef struct {
    u8 unknown_00[0x1C];
} Transfer;

/* The 0x98-byte payload src/081295C8.c creates for this task (its
 * PortraitTask).  The image is what func_080CB928 returns, drawn with tile
 * base 0x240 as src/0812A52C.c draws it. */
typedef struct {
    PanelState *panel;
    Unit *unit;
    u8 variant;
    u8 remaining;
    u16 chunk_size;
    u16 value;
    u16 pose;
    const u8 *image;
    Transfer transfers[4];
    u8 *heap;
    ListOwner *owner;
    void *instance;
    ListObject *resource;
    u8 *storage;
} PortraitTask;

typedef void (*CopyFunction)(void *destination, const void *source, u32 size);

extern u8 data_02005070[];
extern u8 data_03003B20[];
extern CopyFunction data_0836D4BC[];
extern const u8 data_08391576[];

/* The size word that func_080CB808 returns from func_0800588C. */
extern u32 func_080CB808(Unit *unit);
extern const u8 *func_080CB928(Unit *unit);
extern u8 *func_080CB868(u8 *buffer, Unit *unit);
extern u8 func_080CB7C0(Unit *unit, u8 selector);
extern void func_080CB8D4(void *object, u8 index);
extern u32 func_08022080(u32 count);
extern u8 *func_08121B64(u32 size);
extern void func_08121B78(u8 *storage);
extern u8 *func_080070C8(u8 *storage, u32 byte_count);
extern void func_0800718C(u8 *heap);
extern ListOwner *func_08021A3C(void *allocator, u16 first, u16 second,
                                u16 third, u16 fourth);
extern void *func_08021AD0(ListOwner *owner);
extern ListObject *func_08021B1C(ListOwner *owner);
extern void func_08021B54(ListObject *resource);
extern void func_08000ADC(Transfer *entry, const void *source,
                          void *destination, u16 words);
extern u16 func_08022238(Unit *unit, u8 *output);
extern void *func_08021618(ListObject *resource, void *instance, u32 x, u32 y,
                           u32 value, u32 first, u32 second);
extern void func_08021E28(void *instance, u32 value);
extern void func_08021DF8(ListObject *resource, u16 clear, u16 set);
extern void func_08021E7C(ListOwner *owner);
extern void func_08021E64(void *instance, u8 value);
extern void func_08021F18(ListObject *resource, s32 x, s32 y, u8, u8, u8, u8,
                          u8, u8, u8);
extern void func_08001F34(const void *source, s32 x, s32 y, u8 variant,
                          u8 flip_x, u8 flip_y, u8 flag_28, u8 flag_29,
                          u32 value, u8 mode, const void *transform);
extern void func_08001CF0(const void *source, s32 x, s32 y, u8 mode,
                          u8 first_flag, u8 second_flag, u8 third_flag,
                          u8 fourth_flag, u32 value, u8 count, u32 extra);

/* The storage, heap, owner and resource sequence of src/0802B960.c, whose
 * teardown is src/0802B9B4.c, with literal arguments to func_08021A3C as in
 * src/0802995C.c.  The ROM stores the zero fifth argument at 0x08129E94,
 * before it loads 0x2C0 and 0x2E0 into r1/r2, as the call compiles inside
 * this helper; written straight into case 0x101, the call loads them first,
 * as at 0x080299B4 in src/0802995C.c. */
static inline void create_sprite(PortraitTask *portrait)
{
    u16 size = func_08022080(1);

    portrait->storage = func_08121B64(size);
    portrait->heap = func_080070C8(portrait->storage, size);
    portrait->owner = func_08021A3C(portrait->heap, 0x2C0, 0x2E0, 0, 0);
    portrait->resource = func_08021B1C(portrait->owner);
}

/* The ROM has this block twice, at 0x08129DD0 and at 0x0812A00E. */
static inline void destroy_sprite(PortraitTask *portrait)
{
    if (portrait->storage)
    {
        func_08021B54(portrait->resource);
        func_08021AD0(portrait->owner);
        func_0800718C(portrait->heap);
        func_08121B78(portrait->storage);
        portrait->storage = 0;
    }
}

/* Each draw loads 0x3A5 again for its panel-mode test (0x08129F6A,
 * 0x08129FCC), and the image call at 0x08129FDC reuses the zero register r4
 * of the first draw, as the two compile inside inlined helpers.  Written
 * straight into case 0x103, the tests share one 0x3A5 register and the
 * function is 716 bytes. */
static inline void draw_sprite(PortraitTask *portrait)
{
    if (portrait->panel->mode == 3)
    {
        func_08021E7C(portrait->owner);
        func_08021E64(portrait->instance, portrait->variant);
        func_08021F18(portrait->resource, 72, 88, 0, 0, 0, 0, 0, 0, 0);
        if (portrait->pose == 8)
            func_08001F34(data_08391576, 72, 88, 0, 0, 0, 1, 0, 0, 0, 0);
    }
}

static inline void draw_image(PortraitTask *portrait)
{
    if (portrait->panel->mode == 3 && portrait->image)
        func_08001CF0(portrait->image, 200, 142, 0, 0, 1, 0, 0, 0x240, 1, 0);
}

/* Complete [0x08129D90, 0x0812A060): 720 bytes, 308 instructions. */
u32 func_08129D90(void *task, TaskRequest *request, PortraitTask *portrait)
{
    switch (request->phase)
    {
    case 1:
        destroy_sprite(portrait);
        break;

    case 0:
        portrait->panel = request->object;
        portrait->unit = 0;
        break;

    case 0x100:
        if (portrait->panel->mode == 2)
        {
            portrait->unit = portrait->panel->unit;
            request->phase = 0x101;
        }
        break;

    case 0x101:
        portrait->chunk_size = func_080CB808(portrait->unit) >> 2;
        portrait->remaining = 4;
        portrait->image = func_080CB928(portrait->unit);
        func_080CB868(data_02005070, portrait->unit);
        func_080CB8D4(data_02005070 + 0x1000, func_080CB7C0(portrait->unit, 1));
        create_sprite(portrait);
        request->phase = 0x102;
        break;

    case 0x102:
        if (portrait->remaining)
        {
            u16 offset = (4 - portrait->remaining) * portrait->chunk_size;

            /* 0x06014800 is OBJ tile 0x240, the tile base of draw_image. */
            func_08000ADC(&portrait->transfers[portrait->remaining - 1],
                          data_02005070 + offset,
                          (u8 *)0x06014800 + offset,
                          portrait->chunk_size >> 2);
            if (portrait->remaining == 4)
                data_0836D4BC[0](data_03003B20, data_02005070 + 0x1000, 0x60);
            portrait->remaining--;
        }
        else
        {
            portrait->value = func_08022238(portrait->unit, &portrait->variant);
            portrait->pose = 0;
            portrait->instance = func_08021618(portrait->resource, 0, 0, 20,
                                               portrait->value,
                                               portrait->pose + 3, 0);
            func_08021E28(portrait->instance, 1);
            func_08021DF8(portrait->resource, 2, 0x100);
            request->phase = 0x103;
        }
        break;

    case 0x103:
        draw_sprite(portrait);
        draw_image(portrait);
        if (portrait->panel->mode == 1)
        {
            portrait->panel->unit = 0;
            portrait->unit = 0;
            destroy_sprite(portrait);
            request->phase = 0x100;
        }
        break;
    }
    return 0;
}
