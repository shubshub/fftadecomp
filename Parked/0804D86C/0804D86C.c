#include "ffta.h"

extern u16 g_control_flags_03000940;

extern void func_0804D9D0(void);
extern void func_0804DBF8(void);
extern void func_0804DD54(void);
extern void func_0804DDCC(u8 first, u16 second);
extern void func_0804DE8C(void);
extern u32 func_0804DF08(void);

/* Complete [0x0804D86C, 0x0804D91C): 176 bytes.
 * Target: 10b50c1c207809284fd88000014940180068874684d80408c4d80408ccd80408d4d80408e8d8040808d90408f6d80408dcd80408fcd80408acd8040816d90408044a1188e0235b01181c0843108009202ae000004009000300f084f8012023e000f094f902201fe000f03efa06201be001200c2100f074fa032015e000f00efb0006002811d005200ee000f0c9fa0ae000200c2100f064fa042005e000f0fefa0006002801d00820207010bc01bc0047
 */
void func_0804D86C(void *opaque, u8 *state)
{
    switch (*state) {
    case 8:
        g_control_flags_03000940 = 0x1C00 | g_control_flags_03000940;
        *state = 9;
        break;
    case 0:
        func_0804D9D0();
        *state = 1;
        break;
    case 1:
        func_0804DBF8();
        *state = 2;
        break;
    case 2:
        func_0804DD54();
        *state = 6;
        break;
    case 6:
        func_0804DDCC(1, 12);
        *state = 3;
        break;
    case 3:
        if ((u8)func_0804DF08())
            *state = 5;
        break;
    case 5:
        func_0804DE8C();
        *state = 8;
        break;
    case 7:
        func_0804DDCC(0, 12);
        *state = 4;
        break;
    case 4:
        if ((u8)func_0804DF08())
            *state = 8;
        break;
    case 9:
        break;
    }
}
