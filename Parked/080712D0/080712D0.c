#include "ffta.h"

/* Complete target: [0x080712D0, 0x08071374), 164 bytes.
 * f0b5204c204f214d281c211c3422012394f71af8a0267600201c391c321cd0f0
 * bdfa1b4f281c211c3522012394f70cf8201c391c321cd0f0b1fa00231548021c
 * 84328424640017211078002800d00133121901390029f7da0f4908680f4a8018
 * 03700968181c002b00dad81c821003200340002b00d00132094bc8180270f0bc
 * 01bc0047b03c0002007b01065c5a3b08807d010600000002182800035c090000
 * 8a090000
 */

typedef struct {
    u8 unknown_000[0x95C];
    u8 field_95C;
    u8 unknown_95D[0x2D];
    u8 field_98A;
} State080712D0;

extern const u8 data_083B5A5C[];
extern u8 data_02003CB0[];
extern u8 data_06017B00[];
extern u8 g_state_02000000[];
extern State080712D0 *data_03002818;

extern u32 func_08005318(const u8 *resource, void *destination,
                        u16 first, u16 count);
extern void func_0814186C(const void *source, void *destination, u32 control);

void func_080712D0(void)
{
    u8 *scratch = data_02003CB0;
    u8 *destination = data_06017B00;
    const u8 *resource = data_083B5A5C;
    u8 *field;
    State080712D0 *state;
    s32 count;
    s32 i;
    s32 groups;

    func_08005318(resource, scratch, 52, 1);
    func_0814186C(scratch, destination, 0x140);
    destination += 0x280;
    func_08005318(resource, scratch, 53, 1);
    func_0814186C(scratch, destination, 0x140);

    count = 0;
    field = g_state_02000000 + 0x84;
    for (i = 23; i >= 0; i--) {
        if (*field)
            count++;
        field += 0x108;
    }
    data_03002818->field_95C = count;
    state = data_03002818;
    groups = count / 4;
    if (count & 3)
        groups++;
    state->field_98A = groups;
}
