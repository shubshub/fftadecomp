#include "ffta.h"

// Complete [0x08018790, 0x080189A0): 528 bytes, including the jump table
// and literal pools.

typedef struct {
    u8 unknown_00[0x14];
    u32 data;
} Resource;

typedef struct {
    u8 unknown_00[0x1C];
    u8 flags;
    u8 unknown_1D[0x0F];
} WindowState;

typedef struct {
    Resource *first;
    Resource *second;
    u8 phase;
    u8 width;
    u8 x;
    u8 y;
    u16 tile;
    u8 flags;
    u8 handle;
    u8 height;
    u8 unknown_11[3];
    WindowState window;
    u8 context[0x10];
    u8 buffer[0x280];
    void *unknown_2D0;
    u8 *graphics;
    u8 text[0x100];
} PanelContext;

extern PanelContext *data_02009190;
extern u8 func_08013AAC(u8 width, u16 flags);
extern void func_08017424(WindowState *state, u32 first, u32 second,
                          u8 x, u8 y, u8 width, u8 height, u16 flags,
                          u8 value_16, u16 value_18, u16 value_1A,
                          u8 value_17);
extern void func_08016E1C(WindowState *state, u8 first, u8 second);
extern void func_08016E4C(WindowState *state, u8 *destination, u8 first);
extern void func_08016C90(WindowState *state, u8 mode);
extern u8 func_080098F4(u8 (*callback)(void), void *context);
extern u8 func_080099A4(u8 handle);
extern void func_080161D4(void *source, void *destination, void *buffer,
                          u8 rows, u8 width, u8 height, u8 mode);
extern void func_08017508(WindowState *window, u8 value);
extern u8 func_08018A24(void);
extern u8 func_080189A0(void);
extern u8 func_08018A90(void);
extern u8 func_08018A0C(void);

u8 func_08018790(void)
{
    WindowState *window;
    u16 flags;
    u8 width;
    u8 height;

    if (data_02009190 == 0)
        return 1;

    switch (data_02009190->phase) {
    case 0:
        break;
    case 1:
        window = &data_02009190->window;
        if (data_02009190->flags & 2)
            flags = 0x800;
        else
            flags = 0x404;
        width = func_08013AAC(data_02009190->width, flags);
        if (data_02009190->flags & 2)
            height = data_02009190->height * 2 + 2;
        else
            height = 2;
        func_08017424(window, data_02009190->first->data,
                      data_02009190->second->data, data_02009190->x,
                      data_02009190->y, width, height, flags, 0x20, 0xD, 3,
                      0xB);
        window->flags |= 1;
        if (data_02009190->flags & 2) {
            func_08016E1C(window, 2, 0);
            func_08016E4C(window, data_02009190->buffer, 1);
        }
        func_08016C90(window, 0x10);
        if (data_02009190->flags & 2)
            data_02009190->handle = func_080098F4(func_08018A24, 0);
        else
            data_02009190->handle = func_080098F4(func_080189A0, 0);
        data_02009190->phase = 2;
        break;
    case 5:
        data_02009190 = 0;
        return 1;
    case 2:
        if (func_080099A4(data_02009190->handle)) {
            if (data_02009190->flags & 2)
                func_080161D4(data_02009190->context, data_02009190->graphics,
                              data_02009190->text, data_02009190->width,
                              data_02009190->x, data_02009190->y, 0);
            data_02009190->phase = 3;
        }
        return 1;
    case 4:
        if (func_080099A4(data_02009190->handle))
            data_02009190->phase = 5;
        break;
    case 3:
        if (data_02009190->flags & 1) {
            func_08017508(&data_02009190->window, 0x10);
            if (data_02009190->flags & 2)
                data_02009190->handle = func_080098F4(func_08018A90, 0);
            else
                data_02009190->handle = func_080098F4(func_08018A0C, 0);
            data_02009190->phase = 4;
        }
        break;
    }
    return 0;
}
