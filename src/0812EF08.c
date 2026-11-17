#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u8 value_04;
    u8 value_05;
    u8 value_06;
} Object0812EF08;

typedef struct {
    u16 first;
    u16 second;
} ValuePair0812F194;

extern const ValuePair0812F194 data_083A84A4[];
extern s32 func_080C7EA4(const void *object, u32 selector);
extern u16 func_08022238(void *object, u8 *output);

/* An inlined copy of func_0812F194 (src/0812F194.c). */
static inline void inlined_0812F194(u8 selection, u16 *first, u16 *second)
{
    const ValuePair0812F194 *table = data_083A84A4;
    const ValuePair0812F194 *pair = &table[selection];

    *first = pair->first;
    *second = pair->second;
}

/* Complete [0x0812EF08, 0x0812EF94): 140 bytes, 64 instructions. */
u32 func_0812EF08(Object0812EF08 *object, u16 *result, u8 *output, u8 selection)
{
    u16 saved_04 = func_080C7EA4(object, 1);
    u16 saved_06 = func_080C7EA4(object, 3);
    u16 saved_05 = func_080C7EA4(object, 2);
    u16 first;
    u16 second;

    inlined_0812F194(selection, &first, &second);
    object->value_04 = 1;
    object->value_06 = second;
    object->value_05 = first;
    *result = func_08022238(object, output);
    object->value_04 = saved_04;
    object->value_06 = saved_06;
    object->value_05 = saved_05;
    return 1;
}
