typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u8 unknown_000[0x105];
    u8 selected_row;
    u8 previous_row;
} RowSelection;

extern u16 *func_0808B8E4(u32 index, u32 plane, int x, int y);
extern void func_0808B7C0(int index, u16 *destination, u16 tile,
                         u16 count, u16 flags);

/* 0x080774B4..0x080775A8: 244 bytes, 106 instructions. */
void func_080774B4(RowSelection *selection, int alternate)
{
    if (alternate == 0) {
        if (selection->previous_row != 0xFF) {
            func_0808B7C0(4, func_0808B8E4(4, 1, 3,
                selection->previous_row * 2 + 2),
                selection->previous_row * 26 + 0x1AB, 11, 0xC000);
        }
        func_0808B7C0(4, func_0808B8E4(4, 1, 3,
            selection->selected_row * 2 + 2),
            selection->selected_row * 26 + 0x1AB, 11, 0xB000);
    } else {
        if (selection->previous_row != 0xFF) {
            func_0808B7C0(4, func_0808B8E4(4, 1, 3,
                selection->previous_row * 2 + 4),
                (selection->previous_row * 2 + 2) * 13 + 0x1AB,
                11, 0xC000);
        }
        func_0808B7C0(4, func_0808B8E4(4, 1, 3,
            selection->selected_row * 2 + 4),
            (selection->selected_row * 2 + 2) * 13 + 0x1AB,
            11, 0xB000);
    }
}
