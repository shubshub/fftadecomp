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

/* 0x08138E80..0x08138EFC: 124 bytes, 53 instructions. */
void func_08138E80(RowSelection *selection)
{
    if (selection->previous_row != 0xFF) {
        func_0808B7C0(2, func_0808B8E4(2, 1, 1,
            selection->previous_row * 2 + 2),
            selection->previous_row * 22 + 0x1AB, 11, 0xC000);
    }
    func_0808B7C0(2, func_0808B8E4(2, 1, 1,
        selection->selected_row * 2 + 2),
        selection->selected_row * 22 + 0x1AB, 11, 0xB000);
}
