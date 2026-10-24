#include "ffta.h"

/* 0x080DC34C - 200 bytes, including the final 0x03003A60 literal.
 * Target: f0b557464e464546e0b488b0051c1098119c0906090e07911204120c90461b04
 *         1b0c99460004000c82462406240e281c00f0e8ff06a96a461932bdf73dfc071c
 *         281c00f0dfffbdf72ffc0604281cbdf739fc0006010eff2c08d04801194a8018
 *         61018918102265f05bfa211c42461004001400904a4610040014019052461004
 *         0014029030140390049106200590381c00210022079b34f7b1ff041c06a80178
 *         201c34f793fe684619300178201c34f791fe201c08b038bc9846a146aa46f0bc
 *         02bc0847603a0003
 */
typedef struct {
    u8 unknown_00[0x1E];
    u8 field_1e;
} Struct08099C10;

typedef struct {
    u8 data[32];
} Record32;

struct Object08011118;

extern const void *func_080DD350(const void *object);
extern u32 func_08099C04(const void *object, u8 *first, u8 *second);
extern u16 func_08099BF4(const void *object);
extern u8 func_08099C10(const Struct08099C10 *object);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void *func_08011348(u32 resource, u32 argument_1, u16 argument_2,
                          u8 selector, s16 x, s16 y, s16 z, s16 field_12,
                          s16 palette, u16 flags);
extern void func_08011118(struct Object08011118 *object, u8 value);
extern void func_08011120(u8 *object, u8 value);

void *func_080DC34C(const Struct08099C10 *object, u8 selector,
                   u16 x, u16 y, u16 z, u8 requested_palette)
{
    u8 attributes[2];
    u32 resource = func_08099C04(func_080DD350(object), &attributes[0], &attributes[1]);
    s16 field_12 = func_08099BF4(func_080DD350(object));
    u8 palette = func_08099C10(object);
    void *created;

    if (requested_palette != 0xFF) {
        func_0814186C(((Record32 *)0x03003A60)[palette].data,
                      ((Record32 *)0x03003A60)[requested_palette].data, 0x10);
        palette = requested_palette;
    }
    created = func_08011348(resource, 0, 0, selector, (s16)x, (s16)y,
                           (s16)z, (s16)field_12, palette, 6);
    func_08011118(created, attributes[0]);
    func_08011120(created, attributes[1]);
    return created;
}
