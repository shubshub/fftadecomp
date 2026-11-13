#include "ffta.h"

// Complete target [0x0806E298, 0x0806E384), 236 bytes, 90 instructions.

typedef struct {
    u8 unknown_00[0xC];
    void *buffer;
    u8 unknown_10[5];
    u8 width;
    u8 height;
} Grid0806E298;

typedef struct {
    u8 unknown_0000[0x1494];
    u8 window[0x14C0 - 0x1494];
    Grid0806E298 grid;
    u8 unknown_14D8[0x1508 - 0x14D8];
    u8 resource[0x446D - 0x1508];
    u8 rows;
    u8 unknown_446E[0x4504 - 0x446E];
    u8 table[0x4BFB - 0x4504];
    u8 table_mode;
} Root0806E298;

typedef struct {
    u8 unknown_0000[0x1F6C];
    u16 selection;
} State0806E298;

typedef struct {
    u8 unknown_00[0x10];
    u8 *destination;
} Display0806E298;

typedef void (*Callback0806E298)(void *);

extern Root0806E298 *data_0200F428;
extern State0806E298 g_state_02000000;
extern Display0806E298 data_030008B0;
extern u8 data_0600C800[];
extern u8 func_080CBDC0(void *table, u8 index, u16 selection, u8 mode);
extern void func_08016210(void *window, const void *resource, u16 tile, u16 rows);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08015D58(void *window, Callback0806E298 draw, Callback0806E298 cursor);
extern void func_0806EB48(void *cursor);
extern void func_0806E170(u8 first, u8 second, u32 flag);
extern void func_0806E48C(void *window);

void func_0806E298(u8 index, u8 first, u8 second)
{
    u16 fill;
    Callback0806E298 cursor = 0;   /* passed as a value; a literal 0 changes the register allocation */
    Grid0806E298 *grid;

    data_0200F428->rows = func_080CBDC0(data_0200F428->table, index,
                                        g_state_02000000.selection,
                                        data_0200F428->table_mode);
    func_08016210(data_0200F428->window, data_0200F428->resource,
                  (data_0600C800 - data_030008B0.destination) / 32,
                  data_0200F428->rows);
    grid = &data_0200F428->grid;
    fill = 0;
    func_0814186C(&fill, grid->buffer,
                  ((grid->width * grid->height * 2) & 0x1FFFFF) | 0x01000000);
    func_08015D58(data_0200F428->window, func_0806EB48, cursor);
    func_0806E170(first, second, 1);
    func_0806E48C(data_0200F428->window);
}
