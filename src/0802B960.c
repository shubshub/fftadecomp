#include "ffta.h"

typedef struct ListOwner08021B1C ListOwner08021B1C;
typedef struct ListObject08021B1C ListObject08021B1C;

typedef struct {
    u8 unknown_00[8];
    void *field_08;
} Object08099C30;

typedef struct {
    u8 *storage;
    u8 *allocator;
    ListOwner08021B1C *owner;
    void *instance;
    ListObject08021B1C *resource;
    u8 palette_index;
} DisplayRecord0802B960;

typedef struct {
    u8 unknown_000[0x394];
    DisplayRecord0802B960 display;
    u8 unknown_3AC[0x1C50];
    u8 setup[0x80];
} State0802B960;

extern State0802B960 *data_0200F440;
extern void func_0802C72C(void *destination, u16 value, u8 mode);
extern u32 func_08022080(u32 count);
extern void *func_08022840(u32 size);
extern u8 *func_080070C8(u8 *storage, u32 size);
extern void *func_08096D7C(void);
extern void *func_08099C30(const Object08099C30 *object);
extern ListObject08021B1C *func_08021B1C(ListOwner08021B1C *parent);

/* 0802B960..0802B9B4: 84 bytes, including the state-pointer and setup-offset literals. */
void func_0802B960(void)
{
    DisplayRecord0802B960 *display;
    u32 size;

    func_0802C72C(data_0200F440->setup, 0x120, 1);
    display = &data_0200F440->display;
    size = func_08022080(1);
    display->storage = func_08022840(size);
    display->allocator = func_080070C8(display->storage, size);
    display->owner = func_08099C30(func_08096D7C());
    display->resource = func_08021B1C(display->owner);
    display->palette_index = 0;
}
