#include "control_flags.h"

// Target: complete [0x081102F4, 0x081104DA), 486 bytes.
typedef struct {
    u16 state;
} Event;

typedef struct {
    u16 first[16][16];
    u16 second[16][32];
} Work;

typedef struct {
    s32 origin_x;
    s32 origin_y;
    s16 display_x;
    s16 display_y;
    s16 scale_x;
    s16 scale_y;
    u16 angle;
} AffineSource;

typedef struct {
    s16 pa;
    s16 pb;
    s16 pc;
    s16 pd;
    s32 x;
    s32 y;
} AffineTransform;

extern u16 data_03003860;
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_0801DB78(void);
extern void *func_080D3AF8(void);
extern void func_08000A98(void *record, const void *source, void *destination,
                          u32 count);
extern void func_08003620(u8 value);
extern u32 func_08003A74(u32 packed);
extern u32 func_08003A80(u32 packed);
extern void func_080034B8(u16 control, u8 layer);
extern void func_08141864(const AffineSource *source,
                          AffineTransform *destination, u32 count);
extern void func_080032F8(const AffineTransform *transform, u8 layer);
extern void func_0801E610(u8 *first, u8 *second);
extern int func_080035D0(int);

int func_081102F4(void *unused, Event *event, Work *work)
{
    switch (event->state) {
    case 0: {
        u16 fill;
        u16 *source = &fill;
        *source = 0xFFFF;
        func_0814186C(source, work->second, 0x01000200);
        break;
    }
    case 1:
        break;
    case 0x100:
        func_0801DB78();
        data_03003860 = 0;
        func_08000A98(func_080D3AF8(), (void *)0x06005000, work, 0x100);
        event->state++;
        break;
    case 0x101: {
        u8 i;

        for (i = 0; i < 16; i++)
            func_0814186C(work->first[i], work->second[i], 6);
        event->state++;
        break;
    }
    case 0x102:
        func_08000A98(func_080D3AF8(), work->second, (void *)0x06005000, 0x200);
        func_08000A98(func_080D3AF8(), work->second, (void *)0x06005400, 0x200);
        event->state++;
        break;
    case 0x103: {
        AffineSource source;
        AffineTransform transform;
        u8 first;
        u8 second;
        u32 packed;
        u32 map;

        func_08000A98(func_080D3AF8(), work->second, (void *)0x06005800, 0x200);
        func_08000A98(func_080D3AF8(), work->second, (void *)0x06005C00, 0x200);
        func_08003620(1);
        packed = func_08003A74(0x06005000);
        map = func_08003A80(0x0600C000);
        func_080034B8((u16)(map | 0x8000) | packed | 0x80, 2);
        source.origin_x = 0x3000;
        source.origin_y = 0x3000;
        source.display_x = 0x78;
        source.display_y = 0x50;
        source.scale_x = 0x100;
        source.scale_y = 0x100;
        source.angle = 0;
        func_08141864(&source, &transform, 1);
        func_080032F8(&transform, 2);
        g_control_flags_03000940.bldcnt_lo = 0x84;
        g_control_flags_03000940.bldy_lo = 0x10;
        func_0801E610(&first, &second);
        g_control_flags_03000940.winin_lo =
            0x3F & ~(func_080035D0(first) | func_080035D0(second));
        g_control_flags_03000940.winout_lo = 0x10;
        event->state++;
        break;
    }
    case 0x104:
        event->state = 2;
        break;
    }
    return 0;
}
