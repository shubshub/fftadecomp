#include "ffta.h"

/* Complete [0x080D1C94, 0x080D1E70): 476 bytes, 222 instructions, six literal
 * words in two pools.
 * f0b557464e464546e0b483b0009001911206120e0292002082461c481c49401800688146
 * 002800d1cfe0032290464e46356828786e78331c41460b4019020143144a88180004000c
 * 0022162800d80122002a00d0b3e0af781c203840002800d0ade0462041430c480a189178
 * 07200840002800d0a3e0107c8006440f022c31d0022c0bdc012c0cd08ee0000000000002
 * c8280000b0feffff4cae5508032c4bd082e00298002800d17ee0b108a878424610408001
 * 0843002876d0411e09040a0c3f20024092001a436a70890d46463140433838400843a870
 * 9208a87830408001104326e04520f7f7e1fb000600285bd06c78a108a878424610408001
 * 0843002852d0421e1204110c3f2001408900434623400b436b70920d46463240a8780421
 * 494208401043a8709b08a878304080011843002838d13ae04520f7f7b7fb0006002831d0
 * 6b789908a878204082010a43111c002928d00748074e8019007881420cd81c406c70a878
 * 042149420840a8701de00000000000022b3c00001106090e091a09040a0c3f2002409200
 * 201c184010436870890d214042461140a8780426764230400843a8700020002807d00099
 * 20c1009101229244019eb24505d0484680688146002800d031e7504603b038bc9846a146
 * aa46f0bc02bc0847
 */

/* The record layout of src/080D29D4.c.  The eight bits after the ten-bit id,
 * straddling bytes 1 and 2, are that file's field_0A; this function counts
 * them down to zero. */
typedef struct {
    u16 id : 10;
    u16 countdown : 8;
    u8 status : 3;
    u8 unknown_15 : 3;
    u8 unknown_03;
    u8 unknown_04[12];
} __attribute__((packed)) Item;

/* One 0x46-byte row.  Byte 2 and field_10 are declared as src/080D29D4.c
 * declares them; this function tests the low three bits of byte 2 and switches
 * on bits 3..5 of byte 0x10, which that file leaves inside a six-bit unknown. */
typedef struct {
    u8 unknown_00[2];
    u8 unknown_02_low : 3;
    u8 kind : 3;
    u8 unknown_02_high : 2;
    u8 unknown_03[0xD];
    u16 unknown_10_low : 3;
    u16 mode : 3;
    u16 field_10 : 8;
    u16 unknown_11_high : 2;
    u8 unknown_12[0x34];
} __attribute__((packed)) ItemMetadata;

typedef struct ItemNode {
    Item *item;
    struct ItemNode *previous;
    struct ItemNode *next;
} ItemNode;

/* counter_3C2B is named as src/080A22F0.c names it. */
typedef struct {
    u8 unknown_00[0x25C8];
    ItemNode nodes[64];
    ItemNode *head;
    u8 unknown_28CC[0x135F];
    u8 counter_3C2B;
} ItemListState;

extern ItemListState g_state_02000000;
extern const ItemMetadata g_table_0855AE4C[];
extern u8 func_080C9540(u16 bitIndex);

/* An inlined copy of func_080D2FB8 (src/080D2FB8.c). */
static inline u32 inlined_080D2FB8(u16 id)
{
    u16 relative = id - 0x150;

    if (relative <= 0x16) {
        return 1;
    }
    return 0;
}

/* Walks the item list, runs each eligible item's countdown according to its
 * metadata mode, and stores the items whose countdown reached zero, at most
 * `limit` of them; returns how many it stored. */
u32 func_080D1C94(Item **items, u32 limit, u8 advance)
{
    u32 count = 0;
    ItemNode *node;

    for (node = g_state_02000000.head; node != 0; node = node->next) {
        Item *item = node->item;
        const ItemMetadata *metadata;
        u32 expired;

        if (inlined_080D2FB8(item->id))
            continue;
        if (item->status != 0)
            continue;
        metadata = &g_table_0855AE4C[item->id];
        if (metadata->unknown_02_low != 0)
            continue;
        expired = 0;
        switch (metadata->mode) {
        case 1:
            if (advance != 0 && item->countdown != 0) {
                item->countdown--;
                if (item->countdown == 0)
                    expired = 1;
            }
            break;
        case 2:
            if (func_080C9540(0x45) && item->countdown != 0) {
                item->countdown--;
                if (item->countdown == 0)
                    expired = 1;
            }
            break;
        case 3:
            if (func_080C9540(0x45) && item->countdown != 0) {
                if (item->countdown <= g_state_02000000.counter_3C2B) {
                    item->countdown = 0;
                    expired = 1;
                } else {
                    item->countdown -= g_state_02000000.counter_3C2B;
                }
            }
            break;
        }
        if (expired) {
            *items++ = item;
            count++;
            if (count == limit)
                return count;
        }
    }
    return count;
}
