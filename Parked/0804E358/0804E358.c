#include "ffta.h"

/* 0x0804E358..0x0804E3BA: 98 bytes. */
typedef struct {
    u16 first;
    u16 length;
} ListWindow;

typedef struct {
    u8 unknown_00[0x53C];
    ListWindow windows[5];
} ListState;

extern ListState *data_0201F548;
extern u8 func_08050E74(void);
extern u8 func_08050E84(void);

void func_0804E358(u8 index)
{
    ListWindow *window = &data_0201F548->windows[index];
    u8 count;
    u8 visible;

    func_08050E74();
    if (index == 4)
        count = func_08050E74();
    else
        count = func_08050E84();
    visible = 6;
    if (window->first + visible > count) {
        if ((u8)(window->length + window->first) >= count && count < visible)
            window->length--;
        if (window->first)
            window->first--;
    }
}
