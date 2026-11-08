#include "ffta.h"

typedef struct TransferRecord TransferRecord;
typedef void (*BufferCopier)(void *destination, const void *source, u32 size);
typedef void (*BufferInitializer)(void *destination, u32 size);

typedef struct {
    u8 unknown_000[2];
    u16 base;
    u8 unknown_004[3];
    u8 rows;
    u8 unknown_008[0x460];
    u16 x;
    u16 y;
} Panel0802EC24;

extern u8 data_02005D30[2][0x300];
extern Panel0802EC24 *data_0200F444;
extern BufferCopier data_0836D4BC[];
extern BufferInitializer g_callbacks_0836D4B8[];
extern const u8 *func_080CB4E0(u32 identifier);
extern void func_08015110(void *context, void *destination, const u8 *text,
                          u32 mode, u32 reset);
extern void func_0802EAE0(u8 *destination, const u8 *source);
extern TransferRecord *func_0802DFCC(void);
extern void func_08000ADC(TransferRecord *entry, const void *source,
                          void *destination, u16 words);
extern const u8 *func_080CBABC(u32 index);

/* Complete [0x0802EC24, 0x0802ECEC): 200 bytes.
 * 70b5464640b481b0041c2406240e1e4dc02080002e181d48c02189000268281c13f102fb
 * 201c9cf049fc021c184988460868103001210091291c0023e6f756fa301c291cfff73aff
 * fff7aef9114a311cc023d1f731ff104c104d15209cf01cff011c2368281c202213f1e0fa
 * 43461a688d20c00011180a480880d079002811d15088023013e00000305d0002b8d43608
 * 44f40002805c0106bcd43608803b000398ff0000d0790130400051884018c000044bd118
 * 088001b008bc984670bc01bc004700006a040000
 */
void func_0802EC24(u8 identifier)
{
    u8 *text = data_02005D30[0];
    u8 *tiles = data_02005D30[1];
    Panel0802EC24 *panel;

    g_callbacks_0836D4B8[0](text, 0x300);
    func_08015110((u8 *)data_0200F444 + 0x10, text,
                  func_080CB4E0(identifier), 0, 1);
    func_0802EAE0(tiles, text);
    func_08000ADC(func_0802DFCC(), tiles, (void *)0x06015C80, 0xC0);
    data_0836D4BC[0]((void *)0x03003B80, func_080CBABC(0x15), 0x20);

    panel = data_0200F444;
    panel->x = 0xFF98;
    if (panel->rows == 0)
        panel->y = (panel->base + 2) * 8;
    else
        panel->y = ((panel->rows + 1) * 2 + panel->base) * 8;
}
