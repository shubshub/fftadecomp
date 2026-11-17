#include "ffta.h"

// Complete target [0x0813BEEC, 0x0813BF5C): 112 bytes.
// 10b582b01248c021c904124a05f0b8fc01a900200880104c216802310f4a01a805f0aefc
// 0e482168023196229200002300931e23faf73ef80a4a0b480b491368202206f08ff902b0
// 10bc01bc00470000f8699508d6040000b4f3000200040001fc649508bcd4360860380003
// ac699508

typedef void (*BufferCopier0813BEEC)(void *, const void *, u32);

extern u16 *data_0200F3B4;
extern BufferCopier0813BEEC data_0836D4BC[];
extern u16 data_03003860[][16];
extern const u16 data_089569F8[];
extern const u16 data_089564FC[];
extern const u16 data_089569AC[];

extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08135FA0(const u16 *source, u16 *destination, u16 count,
                          u8 width, u16 offset);
extern void func_08142250(void *destination, const void *source, u32 size,
                          BufferCopier0813BEEC callback);

void func_0813BEEC(void)
{
    BufferCopier0813BEEC *copy;

    func_0814186C(data_089569F8, (void *)0x06000000, 0x4D6);
    {
        u16 zero;
        u16 *source = &zero;
        *source = 0;
        func_0814186C(source, data_0200F3B4 + 1, 0x01000400);
    }
    func_08135FA0(data_089564FC, data_0200F3B4 + 1, 600, 0x1E, 0);
    copy = data_0836D4BC;
    func_08142250(data_03003860, data_089569AC, 0x20, copy[0]);
}
