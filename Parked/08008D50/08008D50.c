#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    u32 value;
} Resource;

typedef struct {
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u16 unknown_04;
    u16 flags;
    u8 mode;
    u8 unknown_09[7];
} Descriptor;

typedef struct {
    u32 field_00;
    u32 field_04;
    u32 field_08;
    u32 field_0C;
    u8 field_10;
    u8 field_11;
    u8 field_12;
    u8 field_13;
    u16 field_14;
    u8 field_16;
    u8 field_17;
    u16 field_18;
    u16 field_1A;
    u8 field_1C;
    u8 field_1D;
    u8 field_1E;
    u8 field_1F;
    u16 field_20;
    u16 field_22;
    u16 field_24;
    u16 field_26;
    u16 field_28;
    u16 field_2A;
} State08017424;

typedef struct {
    u8 unknown_00[0x18];
    Resource *first;
    Resource *second;
    u8 slot;
    u8 unknown_21[0x293];
    Descriptor descriptor;
    State08017424 widget;
} State;

typedef struct {
    u8 unknown_00[0xAE];
    u8 enabled;
} ControlPrefix;

typedef void (*CopyBuffer)(void *destination, const void *source, s32 size);
typedef u8 (*TaskCallback)(void);

extern ControlPrefix g_state_020020D0;

void func_08017424(State08017424 *state, u32 first, u32 second,
                   u8 x, u8 y, u8 width, u8 height, u16 flags,
                   u8 format, u16 first_setting, u16 second_setting, u8 style);
void func_08013B7C(Descriptor *descriptor, State08017424 *widget, void *storage);
void func_08016C90(State08017424 *widget, u8 mode);
u8 func_080098F4(TaskCallback callback, u32 argument);
u8 func_08008DFC(void);

/* Target: 0x08008D50, 172 bytes including alignment and six literal words. */
void func_08008D50(void)
{
    State **active = (State **)0x02009188;
    Descriptor *descriptor = &(*active)->descriptor;
    State08017424 *widget = &(*active)->widget;

    (*(CopyBuffer const *)0x0836D4BC)(descriptor, (const void *)0x0836D4C4,
                                   sizeof(*descriptor));
    descriptor->width += 2;
    descriptor->height = descriptor->height * 2 + 8;
    func_08017424(widget, (*active)->first->value, (*active)->second->value,
                   descriptor->x, descriptor->y, descriptor->width,
                   descriptor->height, descriptor->flags, 0x20, 5, 1, 0xC);
    g_state_020020D0.enabled = widget->field_13 - 5;
    func_08013B7C(descriptor, widget, (void *)0x02003CB0);
    func_08016C90(widget, descriptor->mode);
    (*active)->slot = func_080098F4(func_08008DFC, 0);
}
