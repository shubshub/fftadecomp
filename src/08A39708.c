#include "ffta.h"

typedef struct {
    u8 unknown_00[0x17];
    u8 field_17;
    u8 field_18;
    u8 field_19;
    u8 field_1A;
    u8 unknown_1B;
    u16 field_1C;
} ChildParameters;

/* 0x08A39708..0x08A3971E, 22 bytes. Installer 0808F74C copies the
 * function to 03006B54. Callback slot 08394034 holds its Thumb pointer.
 */
void func_08A39708(void *object, u8 value, u32 second, u32 third,
                   u32 fourth, u32 fifth)
{
    ChildParameters *child = object;

    child->field_17 = value;
    child->field_18 = second;
    child->field_19 = third;
    child->field_1C = fourth;
    child->field_1A = fifth;
}
