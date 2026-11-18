#include "ffta.h"
#include "control_flags.h"

// Target [0x0813DC3C, 0x0813DD58), 284 bytes:
// 30b582b009060d0e6c466946042203f00ffe684602880023c15eef293cdc608800040014
// 9f2837dc00290bdaa1885018a080011c0004002800da0021a18069460020088068460023
// c05e6a460423d15e4018f02804dd68460188ef20401a90805188080400280adad388c818
// d080011c0004002800da0021d180002050806a460221505e0623d15e4018a0280add5188
// 9f20401ad08005e068460021c180818041800180002d19d10b4884466846008862463b32
// 117810706a461179401863463a331978187051880533187819709279891860463e3019e0
// 400900030e4b9c466846018862463d32107811706a461079091860463c30037801705188
// 634641331878197092798918604640300278017002b030bc01bc004740090003

typedef struct {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
} WindowRect;

extern void func_0814186C(const void *source, void *destination, u32 control);

void func_0813DC3C(const WindowRect *source, u8 channel)
{
    WindowRect rect;

    func_0814186C(source, &rect, 4);
    if (rect.x < 240 && rect.y < 160) {
        if (rect.x < 0) {
            rect.width += rect.x;
            rect.width = rect.width < 0 ? 0 : rect.width;
            rect.x = 0;
        }
        if (rect.x + rect.width > 240)
            rect.width = 239 - rect.x;
        if (rect.y < 0) {
            rect.height += rect.y;
            rect.height = rect.height < 0 ? 0 : rect.height;
            rect.y = 0;
        }
        if (rect.y + rect.height > 160)
            rect.height = 159 - rect.y;
    } else {
        rect.x = rect.y = rect.width = rect.height = 0;
    }
    if (channel == 0) {
        g_control_flags_03000940.win0h_hi = rect.x;
        g_control_flags_03000940.win0h_lo = rect.x + rect.width;
        g_control_flags_03000940.win0v_hi = rect.y;
        g_control_flags_03000940.win0v_lo = rect.y + rect.height;
    } else {
        g_control_flags_03000940.win1h_hi = rect.x;
        g_control_flags_03000940.win1h_lo = rect.x + rect.width;
        g_control_flags_03000940.win1v_hi = rect.y;
        g_control_flags_03000940.win1v_lo = rect.y + rect.height;
    }
}
