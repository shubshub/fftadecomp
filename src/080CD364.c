#include "ffta.h"

extern u8 func_080C8240(void *object);
extern u8 func_080C8260(const void *object);
extern s32 func_080C7EA4(const void *object, u32 selector);
extern u32 func_080C8570(u8 first, u8 second, u8 selector);
extern void func_080C9574(u16 bitIndex, u16 enabled);

/* Target [0x080CD364, 0x080CD426), 194 bytes:
 * f0b5474680b4051c0906090e8846faf765ff000600284fd1281cfaf76fff0006002849d102247327281c0321faf788fd0138042825d880000149401800688746a8d30c08bcd30c08c2d30c08c8d30c08ced30c08e2d30c0802240c2711e00d2413270ee014241b270be01c24232708e0f01c0004000c0121fcf7caf81ce024242b27261cbe4217dc3406240e201c211c2522fbf7bbf8051c2d062d0e201c211c2622fbf7b3f80006000e454501d88045ded90136be42e7dd08bc9846f0bc01bc0047
 */
void func_080CD364(void *object, u8 value)
{
    s32 first;
    s32 last;
    s32 index;

    if (func_080C8240(object) || func_080C8260(object))
        return;

    first = 2;
    last = 115;
    switch (func_080C7EA4(object, 3)) {
    case 1:
        first = 2;
        last = 12;
        break;
    case 2:
        first = 13;
        last = 19;
        break;
    case 3:
        first = 20;
        last = 27;
        break;
    case 4:
        first = 28;
        last = 35;
        break;
    case 5:
        first = 36;
        last = 43;
        break;
    }

    for (index = first; index <= last; index++) {
        u8 lower = (u8)func_080C8570(index, index, 0x25);
        u8 upper = (u8)func_080C8570(index, index, 0x26);

        if (lower <= value && value <= upper) {
            func_080C9574(index + 3, 1);
            return;
        }
    }
}
