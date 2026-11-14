// func_0808B288: [0x0808B288, 0x0808B4FC), 628 bytes
// Steps the open/close animation of each of the fourteen tile windows.
#include "ffta.h"

typedef struct {
    u8 state;
    u8 unknown_01[3];
    u8 height;
    u8 step;
    u8 width;
    u8 unknown_07[0x19];
    void *contents;
    u8 unknown_24[0x14];
    s8 max_width;
    s8 max_height;
    u8 unknown_3a[0x12];
} Window0808B288;

extern Window0808B288 data_030009E0[];
extern void func_0808A830(int index);
extern void func_0808A8C0(int index);
extern void func_0808A948(int index);
extern void func_0808AAF0(int index);
extern void func_0808AC34(int index);
extern void func_0808ADD4(int index, int height, int width);
extern void func_0808B0F0(int index, int height, int width);

void func_0808B288(int unused, u8 *initialized)
{
    Window0808B288 *window;
    int height;
    int width;
    int i;

    if (*initialized == 0) {
        for (i = 13; i >= 0; i--)
            data_030009E0[i].state = 0;
        *initialized = 1;
    }

    for (i = 0; i < 14; i++) {
        switch (data_030009E0[i].state) {
        case 0:
            break;
        case 2:
            func_0808AC34(i);
            data_030009E0[i].state = 0;
            break;
        case 3:
            func_0808A8C0(i);
            func_0808AC34(i);
            data_030009E0[i].state = 0;
            break;
        case 4:
            func_0808A830(i);
            data_030009E0[i].state = 0;
            break;
        case 5:
            func_0808A8C0(i);
            data_030009E0[i].state = 0;
            break;
        case 6:
            func_0808A948(i);
            func_0808AC34(i);
            data_030009E0[i].state = 0;
            break;
        case 7:
            func_0808AAF0(i);
            func_0808A948(i);
            func_0808AC34(i);
            data_030009E0[i].state = 0;
            break;
        case 8:
            func_0808AAF0(i);
            func_0808AC34(i);
            data_030009E0[i].state = 0;
            break;
        case 9:
            func_0808A948(i);
            data_030009E0[i].state = 0;
            break;
        case 1:
        case 10:
            func_0808AAF0(i);
            data_030009E0[i].state = 0;
            break;
        case 11:
            func_0808ADD4(i, data_030009E0[i].height, data_030009E0[i].width);
            if (data_030009E0[i].width >= data_030009E0[i].max_width
                && data_030009E0[i].height >= data_030009E0[i].max_height) {
                data_030009E0[i].state = 0;
                break;
            }
            data_030009E0[i].width += 4;
            if (data_030009E0[i].width >= data_030009E0[i].max_width)
                data_030009E0[i].width = data_030009E0[i].max_width;
            data_030009E0[i].height += data_030009E0[i].step;
            if (data_030009E0[i].height >= data_030009E0[i].max_height)
                data_030009E0[i].height = data_030009E0[i].max_height;
            break;
        case 12:
            window = &data_030009E0[i];
            func_0808B0F0(i, window->height, window->width);
            if (window->width >= window->max_width
                || window->height >= window->max_height - 2) {
                window->state = 1;
                break;
            }
            window->width += 4;
            if (window->width >= window->max_width)
                window->width = window->max_width;
            window->height += window->step;
            if (window->height >= window->max_height - 2)
                window->height = window->max_height - 2;
            break;
        case 13:
            window = &data_030009E0[i];
            height = window->height;
            width = window->width;
            if (data_030009E0[i].contents == 0)
                func_0808B0F0(i, height, width);
            func_0808AAF0(i);
            func_0808ADD4(i, window->max_height - height,
                window->max_width - width + 2);
            if (window->width >= window->max_width
                || window->height >= window->max_height - 2) {
                window->state = 10;
                break;
            }
            window->width += 4;
            if (window->width >= window->max_width)
                window->width = window->max_width;
            window->height += window->step;
            if (window->height >= window->max_height - 2)
                window->height = window->max_height - 2;
            break;
        }
    }
}
