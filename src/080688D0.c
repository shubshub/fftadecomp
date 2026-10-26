#include "ffta.h"

/* 0x080688D0..0x0806890C: 60 bytes. */
typedef struct {
    u8 unknown_00[0x0C];
    u8 first_control[0x10];
    u8 second_control[0x10];
    void *menu;
} MenuContext;

typedef struct {
    u8 unknown_00[0x10];
    u8 index;
} MenuRecord;

extern MenuRecord g_state_020020D0;
extern const u8 data_0851BA72[];
extern const u8 data_0851BA7A[];
extern void func_08061518(void *context, u8 index);
extern void func_08017FA8(void *control, const u8 *text, u32 x, u32 y);

void func_080688D0(MenuContext *context)
{
    func_08061518(context->menu, g_state_020020D0.index);
    func_08017FA8(context->first_control, data_0851BA72, 0xD8, 0x0E);
    func_08017FA8(context->second_control, data_0851BA7A, 0x18, 0x0E);
}
