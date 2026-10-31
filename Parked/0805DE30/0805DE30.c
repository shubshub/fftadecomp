#include "ffta.h"

typedef struct {
    u8 identifier;
    u8 flags;
    u16 count;
} MenuEntry;

typedef struct {
    u8 unknown_00[4];
    u8 active[0];
} SlotFlags;

typedef struct {
    u8 unknown_0000[0x11A3];
    u8 selection;
    u8 unknown_11A4[6];
    u8 selected;
    u8 unknown_11AB[0x9D];
    MenuEntry *entries[130];
    SlotFlags *slot_flags;
} MenuState;

extern MenuState *data_0200F448;
extern void func_0805DDC8(u16 index);

/* Complete target [0x0805DE30, 0x0805DF94): 356 bytes,
 * 154 reached Thumb instructions, 44 literal bytes and 2 alignment bytes.
 * Target bytes:
 * f0b557464e464546e0b40004000c84461f48824601681f4a881804781e4bc818
 * 0078201880009e328918081807686346980009180d68d046002f63d07a886888
 * 824259d1697801200840002818d00023a34215dac146161c104a414608680d49
 * 40180478634508d04946086899008018401801684888b04212d00133a342f1db
 * 42461068044bc0180078fff785ff5ae048f40002aa110000a311000048120000
 * 48780124204348706978fe2008406870504602680d49561830780d4bd5182978
 * 43189b0099460b4bd21891446140401880001018006849460860307829784c40
 * 0019800012181760cae70000aa110000a311000048120000002078807978fe20
 * 0840787042461168124bc8180068124c0919043009784018297801701268d318
 * 186803784078032108400002184368800a4bd018007814192178401880000849
 * 52181218156038bc9846a146aa46f0bc01bc004750140000a3110000aa110000
 * 48120000
 */
void func_0805DE30(u16 index)
{
    MenuEntry *current = data_0200F448->entries[
        data_0200F448->selected + data_0200F448->selection];
    MenuEntry *chosen = data_0200F448->entries[index];
    int i;

    if (current != 0) {
        if (current->count == chosen->count) {
            if (chosen->flags & 1) {
                for (i = 0; i < data_0200F448->selected; i++) {
                    if (i != index &&
                        data_0200F448->entries[i]->count == current->count) {
                        data_0200F448->entries[i]->flags |= 1;
                        chosen->flags &= ~1;
                        data_0200F448->entries[
                            data_0200F448->selected + data_0200F448->selection] =
                            data_0200F448->entries[
                                data_0200F448->selected +
                                (data_0200F448->selection ^ 1)];
                        data_0200F448->entries[
                            data_0200F448->selected +
                            (data_0200F448->selection ^ 1)] = current;
                        break;
                    }
                }
            }
            func_0805DDC8(data_0200F448->selection);
            return;
        }
        current->count = 0;
        current->flags &= ~1;
    }

    data_0200F448->slot_flags->active[data_0200F448->selection] =
        chosen->identifier;
    chosen->count = data_0200F448->slot_flags->unknown_00[0] |
        ((data_0200F448->slot_flags->unknown_00[1] & 3) << 8);
    data_0200F448->entries[
        data_0200F448->selected + data_0200F448->selection] = chosen;
}
