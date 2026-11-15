#include "ffta.h"

typedef struct __attribute__((packed)) {
    u16 id : 10;
    u16 unknown_0A : 6;
    u8 unknown_02[6];
    u16 identifiers[2];
} SelectedResource;

typedef struct {
    SelectedResource *current;
} ResourceSelection;

extern ResourceSelection g_state_020020D0;
extern const u8 *const g_table_08526680[];
extern const u8 *const g_table_085567F0[];
extern u32 func_080CE4DC(u16 id, u8 field);
extern s32 func_080CA7A4(u16 entry, u8 selector);
extern u16 func_08018C24(u8 *destination, const u8 *text);

/* Complete target: [0x080194E4, 0x08019574), 144 bytes, 58 instructions.
 * Target bytes:
 * 70b5061c0906090e03480468822905d100253d2304e00000d020000201253e23
 * 227860780321084000021043191cb4f0e3ff002806d00248983001681ee00000
 * f067550868002018017a407a02020a43002a01d100210de00348824206d8101c
 * 0021b1f02df903e077010000101c7b300004010c0548890009180968301cfff7
 * 5ffb002070bc02bc0847000080665208
 */
u32 func_080194E4(u8 *destination, u8 field)
{
    SelectedResource *record = g_state_020020D0.current;
    u32 index;
    u32 property;
    u16 identifier;
    u16 text_index;

    if (field == 0x82) {
        index = 0;
        property = 0x3D;
    } else {
        index = 1;
        property = 0x3E;
    }

    if (func_080CE4DC(record->id, property)) {
        func_08018C24(destination, g_table_085567F0[0x26]);
        return 0;
    }

    identifier = record->identifiers[index];
    if (identifier == 0)
        text_index = 0;
    else if (identifier <= 0x177)
        text_index = func_080CA7A4(identifier, 0);
    else
        text_index = identifier + 0x7B;
    func_08018C24(destination, g_table_08526680[text_index]);
    return 0;
}
