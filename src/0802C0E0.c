#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
} SourceObject;

typedef struct {
    u8 unknown_00[0xC];
    void *instance;
    void *resource;
    u8 palette_index;
    u8 unknown_15;
    u16 value;
    u16 colors[16];
} DisplayRecord;

typedef struct {
    u8 unknown_00[0x394];
    DisplayRecord display;
} DisplayContext;

typedef void (*BufferCopier)(void *destination, const void *source, u32 size);

extern DisplayContext *data_0200F440;
extern BufferCopier data_0836D4BC[];
extern u16 data_03003A60[][16];
extern u16 func_08022238(void *object, u8 *output);
extern const u8 *func_080CBA3C(u8 index);
extern void func_08148104(const u16 *source, u16 *destination, u16 count,
                         u16 adjustment);
extern void *func_08021618(void *resource, void *instance, s32 x, s32 y,
                          u16 value, u8 first, u8 second);
extern void func_08021DF8(void *object, u16 first, u16 second);

/* 0802C0E0..0802C168: 136 bytes. */
void func_0802C0E0(SourceObject *object)
{
    DisplayContext *context = data_0200F440;
    DisplayRecord *display = &context->display;

    display->value = func_08022238(object, &context->display.palette_index);
    if (object->flags & 1) {
        const u16 *source = (const u16 *)func_080CBA3C(display->palette_index);
        u16 *colors = context->display.colors;

        func_08148104(source, colors, 16, 153);
        display->palette_index = 9;
        data_0836D4BC[0](data_03003A60[display->palette_index], colors, 32);
    }
    display->instance = func_08021618(display->resource, display->instance,
                                     0, 20, display->value, 0, 0);
    func_08021DF8(display->resource, 0, 2);
}
