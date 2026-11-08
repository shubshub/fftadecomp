#include "ffta.h"

extern const u8 data_085668B0[];
extern u8 *data_03002818;
extern u8 data_0600BD20[];

extern u8 func_080C8194(const void *object, u8 category);
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_0808B7C0(s32 index, u16 *destination, u16 tile,
                          u16 count, u16 flags);
extern u16 func_08015110(void *context, void *destination,
                       const u8 *text, u8 mode, u8 reset);

void func_08074FA4(u8 *object)
{
    const u8 *resources = data_085668B0;
    const u8 *text = *(const u8 **)(resources + 0xD4);

    if ((*(u16 *)(object + 0x28) & 0x1C) == 0 &&
        (object[4] == 1 ||
         func_080C8194(object, 0x5E) ||
         func_080C8194(object, 10) ||
         func_080C8194(object, 9) ||
         func_080C8194(object, 4) ||
         func_080C8194(object, 12) ||
         func_080C8194(object, 6))) {
        *func_0808B8E4(4, 1, 0, 9) = 0xD00C;
        func_0808B7C0(4, func_0808B8E4(4, 1, 1, 8), 0x1E9, 10, 0xC000);
        func_08015110(data_03002818 + 0x68C, data_0600BD20, text, 0, 1);
    } else {
        *func_0808B8E4(4, 1, 0, 9) = 0xD00C;
        func_0808B7C0(4, func_0808B8E4(4, 1, 1, 8), 0x1E9, 10, 0xC000);
        func_08015110(data_03002818 + 0x68C, data_0600BD20, text, 1, 1);
    }
}
