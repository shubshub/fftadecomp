#include "ffta.h"

/* Complete target: [0x080CEF78, 0x080CF060), 232 bytes, 104 instructions,
 * four literal words in three pools.
 * f0b50006060e09040f0c0548054940180068002861d0002e43d0041c05e0000000000002c828
 * 0000a468a0680028fbd16068002851d022689078c006400fb8422ad1012e1ed1117850780325
 * 284000020843fff77fff002814d1206801784078284000020843064940180004000c00211628
 * 00d8012100290ed1201c2ee00000b0feffff022e07d12068027840780321084000021043e6e7
 * 646860680028cad11be0041c16e021688878c006400fb8420fd1087849780322114009020143
 * 094809180904090c0020162900d801200028d3d0a468a0680028e5d10020f0bc02bc08470000
 * b0feffff
 */

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

typedef struct {
    u8 unknown_00[0x28C8];
    ItemNode *head;
} ItemListState;

extern ItemListState g_state_02000000;
extern u32 func_080CEECC(u16 index);

/* An inlined copy of func_080D2FB8 (src/080D2FB8.c). */
static inline u32 inlined_080D2FB8(u16 id)
{
    u16 relative = id - 0x150;

    if (relative <= 0x16) {
        return 1;
    }
    return 0;
}

ItemNode *func_080CEF78(u8 mode, u16 status)
{
    ItemNode *head = g_state_02000000.head;
    ItemNode *node;

    if (head == 0)
        return 0;
    if (mode != 0) {
        for (node = head; node->next != 0; node = node->next)
            ;
        for (; node->previous != 0; node = node->previous) {
            if (node->item->status == status) {
                if (mode == 1 && func_080CEECC(node->item->id) == 0) {
                    if (!inlined_080D2FB8(node->item->id))
                        return node;
                } else if (mode == 2) {
                    if (!inlined_080D2FB8(node->item->id))
                        return node;
                }
            }
        }
    } else {
        for (node = head; node->next != 0; node = node->next) {
            if (node->item->status == status) {
                if (!inlined_080D2FB8(node->item->id))
                    return node;
            }
        }
    }
    return 0;
}
