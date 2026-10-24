/* 0x080E06A4 - 138 bytes
 * Target bytes:
 * f0 b5 57 46 4e 46 45 46 e0 b4 83 b0 89 46 90 46
 * 02 93 0b 99 00 04 07 0c 09 04 09 0c 8a 46 fc 04
 * 24 0c 60 00 20 18 29 f7 c3 ff 06 1c 34 19 00 94
 * 38 1c 49 46 42 46 33 1c 27 f7 d0 fe 00 25 28 1c
 * 00 21 03 0c 0a 04 19 1c 11 43 00 04 42 46 00 92
 * 01 96 3a 1c 4b 46 27 f7 e9 ff 6b 00 02 9a 9b 18
 * 0c 04 02 0c 20 1c 10 43 18 80 68 1c 00 04 05 0c
 * 55 45 e4 d3 30 1c 29 f7 a5 ff 03 b0 38 bc 98 46
 * a1 46 aa 46 f0 bc 01 bc 00 47
 */
#include "ffta.h"

void *func_0800A654(u32 size);
void func_0800A668(void *object);
void func_08008480(s32 count, const signed long long *coordinates,
                  const signed long long *values, signed long long *result,
                  signed long long *workspace);
signed long long func_080086D0(signed long long coordinate, s32 count,
                             const signed long long *coordinates,
                             const signed long long *values,
                             const signed long long *coefficients);

void func_080E06A4(u16 knots, const signed long long *coordinates,
                  const signed long long *values, s16 *output, u16 samples)
{
    u16 buffer_bytes;
    signed long long *coefficients;
    u16 index;

    buffer_bytes = knots * sizeof(signed long long);
    coefficients = func_0800A654(3 * buffer_bytes);
    func_08008480(knots, coordinates, values, coefficients,
                  (signed long long *)((u8 *)coefficients + buffer_bytes));
    index = 0;
    do {
        output[index] = func_080086D0((signed long long)index << 16, knots,
                                    coordinates, values, coefficients) >> 16;
        index++;
    } while (index < samples);
    func_0800A668(coefficients);
}
