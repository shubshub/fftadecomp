#include "ffta.h"

/* Target: complete [0x0800D8F8, 0x0800D95C), 100 bytes. */
typedef struct {
    u16 values[160];
} ValueRow;

extern ValueRow *func_0800C614(void *object);
extern void func_0800C64C(void *object);

void func_0800D8F8(void *object, u8 mode, u8 row, u8 index, u16 value)
{
    ValueRow *values = 0;

    switch (mode) {
    case 0:
        values = func_0800C614(object);
        break;
    case 1:
        values = func_0800C614(object) + row;
        break;
    case 2:
        values = func_0800C614(object) + row;
        break;
    }
    values->values[index] = value;
    func_0800C64C(object);
}
