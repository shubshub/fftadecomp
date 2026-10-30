#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u8 unknown_18;
    u8 unknown_19[7];
} Record080CC788;

extern const Record080CC788 g_table_0851D180[];
extern u16 data_02001F30[];
extern u32 func_08002804(void);

/* Complete target: [0x080CC788, 0x080CC7CC), 68 bytes.
 * Target bytes: f0b500210d4e0e4f48004d1cc41936f735f800040014bc21490076f0d5f80004010c48018019007e0028f0d021802806010e0429e8d9f0bc01bc004780d15108301f0002
 */
void func_080CC788(void)
{
    u8 index;

    for (index = 0; index < 5; index++) {
        u16 value;

        do {
            value = (s16)func_08002804() % 0x178;
        } while (g_table_0851D180[value].unknown_18 == 0);
        data_02001F30[index] = value;
    }
}
