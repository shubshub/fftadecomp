#include "control_flags.h"
// Complete target [0x08114F1C, 0x081151A0), 644 bytes, 278 instructions:
// f0b54f464646c0b484b0071c8846151c098880204000814213d0814202dc0029
// 0cd025e181204000814200d1dee0814270db0130814200d100e119e10a202880
// 16e1288801380021894628800004040c002c00d00ce101200090281c0c300190
// 2748029003977820602100220123c1f785f828612348391cbef782ff68611821
// ff22bef7f1ff204800940194012103220023c2f737f90020002100223b1cc5f7
// e3fda861194e311c423108783f243f2008700320eef6fefa8443301c44300178
// 0470311c3b3108784a460a70013908780a70053108780a7001390878ff200870
// 308880239b01191c0843308008480097012104220023caf7bbfe28626ae00000
// d8383a0838dc9408cc468f084009000378393a080021324b2888021c041c1878
// 824209d0481c0006010e0c2904d8c800c01800788242f5d1601c002628800d29
// 00d195e02748e2302749018071200121052232f005fde8612149a87ac0004018
// 40886880a87ac00040188088a880a87ac000401840780138e880a87ac0004018
// 80882881a869c5f787fda869c5f7a8fea8690222a95e0423ea5e2b896c881b19
// 1b041b1400960196c5f77efda869ec8869886418210409140423ea5e2b891b19
// 1b041b14009601240194c5f76dfda869c4f754fd444620880130208048e00000
// f0383a0860380003187f0000288801302880e86933f0dcf9e861002838d1a87a
// 0130a8720006000e0c2805d80148414608802de0010100000320eef637fa054a
// 1188814304480140118042461088013010801de040090003ffdf00006869bef7
// d5fe6861002813d12869c0f7e5ff286100280dd1a869c4f7f7fc021caa61002a
// 06d107484a3001780270022043461880002004b018bc9846a146f0bc02bc0847
// 40090003

typedef struct {
    u8 key;
    u8 width;
    u16 x;
    u16 y;
    u16 unknown_06;
} WindowEntry;

typedef struct {
    u16 phase;
} Descriptor;

typedef struct {
    u16 delay;
    s16 x;
    s16 y;
    u16 width;
    u16 height;
    u8 index;
    u8 unknown_0B;
    u8 unknown_0C[4];
    void *particle;
    void *child;
    void *window;
    void *effect;
    void *other;
} Payload;

extern const u8 data_083A38D8[], data_0894DC38[], data_088F46CC[], data_083A3978[];
extern const WindowEntry data_083A38F0[];
extern struct { u8 unknown_00[0xE2]; u16 color; } data_03003860;
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080D6134(void *);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D3F08(void *);
extern void func_080D3F84(void *, int, int);
extern void func_080D7220(const void *, int, int, int, int, int);
extern void *func_080DAB84(int, s16, s16, void *);
extern u32 func_080035D0(int);
extern u32 func_080035A8(int);
extern void func_080DABB4(void *);
extern void func_080DABC4(void *, s16, s16, s16, s16, int);
extern void func_080D9B98(void *);
extern void func_080DADFC(void *);
extern void *func_08147A7C(int, int, int);
extern void *func_081484CC(void *);
extern void *func_080DFD8C(const void *, int, int, int, void *);
extern void *func_080D9B64(void *);

u32 func_08114F1C(void *task, Descriptor *descriptor, Payload *p)
{
    u8 i;

    switch (descriptor->phase) {
    case 0:
        p->delay = 10;
        break;
    case 1:
        break;
    case 0x100:
        if (--p->delay == 0) {
            p->particle = func_080D6098(0x78, 0x60, 0, 1, 1, p->unknown_0C,
                                        data_083A38D8, task);
            p->child = func_080D3E9C(data_0894DC38, task);
            func_080D3F84(p->child, 24, 255);
            func_080D7220(data_088F46CC, 1, 3, 0, 0, 0);
            p->window = func_080DAB84(0, 0, 0, task);
            g_control_flags_03000940.winin_lo = 63;
            g_control_flags_03000940.winout_lo = 63 & ~func_080035D0(3);
            g_control_flags_03000940.win0h_hi = 0;
            g_control_flags_03000940.win0h_lo = 0;
            g_control_flags_03000940.win0v_hi = 0;
            g_control_flags_03000940.win0v_lo = 255;
            g_control_flags_03000940.display |= 0x2000;
            p->other = func_080DFD8C(data_083A3978, 1, 4, 0, task);
            ++descriptor->phase;
        }
        break;
    case 0x101:
        for (i = 0; i < 13; i++)
            if (p->delay == data_083A38F0[i].key)
                break;
        p->delay++;
        if (i == 13)
            break;
        data_03003860.color = 0x7F18;
        p->effect = func_08147A7C(0x71, 1, 5);
        p->x = data_083A38F0[p->index].x;
        p->y = data_083A38F0[p->index].y;
        p->width = data_083A38F0[p->index].width - 1;
        p->height = data_083A38F0[p->index].y;
        func_080DABB4(p->window);
        func_080DADFC(p->window);
        func_080DABC4(p->window, p->x, p->y, (u16)p->x + p->height, 0, 0);
        func_080DABC4(p->window, (u16)p->x + p->width, p->y,
                      p->height + ((u16)p->x + p->width), 0, 1);
        func_080D9B98(p->window);
        ++descriptor->phase;
        break;
    case 0x102:
        p->delay++;
        p->effect = func_081484CC(p->effect);
        if (p->effect)
            break;
        if (++p->index <= 12) {
            descriptor->phase = 0x101;
            break;
        }
        g_control_flags_03000940.display &= ~func_080035A8(3);
        g_control_flags_03000940.display &= 0xDFFF;
        ++descriptor->phase;
        break;
    case 0x103:
        p->child = func_080D3F08(p->child);
        if (p->child)
            break;
        p->particle = func_080D6134(p->particle);
        if (p->particle)
            break;
        p->window = func_080D9B64(p->window);
        if (!p->window) {
            g_control_flags_03000940.bldcnt_lo = 0;
            descriptor->phase = 2;
        }
        break;
    }
    return 0;
}
