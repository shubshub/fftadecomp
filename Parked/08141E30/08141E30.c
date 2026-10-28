#include "ffta.h"

/* 08141E30 .. 08141EB8: 136 bytes. */
typedef struct {
    u8 unknown_00[0x14];
    u8 manufacturer;
} FlashInfo;

extern u8 data_0200F360;
extern u8 (*data_0200F364)(const u8 *);
extern FlashInfo *data_0200F370;
extern void func_081419C0(u8);
extern void func_08141A68(void);

u16 func_08141E30(u8 phase, const u8 *address, u8 expected)
{
    u16 result = 0;
    u16 timeout_error;

    func_081419C0(phase);
    timeout_error = phase | 0xC000;
    while (data_0200F364(address) != expected) {
        if (data_0200F360) {
            if (data_0200F364(address) != expected) {
                if (data_0200F370->manufacturer == 0xC2)
                    *(u8 *)0x0E005555 = 0xF0;
                result = timeout_error;
            }
            break;
        }
    }
    func_08141A68();
    return result;
}
