typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern const u8 data_083E105C[];
extern const u8 *func_080071A8(const u8 *table, u16 index);
extern u32 func_0800588C(const u8 *bytes);

/* Target: 080CB84C..080CB868, 28 bytes. */
u32 func_080CB84C(u8 index)
{
    return func_0800588C(func_080071A8(data_083E105C, index));
}
