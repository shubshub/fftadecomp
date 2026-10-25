/* Target 0x081021E8, complete [0x081021E8, 0x081022AC), 196 bytes. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

extern const u8 data_08502ED8[];

extern void *func_080D5E80(const void *, u16, s16, s16, s16, s16, u8);
extern void func_08010884(void *, u8);
extern void func_080112E8(void *, u8);
extern void func_0801115C(void *, u8);
extern void func_0801121C(void *, s16);
extern void func_080111A8(void *, u8);
extern void func_080112A4(void *, u8);

void *func_081021E8(u8 selector, const s16 *coordinates, void **outputs)
{
    void *first;
    u8 i;

    first = func_080D5E80(data_08502ED8, selector, coordinates[0],
        (s16)(coordinates[1] + 56), coordinates[2], 640, 12);
    func_08010884(first, 1);
    func_080112E8(first, 1);
    func_0801115C(first, 0);
    func_0801121C(first, -1);

    for (i = 0; i < 4; i++) {
        outputs[i] = func_080D5E80(data_08502ED8, selector, coordinates[0],
            (s16)(coordinates[1] + 56), coordinates[2], 640, 12);
        func_0801115C(outputs[i], 0);
        func_080111A8(outputs[i], 1);
        func_0801121C(outputs[i], -1);
        func_080112A4(outputs[i], 1);
    }

    return first;
}
