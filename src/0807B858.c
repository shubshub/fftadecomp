#include "ffta.h"

// Complete 0x0807B858..0x0807B928: 208 bytes, 87 instructions.
typedef struct {
    u8 unknown_00[4];
    u8 unknown_04;
    u8 unknown_05;
    u8 unknown_06[0x46];
} Window0807B858;

extern Window0807B858 data_030009E0[];
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_0808A604(u32 object, u32 command);

void func_0807B858(void)
{
    {
        u16 zero;
        u16 *p = &zero;
        *p = 0;
        func_0814186C(p, func_0808B8E4(0, 1, 6, 9), 0x01000001);
    }
    {
        u16 zero;
        u16 *p = &zero;
        *p = 0;
        func_0814186C(p, func_0808B8E4(0, 1, 6, 10), 0x01000001);
    }
    {
        u16 zero;
        u16 *p = &zero;
        *p = 0;
        func_0814186C(p, func_0808B8E4(0, 1, 11, 14), 0x01000003);
    }
    {
        u16 zero;
        u16 *p = &zero;
        *p = 0;
        func_0814186C(p, func_0808B8E4(0, 1, 11, 15), 0x01000003);
    }
    {
        u16 zero;
        u16 *p = &zero;
        *p = 0;
        func_0814186C(p, func_0808B8E4(0, 1, 11, 17), 0x01000003);
    }
    {
        u16 zero;
        u16 *p = &zero;
        *p = 0;
        func_0814186C(p, func_0808B8E4(0, 1, 11, 18), 0x01000003);
    }
    data_030009E0[3].unknown_04 = 0;
    data_030009E0[3].unknown_05 = 0;
    func_0808A604(3, 4);
}
