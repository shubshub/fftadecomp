#include "ffta.h"

extern u8 data_06008000[];
extern u8 data_0600E000[];
extern u8 data_06005000[];
extern void func_0801E458(u8 layer, u8 format, u8 mode, s16 x, s16 y,
                          void *source, void *destination);

/* 0812B340..0812B384: 68 bytes, including literal pool.
 * 30b583b0002500950b4c01940b480290022001210022d023f3f67ef800950194
 * 07480290032001210122d023f3f674f803b030bc01bc00470080000600e0000600500006
 */
void func_0812B340(void)
{
    func_0801E458(2, 1, 0, 208, 0, data_06008000, data_0600E000);
    func_0801E458(3, 1, 1, 208, 0, data_06008000, data_06005000);
}
