/* Target 0x080DC414, 132 bytes including the literal at 0x080DC494:
 * 70b5 81b0 041c 0d1c 1206 160e 00f096ff 6946 6a46 0132
 * bdf7ebfb 011c 281c 34f783ff 6846 0178 281c 34f76cfe
 * 6846 0130 0178 281c 34f76afe 201c 00f07fff bdf7cffb
 * 011c 0904 0914 281c 34f777fe 201c bdf7d4fb 0006 000e
 * ff2e 08d0 4001 084a 8018 7101 8918 1022 65f0f6f9
 * 301c 0106 0916 281c 34f75afe 01b0 70bc 01bc 0047 603a0003
 */
#include "ffta.h"

typedef struct {
    u16 colors[16];
} Palette;

typedef struct {
    u8 first;
    u8 second;
} ObjectOutputPair;

void *func_080DD350(void *object);
u32 func_08099C04(void *object, u8 *first, u8 *second);
void func_0801133C(void *object, u32 value);
void func_08011118(void *object, u8 value);
void func_08011120(void *object, u8 value);
u16 func_08099BF4(void *object);
void func_08011150(void *object, s16 value);
u8 func_08099C10(const void *object);
void func_0814186C(const void *source, void *destination, u32 control);
void func_08011140(void *object, s8 value);

void func_080DC414(void *source, void *destination, u8 palette)
{
    ObjectOutputPair outputs;
    u8 palette_index;

    func_0801133C(destination, func_08099C04(func_080DD350(source), &outputs.first, &outputs.second));
    func_08011118(destination, outputs.first);
    func_08011120(destination, outputs.second);
    func_08011150(destination, (s16)func_08099BF4(func_080DD350(source)));
    palette_index = func_08099C10(source);
    if (palette != 0xFF) {
        func_0814186C(&((Palette *)0x03003A60)[palette_index],
                      &((Palette *)0x03003A60)[palette], 0x10);
        palette_index = palette;
    }
    func_08011140(destination, (s8)palette_index);
}
