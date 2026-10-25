/* 0x080DE3E0, 130 bytes
 * f0b5474680b4041c171c1d1c2406240e0906090e884660202cf72cf9061c201c311c2a1cfef780fc0006050e0024ac421fd24146080600168046a100002f03d088190068b8420fd0881900684146002905d0002180225200bcf79af804e0802149000022bcf794f8601c0006040eac42e3d3301c2cf708f908bc9846f0bc01bc0047
 */
#include "ffta.h"

void *func_0800A654(u32 size);
void func_0800A668(void *object);
u32 func_080DCD08(u8 selector, void *list, void *arg);
void func_0809A570(void *object, u32 clear, u32 set);

void func_080DE3E0(u8 selector, s8 flag, void *skip, void *arg)
{
    void **list = func_0800A654(0x60);
    u8 count = func_080DCD08(selector, list, arg);
    void *object;
    u8 index;

    for (index = 0; index < count; index++) {
        if (skip != 0 && list[index] == skip)
            continue;
        object = list[index];
        if (flag)
            func_0809A570(object, 0, 0x100);
        else
            func_0809A570(object, 0x100, 0);
    }
    func_0800A668(list);
}
