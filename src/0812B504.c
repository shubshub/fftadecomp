#include "ffta.h"

extern const u8 data_0851BA62[];
extern u16 func_0812B184(const void *state);
extern void func_08001CF0(const void *source, s32 first, s32 second, u8 mode,
                          u8 first_flag, u8 second_flag, u8 third_flag,
                          u8 fourth_flag, u32 value, u8 count, u32 extra);

/* Complete target: [0x0812B504, 0x0812B538), 52 bytes.
 * 00b587b0fff73cfe011c0904090c08485c310022009201920292039204920592069295220023d6f6e1fb07b001bc004762ba5108
 */
void func_0812B504(const void *state)
{
    u16 value = func_0812B184(state);

    func_08001CF0(data_0851BA62, value + 0x5C, 0x95,
                  0, 0, 0, 0, 0, 0, 0, 0);
}
