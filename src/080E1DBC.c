#include "ffta.h"

// Target 0x080E1DBC, 292 bytes (complete span including literal pool):
// 70b583b0051c0e1c141c318880204000814216d0814202dc002909d073e0034881422bd0013081423fd06ce001010000b08aa070f08a20717068a061b068606261e02079002811d1a0693c21fcf780f908492279900040180068074952181178009504220023fdf7b3ff20623088013048e00000945b3908985b39082088002804d001382080000400283cd1e069002802d0e078002836d0a069a11d221c0832f9f7b4ff308801302ce0e069f9f7f8fd051ce561002d26d1a069fcf7bbf90006002820d02079002804d1a06900210022fcf760f901a805800d4c211c0d4a5ff0e7fc684606300580802189006418211c094a5ff0ddfc029502a80849084a5ff0d5fc02203080002003b070bc02bc0847203900034000000170000001c0ff000610000001

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *object;
    void *unknown_08;
    u8 unknown_0C[8];
    u16 selector;
    u16 index;
} Descriptor080E1DBC;

typedef struct {
    u16 delay;
    u8 selector;
    u8 ready;
    u8 index;
    u8 unknown_05;
    s16 x;
    s16 y;
    u8 unknown_0A[0xE];
    void *object;
    void *child;
    void *record_child;
    void *unknown_24;
} Work080E1DBC;

extern u16 data_03003920[];
extern u32 data_0600FFC0[];
extern const void *const data_08395B94[];
extern const u8 data_08395B98[];
extern void func_080DE10C(void *object, u16 value);
extern void *func_080DFD8C(const void *records, u8 count, u16 flags,
                         u16 delay, void *parent);
extern void func_080DBDC8(void *object, s16 *x, s16 *y);
extern void *func_080DBA5C(void *task);
extern u8 func_080DE1F0(void *object);
extern void func_080DE150(void *object, u16 first, u16 second);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08141868(const void *source, void *destination, u32 control);

static inline void fill_halfwords(const u16 *source, u16 *destination, u32 control)
{
    func_0814186C(source, destination, control);
}

u32 func_080E1DBC(void *task, Descriptor080E1DBC *descriptor, Work080E1DBC *work)
{
    u16 zero_a;
    u16 zero_b;
    u32 zero_c;
    void *child;
    u16 *buffer;

    switch (descriptor->phase) {
    case 0:
        work->selector = descriptor->selector;
        work->index = descriptor->index;
        work->object = descriptor->object;
        work->unknown_24 = descriptor->unknown_08;
        break;
    case 0x100:
        if (work->index == 0) {
            func_080DE10C(work->object, 0x3C);
            work->record_child = func_080DFD8C(data_08395B94[work->index],
                                               data_08395B98[work->index],
                                               4, 0, task);
        }
        descriptor->phase++;
        break;
    case 0x101:
        if (work->delay != 0) {
            work->delay--;
            if (work->delay != 0)
                break;
        }
        if (work->child != 0 && work->ready == 0)
            break;
        func_080DBDC8(work->object, &work->x, &work->y);
        descriptor->phase++;
        break;
    case 0x102:
        child = func_080DBA5C(work->child);
        work->child = child;
        if (child != 0)
            break;
        if (func_080DE1F0(work->object) != 0) {
            if (work->index == 0)
                func_080DE150(work->object, 0, 0);
            zero_a = 0;
            buffer = data_03003920;
            fill_halfwords(&zero_a, buffer, 0x01000040);
            zero_b = 0;
            buffer += 0x100;
            fill_halfwords(&zero_b, buffer, 0x01000070);
            zero_c = 0;
            func_08141868(&zero_c, data_0600FFC0, 0x01000010);
            descriptor->phase = 2;
        }
        break;
    }
    return 0;
}
