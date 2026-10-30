#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u8 mode;
    u8 unknown_05[7];
    u32 word_0C;
    u32 word_10;
    u32 word_14;
    u32 word_18;
} Object08024A24;

extern u8 func_0801BDB0(void);
extern u8 func_0801CC18(u8 column, u8 row);
extern void func_0801C918(s16 first, s16 second, s16 third,
                         s16 *first_output, s16 *second_output,
                         s16 *third_output);
extern void func_0801C960(s16 first, s16 second,
                         s16 *first_output, s16 *second_output);
extern u16 func_0801B938(s16 first, s16 second);
extern void func_08025238(Object08024A24 *object);

/* Complete [08024A24, 08024ABA): 150 bytes.
 * 70b584b0061cf7f7c1f9000600283ed1b0894101103102aa1180318a4a011032
 * 03ad2a800006000e0906090ef8f7e2f80006000d6c460a34208002a80021405e
 * 0022a15e0023ea5e0094019502abf7f751ff02a80021405e0022a15e02aa231c
 * f7f76cff02a800887838000400142188603909040914f6f74dfff06831697061
 * b1613079042802d1301c00f0c3fb04b070bc01bc0047
 */
void func_08024A24(Object08024A24 *object)
{
    if (func_0801BDB0() == 0) {
        u16 column = object->word_0C;
        u16 row = object->word_10;
        s16 first = (column << 5) + 16;
        s16 second;
        s16 third = (row << 5) + 16;

        second = func_0801CC18(column, row) << 4;
        func_0801C918(first, second, third, &first, &second, &third);
        func_0801C960(first, second, &first, &second);
        func_0801B938(first - 120, second - 96);
        object->word_14 = object->word_0C;
        object->word_18 = object->word_10;
        if (object->mode == 4)
            func_08025238(object);
    }
}
