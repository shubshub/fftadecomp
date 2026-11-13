#include "ffta.h"

// 0x080BDD7C..0x080BDECC: 336 bytes, 168 Thumb instructions.

u8 func_080BDCD0(void *grid, u8 x, u8 y, u8 type);
void *func_080BDC20(void *grid, u8 x, u8 y);
u8 func_080BDB64(void *node);
void func_080BDB9C(void *node, u8 *low, u8 *high);
void *func_080BDB60(void *node);
void *func_080BDB2C(void *grid);
void func_080BDBC4(void *grid, void *node, u8 x, u8 y);
void func_080BDC58(void *grid, void *node, u8 x, u8 y);
void func_080BDB68(void *node, u8 type);
s32 func_080BDB6C(void *node);
void func_080BDB74(void *node, s16 value);
void func_080BDB78(void *node, u8 low, u8 high);

static inline void *FindNibbles(void *grid, u8 x, u8 y, u8 type, u8 low, u8 high)
{
    void *node;
    u8 low2, high2;

    for (node = func_080BDC20(grid, x, y); node != 0; node = func_080BDB60(node)) {
        if (func_080BDB64(node) == type) {
            func_080BDB9C(node, &low2, &high2);
            if (low2 == low && high2 == high)
                return node;
        }
    }
    return node;
}

static inline void *FindType(void *grid, u8 x, u8 y, u8 type)
{
    void *node;

    for (node = func_080BDC20(grid, x, y); node != 0; node = func_080BDB60(node)) {
        if (func_080BDB64(node) == type)
            return node;
    }
    return node;
}

s32 func_080BDD7C(void *grid, u8 x, u8 y, u8 low, u8 high, u8 type,
                  s16 amount, u8 replace, u8 matchNibbles)
{
    void *node;
    s32 existed = 1;

    if (!replace && !func_080BDCD0(grid, x, y, type))
        return 1;

    if (matchNibbles)
        node = FindNibbles(grid, x, y, type, low, high);
    else
        node = FindType(grid, x, y, type);

    if (node == 0) {
        if (replace)
            return 0;
        node = func_080BDB2C(grid);
        if (node == 0)
            return 0;
        func_080BDBC4(grid, node, x, y);
        existed = 0;
    } else if (replace) {
        func_080BDC58(grid, node, x, y);
        return 1;
    }

    func_080BDB68(node, type);
    func_080BDB74(node, amount + func_080BDB6C(node));
    func_080BDB78(node, low, high);
    return existed;
}
