/* Target: 0x08000460-0x080004B0, 80 complete bytes. */
typedef unsigned char u8;
typedef unsigned short u16;

extern u8 data_03000E10[];
extern u8 data_03000000[];
extern u16 data_04000130;
extern void func_08001194(void);
extern void func_08001244(void);
extern void func_080069F4(u8 *, int);
extern void func_08002804(void);
extern void func_08001CD0(void);
extern void func_08001CE0(void);
extern void func_0800221C(u8 *, u16);

void func_08000460(void)
{
    func_08001194();
    func_08001244();
    func_080069F4(data_03000E10, 3);
    func_08002804();
    func_08001CD0();
    func_08001CE0();
    func_0800221C(data_03000000, (u16)(data_04000130 ^ 0x3FF));
}
