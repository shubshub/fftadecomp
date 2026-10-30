#include "ffta.h"

typedef struct {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} Motion081130B8;

typedef struct {
    u8 mode;
    u8 unknown_01[3];
    void *object;
    u8 unknown_08[2];
    s16 delta_x;
    s16 delta_y;
    u8 duration_x;
    u8 duration_y;
    Motion081130B8 x;
    Motion081130B8 y;
} Record081130B8;

typedef struct ListNode ListNode;

extern void func_080E064C(Motion081130B8 *state);
extern void func_080107D4(void *object, u16 base, u16 value, u16 offset);
extern u8 func_080E0690(Motion081130B8 *state);
extern void func_080E0608(Motion081130B8 *state, s16 start, s16 end, s16 duration);
extern void func_08011428(ListNode *node);

/* 0x081130B8..0x08113220:
 * F0 B5 57 46 4E 46 45 46 E0 B4 82 B0 81 46 09 06
 * 09 0E 8A 46 00 27 57 45 00 D3 9D E0 B8 00 C1 19
 * C9 00 4A 46 8C 18 61 68 80 46 00 29 00 D1 8D E0
 * 25 1C 10 35 28 1C CD F7 AD FA 26 1C 1C 36 30 1C
 * CD F7 A8 FA 20 78 00 28 32 D0 60 68 21 8A 09 04
 * 89 15 A2 8B 12 04 92 15 00 23 FD F6 5F FB 28 1C
 * CD F7 BA FA 00 06 00 28 0D D0 10 23 E1 5E 62 89
 * 10 04 80 14 12 18 20 8A 12 18 12 04 12 14 A3 7B
 * 28 1C CD F7 65 FA 30 1C CD F7 A6 FA 00 06 00 28
 * 38 D0 1C 22 A1 5E A2 89 10 04 80 14 12 18 A3 8B
 * D2 18 12 04 12 14 E3 7B 30 1C CD F7 51 FA 29 E0
 * 60 68 10 22 A1 5E 1C 23 E2 5E 00 23 FD F6 2E FB
 * 28 1C CD F7 89 FA 00 06 00 28 0A D0 10 20 21 5E
 * 62 89 23 8A D2 18 12 04 12 14 A3 7B 28 1C CD F7
 * 37 FA 30 1C CD F7 78 FA 00 06 00 28 0A D0 1C 20
 * 21 5E A2 89 A3 8B D2 18 12 04 12 14 E3 7B 30 1C
 * CD F7 26 FA 41 46 C8 19 C0 00 4A 46 84 18 60 68
 * 6D 46 02 35 69 46 2A 1C 01 AB FD F6 35 FF 68 46
 * 00 23 C0 5E 08 21 49 42 88 42 0A DB 00 23 EA 5E
 * A7 2A 06 DC F7 28 01 DC 8A 42 07 DA 20 78 00 28
 * 04 D0 60 68 FE F6 14 F9 00 20 60 60 78 1C 00 06
 * 07 0E 57 45 00 D2 61 E7 02 B0 38 BC 98 46 A1 46
 * AA 46 F0 BC 01 BC 00 47
 */
void func_081130B8(Record081130B8 *records, u8 count)
{
    u8 index;

    for (index = 0; index < count; ++index) {
        if (records[index].object != 0) {
            Motion081130B8 *x = &records[index].x;
            Motion081130B8 *y = &records[index].y;
            u16 first;
            u16 second;
            u16 third;

            func_080E064C(x);
            func_080E064C(y);
            if (records[index].mode) {
                func_080107D4(records[index].object,
                    records[index].x.current >> 6, records[index].y.current >> 6, 0);
                if (func_080E0690(x))
                    func_080E0608(x, records[index].x.current,
                        records[index].delta_x + (records[index].delta_x >> 2) +
                        records[index].x.current, records[index].duration_x);
                if (func_080E0690(y))
                    func_080E0608(y, records[index].y.current,
                        records[index].delta_y + (records[index].delta_y >> 2) +
                        records[index].y.current, records[index].duration_y);
            } else {
                func_080107D4(records[index].object,
                    records[index].x.current, records[index].y.current, 0);
                if (func_080E0690(x))
                    func_080E0608(x, records[index].x.current,
                        records[index].delta_x + records[index].x.current,
                        records[index].duration_x);
                if (func_080E0690(y))
                    func_080E0608(y, records[index].y.current,
                        records[index].delta_y + records[index].y.current,
                        records[index].duration_y);
            }
            func_08011040(records[index].object, &first, &second, &third);
            if ((s16)first < -8 || (s16)second > 167 ||
                (((s16)first > 247 || (s16)second < -8) && records[index].mode)) {
                func_08011428(records[index].object);
                records[index].object = 0;
            }
        }
    }
}
