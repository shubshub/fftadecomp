#include "ffta.h"

/* Complete [0x08135890, 0x08135982): 242 bytes, 77 instructions.
 * Target bytes:
 * 30b50d1c2878032858d0032806dc012824d001282edc002805d067e0052860d0
 * 052857db62e002f0f1f8074c0749084a201c0123d1f6daf8064a201c0021d1f6
 * 05f9054901202ce0a0f30002c0f30002bcf300028560130890f3000203480121
 * d1f680f8024800783fe00000a0f3000290f300020c48d1f629f902f0e1f802f0
 * c5f80a4c0a4802f0e9f82060002102f0fff80849002008700720cdf6cdff0649
 * 03202870087021e0a0f30002b8f30002e02200004c28000390f3000203480121
 * d1f650f8024800780fe00000a0f3000290f30002cdf66afe0120d4f6c7f80220
 * 00e00b20cdf6a8ffff20287030bc01bc0047
 */
/* The 0x22E0-byte resource func_08137B20 (src/08137B20.c) clears and adopts. */
typedef struct {
    u8 unknown_00[8];
    u16 *large_second;
    u16 *large_first;
    u16 *small_second;
    u16 *small_first;
    u8 buffer[1];
} ResourceState;

extern Table data_0200F3A0;
extern u32 data_0200F3C0[];
extern u8 data_0200F3BC[];
extern u8 g_state_0200F390;
extern ResourceState *data_0200F3B8;
extern u8 data_0300284C;

extern void func_08137A9C(void);
extern void func_08006A7C(Table *runner, u32 *handlers, u8 *flags, u8 count);
extern void func_08136084(void *task, u8 *phase);
extern void func_080069F4(Table *runner, u8 count);
extern void func_08006B5C(Table *runner);
extern void func_08137AD0(void);
extern void *func_08137AEC(u32 bytes);
extern void func_08137B20(ResourceState *resource, u8 mode);
extern void func_080038C8(u16 value);
extern void func_0800363C(void);
extern void func_08009AFC(u16 event);

void func_08135890(u8 index, u8 *state)
{
    switch (*state) {
    case 0:
        func_08137A9C();
        func_08006A7C(&data_0200F3A0, data_0200F3C0, data_0200F3BC, 1);
        func_08006ADC(&data_0200F3A0, 0, (u32)func_08136084);
        g_state_0200F390 = *state = 1;
        break;
    case 1:
        func_080069F4(&data_0200F3A0, 1);
        *state = g_state_0200F390;
        break;
    case 2:
        func_08006B5C(&data_0200F3A0);
        func_08137AD0();
        func_08137A9C();
        data_0200F3B8 = func_08137AEC(0x22E0);
        func_08137B20(data_0200F3B8, 0);
        data_0300284C = 0;
        func_080038C8(7);
        g_state_0200F390 = *state = 3;
        break;
    case 3:
        func_080069F4(&data_0200F3A0, 1);
        *state = g_state_0200F390;
        break;
    case 4:
        func_0800363C();
        func_08009AFC(1);
        func_080038C8(2);
        *state = 0xFF;
        break;
    case 5:
        func_080038C8(11);
        *state = 0xFF;
        break;
    /* The finished state that cases 4 and 5 store (0x08135978).  A seventh
     * case is what makes the dispatch a compare tree (0x08135896-0x081358B4)
     * rather than a jump table; its empty body shares the exit, so its test
     * folds into the branch at 0x081358B4.  The ROM does not give the value
     * (71..255 all produce these bytes); 0xFF follows src/08068AE0.c and
     * src/0803DC1C.c. */
    case 0xFF:
        break;
    }
}
