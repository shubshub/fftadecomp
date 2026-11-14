#include "ffta.h"

// 0x08011860: complete [0x08011860, 0x08011B30), 720 bytes, 291 instructions.
// Steps the window object through its open, wait, input and close phases.

typedef struct {
    u8 unknown_00[8];
    u8 state;
    u8 next_state;
    u8 unknown_0a[2];
    u16 flags;
    u8 unknown_0e[0x0d];
    u8 timer;
    u8 unknown_1c[4];
    u16 confirm_keys;
    u16 cancel_keys;
    u8 unknown_24[2];
    u8 busy;
    u8 message;
    u8 unknown_28;
    u8 count;
    u8 cursor;
    u8 mark_closed;
    u8 unknown_2c[0x0e];
    u16 options;
    u8 unknown_3c[5];
    u8 choice;
    u8 locked;
    u8 unknown_43[0x709];
    void (*on_open)(void);
    void (*on_close)(void);
} Window08011860;

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} Input08011860;

typedef struct {
    u8 unknown_00[0xb6];
    u8 confirm_sound;
} Sound08011860;

extern Window08011860 *data_0200918C;
extern Input08011860 data_03000000;
extern Sound08011860 g_state_020020D0;
extern void func_08011D9C(void);
extern void func_08011EBC(void);
extern u8 func_080099A4(u8 message);
extern void func_08012A98(void);
extern void func_08012BEC(void);
extern void func_08012C30(void);
extern void func_08012FD8(void);
extern void func_08013060(void);
extern void func_08141540(u32 sound);
extern void func_080C95C0(u16 index, u32 value);

u32 func_08011860(void)
{
    u16 keys;
    u16 pressed;

    if (data_0200918C == 0)
        return 1;
    switch (data_0200918C->state) {
    case 0:
        func_08011D9C();
        if (data_0200918C->on_open)
            data_0200918C->on_open();
        if (data_0200918C->flags & 0x1000)
            data_0200918C->state = 4;
        else
            data_0200918C->state = 1;
        break;
    case 11:
        data_0200918C->options &= 0xfeff;
        data_0200918C = 0;
        return 1;
    case 8:
        if (data_0200918C->busy == 0) {
            data_0200918C->state = data_0200918C->next_state;
            break;
        }
        return 2;
    case 1:
        func_08011EBC();
        data_0200918C->state = 2;
        break;
    case 2:
        if (!func_080099A4(data_0200918C->message))
            break;
        if (data_0200918C->mark_closed)
            data_0200918C->options |= 0x100;
        data_0200918C->state = 4;
        break;
    case 3:
        if (!(data_0200918C->flags & 0x1000) &&
            !func_080099A4(data_0200918C->message))
            break;
        if (data_0200918C->on_close)
            data_0200918C->on_close();
        data_0200918C->state = 11;
        break;
    case 4:
        func_08012A98();
        data_0200918C->state = 5;
        break;
    case 5:
        func_08012BEC();
        break;
    case 6:
        if (data_0200918C->timer) {
            data_0200918C->timer--;
            if (data_0200918C->timer)
                goto update;
        }
        pressed = data_03000000.pressed;
        if ((keys = data_0200918C->confirm_keys & pressed)) {
            if (keys & 4)
                g_state_020020D0.confirm_sound = 1;
            if (data_0200918C->cursor + 1 >= data_0200918C->count &&
                (keys & 0xf0))
                goto update;
            if (data_0200918C->options & 0x40)
                func_08141540(0x64);
            data_0200918C->state = data_0200918C->next_state;
        } else if ((keys = data_0200918C->cancel_keys & pressed)) {
            if (data_0200918C->cursor == 0 && (keys & 0xf0))
                goto update;
            func_08141540(0x69);
            data_0200918C->state = 10;
        }
    update:
        func_08012FD8();
        break;
    case 7:
        if (data_03000000.pressed & data_0200918C->confirm_keys)
            data_0200918C->timer = 0;
        if (data_0200918C->timer) {
            data_0200918C->timer--;
            break;
        }
        data_0200918C->state = data_0200918C->next_state;
        break;
    case 9:
        if (data_0200918C->timer) {
            data_0200918C->timer--;
            if (data_0200918C->timer)
                goto choose;
        }
        if (data_03000000.pressed & 1) {
            func_08141540(0x64);
            data_0200918C->state = data_0200918C->next_state;
            func_080C95C0(0x13, data_0200918C->choice);
        } else if (data_03000000.pressed & 2) {
            func_08141540(0x69);
            data_0200918C->choice = 0xff;
            data_0200918C->state = data_0200918C->next_state;
            func_080C95C0(0x13, data_0200918C->choice);
            break;
        } else if (data_03000000.repeated & 0x30) {
            if (!data_0200918C->locked) {
                func_08141540(0x6d);
                data_0200918C->choice ^= 1;
            }
        } else if (data_03000000.repeated & 0xc0) {
            if (data_0200918C->locked) {
                func_08141540(0x6d);
                data_0200918C->choice ^= 1;
            }
        }
    choose:
        func_08013060();
        break;
    case 10:
        func_08012C30();
        data_0200918C->state = 5;
        break;
    }
    return 0;
}
