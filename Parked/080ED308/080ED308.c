// Complete target [0x080ED308, 0x080ED3B8), 176 bytes, 84 instructions:
// f0b5071cec21490078180068ecf7f8fb031c0024a82040003918086884420cda
// 0025102218781d7058785a70601c0006040e023308688442f4db0025a8214900
// 78180068002802da40420006050e1e2d16d8164e701c84466900881900781a78
// 18706144087859785870681c0006050e601c0006040e02339f2c0ed81e2debd9
// 9f2c0ad810211878197058785970601c0006040e02339f2cf5d9ec2149007818
// 0068ecf7f5fbf0bc01bc0047b8923908
#include "ffta.h"

typedef struct __attribute__((packed)) {
    volatile u8 eva : 8;
    volatile u8 evb : 8;
} BlendLine;

typedef struct {
    u8 unknown_00[0x150];
    s32 offset;
    u8 unknown_154[0x84];
    void *handle;
} Payload;

extern BlendLine *func_080D9B08(void *handle);
extern void func_080D9B98(void *handle);
extern const u8 gUnknown_083992B8[][2];

void func_080ED308(Payload *payload)
{
    BlendLine *line = func_080D9B08(payload->handle);
    u8 y;
    u8 i;

    for (y = 0; y < payload->offset; y++, line++) {
        line->eva = 0;
        line->evb = 16;
    }
    i = 0;
    if (payload->offset < 0)
        i = -payload->offset;
    while (i <= 30) {
        line->eva = gUnknown_083992B8[i][0];
        line->evb = gUnknown_083992B8[i][1];
        i++;
        y++;
        line++;
        if (y > 159)
            break;
    }
    for (; y <= 159; y++, line++) {
        line->eva = 16;
        line->evb = 16;
    }
    func_080D9B98(payload->handle);
}
