#include "ffta.h"

/* Complete target: [0x0812C170, 0x0812C2B8), 328 bytes, 130 instructions,
 * fourteen literal words in three pools.
 * f0b54f464646c0b481b0174f362001213a1c9df743fa797c012000220843787412483918
 * 062008701149781802701148114c124ab918a72212010368201c16f04ff80022e520c000
 * 001981460c49091988460c4990004018046849460868002816d1561c53e00000b03c0002
 * 6a1f00006b1f0000bcd43608a0210002a021000060deffff10843a08141c10e00c1c20e0
 * 031c561c03251a6811785078284000020843a042f0d09b68002bf4d10024002c2dd04546
 * 281c211cfff702ff00220a4829180868a042e1d001320c313f2af8dd0024002c1bd06068
 * 002807d0a168816000290ad0486008e0c8250000a168002900d048600f4aa81801606946
 * 00200880216868460c4a15f0f9fa00202060321c062a9edd094b0a4978180a49a7221201
 * 1b6815f0ddff01b018bc9846a146f0bc01bc0047c828000008000001bcd43608a0210000
 * a0210002
 *
 * Copies the 0xA70-byte item block of the backup at 0x02003CB0 (the snapshot
 * src/080649A4.c takes of g_state_02000000) into the live state, removes the
 * seven items listed at data_083A8410 from it, and copies the block back.
 */

/* Declared as src/080D0ED4.c declares it. */
typedef struct {
    u16 id : 10;
    u16 unknown_0A : 6;
    u8 unknown_flags_low : 2;
    u8 status : 3;
    u8 unknown_flags_high : 3;
    u8 unknown_03;
    u8 unknown_04[12];
} __attribute__((packed)) Item;

typedef struct ItemNode {
    Item *item;
    struct ItemNode *previous;
    struct ItemNode *next;
} ItemNode;

/* The 0xA70 bytes at 0x21A0 that both copies move as one block; the nodes at
 * 0x25C8 and the head at 0x28C8 are where src/080D0ED4.c finds them. */
typedef struct {
    u8 unknown_000[0x428];
    ItemNode nodes[64];
    ItemNode *head;
    u8 unknown_72C[0xA70 - 0x72C];
} Inventory;

typedef struct {
    u8 unknown_0000[0x11];
    u8 unknown_11;
    u8 unknown_0012[0x1F6A - 0x12];
    u8 field_1f6a;
    u8 field_1f6b;
    u8 unknown_1F6C[0x21A0 - 0x1F6C];
    Inventory inventory;
} GameState;

typedef void (*BufferCopier)(void *destination, const void *source, u32 size);

extern GameState g_state_02000000;
extern GameState data_02003CB0;
extern BufferCopier data_0836D4BC[];
extern const u32 data_083A8410[];
extern void func_080C960C(u16 bit_index, u16 enabled, void *base);
extern void func_0812C030(GameState *state, Item *item);
extern void func_0814186C(const void *source, void *destination, u32 control);

/* An inlined copy of func_0812C530 (src/0812C530.c): 0x0812C200-0x0812C21C
 * is that function's 0x0812C548-0x0812C562 in other registers, with the
 * outer loop's i + 1 at 0x0812C202. */
static inline Item *find_item(const GameState *state, u32 id)
{
    ItemNode *head = state->inventory.head;
    ItemNode *node;

    if (head == 0)
        return 0;
    for (node = head; node != 0; node = node->next) {
        Item *item = node->item;

        if (item->id == id)
            return item;
    }
    return 0;
}

/* The node search of func_080D0ED4 (src/080D0ED4.c), on a state passed by
 * pointer as func_0812C030 (src/0812C030.c) takes it. */
static inline ItemNode *find_node(GameState *state, Item *item)
{
    ItemNode *node;
    s32 i;

    for (i = 0, node = state->inventory.nodes; i < 64; i++, node++) {
        if (node->item == item)
            return node;
    }
    return 0;
}

/* The removal of func_080D0ED4 (src/080D0ED4.c) on a state passed by pointer.
 * The ROM copies the state into a register of its own for it (0x0812C222)
 * and addresses the nodes (0x0812C230) and the head (0x0812C266) from that
 * copy.  The fill word is written through a pointer, as src/08029DD4.c
 * does for the same 0x01000008 CpuSet and src/0808AAF0.c does at each of
 * its fills: its address is formed (0x0812C26A) before the zero. */
static inline void remove_item(GameState *state, Item *item)
{
    ItemNode *node;

    func_0812C030(state, item);
    node = find_node(state, item);
    if (node != 0) {
        ItemNode *previous = node->previous;
        ItemNode *next;
        u16 clear;
        u16 *fill;

        if (previous != 0) {
            next = node->next;
            previous->next = next;
            if (next != 0)
                next->previous = previous;
        } else {
            next = node->next;
            if (next != 0)
                next->previous = previous;
            state->inventory.head = next;
        }
        fill = &clear;
        *fill = 0;
        func_0814186C(fill, node->item, 0x01000008);
        node->item = 0;
    }
}

void func_0812C170(void)
{
    GameState *backup = &data_02003CB0;
    s32 i;

    func_080C960C(0x36, 1, backup);
    backup->unknown_11 |= 1;
    backup->field_1f6a = 6;
    backup->field_1f6b = 0;
    data_0836D4BC[0](&g_state_02000000.inventory, &backup->inventory,
                     sizeof(Inventory));
    for (i = 0; i < 7; i++) {
        Item *item = find_item(&g_state_02000000, data_083A8410[i]);

        if (item != 0)
            remove_item(&g_state_02000000, item);
    }
    data_0836D4BC[0](&backup->inventory, &g_state_02000000.inventory,
                     sizeof(Inventory));
}
