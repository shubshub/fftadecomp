#include "ffta.h"

/* Complete target: [0x0806E384, 0x0806E48C), 264 bytes, 106 instructions.
 * f0b557464e464546e0b481b0031c1b061b0e09060e0e1206120e9046234f386823494018
 * 191c5ef025fa3968214a9146494408703b68204882461d181f495c181f4801691f48401a
 * 002800da1f30c202120c494658180378281c211ca7f716ff3a68a6204001121869460020
 * 0880d168537d907d1a1c424352008020400402436846d3f031fa386850440f490022a7f7
 * a1fc386848440178301d81421ddc081c042813d9081f0006060e16e028f4000204450000
 * 6d4400009414000008150000b008000300c8000649eb06080026404503d8481e0006000e
 * 8046301c41460222fff784fe064800680649401800f00cf801b038bc9846a146aa46f0bc
 * 01bc004728f4000294140000
 *
 * The item list of one shop category: collect the category's items, draw
 * the window, clear the list's tiles, then restore the saved top row and
 * cursor row (func_0806B6D0 passes them in) clamped to the new item count,
 * four rows being visible.  func_0806E298 (src/0806E298.c) builds the
 * other list the same way, without the clamp. */

typedef struct {
    u8 unknown_00[0xC];
    void *buffer;
    u8 unknown_10[5];
    u8 width;
    u8 height;
} Grid0806E384;

typedef struct {
    u16 item;
    u8 quantity;
    u8 unknown_03;
} Item0806E384;

typedef struct {
    u8 unknown_0000[0x1494];
    u8 window[0x14C0 - 0x1494];
    Grid0806E384 grid;
    u8 unknown_14D8[0x1508 - 0x14D8];
    u8 content[0x446D - 0x1508];
    u8 count;
    u8 unknown_446E[0x4504 - 0x446E];
    Item0806E384 items[0x17C];
} Root0806E384;

typedef struct {
    u8 unknown_00[0x10];
    u8 *destination;
} Display0806E384;

typedef void (*Callback0806E384)(void *);

extern Root0806E384 *data_0200F428;
extern Display0806E384 data_030008B0;
extern u8 data_0600C800[];
extern u16 func_080CC7F8(Item0806E384 *output, u8 selector);
extern void func_08016210(void *window, const void *content, u16 tile, u16 count);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08015D58(void *window, Callback0806E384 draw, Callback0806E384 cursor);
extern void func_0806EB48(void *cursor);
extern void func_0806E170(u16 top, u8 row, u8 mode);
extern void func_0806E48C(void *window);

void func_0806E384(u8 entry, u8 position, u8 row)
{
    u16 fill;
    Grid0806E384 *grid;

    data_0200F428->count = func_080CC7F8(data_0200F428->items, entry);
    func_08016210(data_0200F428->window, data_0200F428->content,
                  (data_0600C800 - data_030008B0.destination) / 32,
                  data_0200F428->count);
    grid = &data_0200F428->grid;
    /* CpuFill16(0, grid->buffer, width * height << 2): the byte size,
     * halved to halfwords; the * 2 and * 4 spellings give other bytes. */
    fill = 0;
    func_0814186C(&fill, grid->buffer,
                  ((grid->width * grid->height << 2) / 2 & 0x1FFFFF) | 0x01000000);
    func_08015D58(data_0200F428->window, func_0806EB48, 0);
    if (data_0200F428->count <= position + 4) {
        if (data_0200F428->count > 4) {
            position = data_0200F428->count - 4;
        } else {
            position = 0;
            if (data_0200F428->count <= row)
                row = data_0200F428->count - 1;
        }
    }
    func_0806E170(position, row, 2);
    func_0806E48C(data_0200F428->window);
}
