#include "ffta.h"

/* Complete target: [0x08037C84, 0x08037DF0), 364 bytes, 159 instructions.
 * f0b557464e464546e0b486b00f9c05944b4e3568cc24071c6743b9464d444c20
 * 141c44430094474ea419a24628275744bc463878962424012d192870404d2868
 * 48442926b24457463c783f4d401904703b4e366801963d4ff01948443c4c0460
 * 07357619b046c844364d1c35009e7519674638780e9e041c7443640028680019
 * 5b00c0184746386001984844029064462078304e029dae193070294f38684844
 * 55462c782c4e801904703d682b4fe8194844274c04600736ae194e44b0462148
 * 1830009f3e18644620780e9f041c7c43640030680019c018434618604d44204c
 * 281902801f4ea819002707801e4aa8180023038002342d196e46367d2e70104f
 * 38680a3280184844016010a80078087238688018484402680120119901401191
 * 517a022040420840119b1843507206b038bc9846a146aa46f0bc01bc00470000
 * 10280003e009000361090000640900000080000678090000790900007c090000
 * 840900008c09000092090000
 */

typedef struct {
    u8 unknown_00[0x18];
    u16 *first_plane;
    u16 *second_plane;
    u8 unknown_20[8];
    u8 width;
    u8 height;
    u8 unknown_2A[0x22];
} Renderer;

typedef struct {
    u8 unknown_00[8];
    u8 kind;
    u8 enabled : 1;
} TransferResource;

typedef struct {
    u8 unknown_00[0x0C];
    u8 first_width;
    u8 first_height;
    u8 unknown_0E[2];
    u16 *first_destination;
    u16 *first_source;
    u8 unknown_18[0x0C];
    u8 second_width;
    u8 second_height;
    u8 unknown_26[2];
    u16 *second_destination;
    u16 *second_source;
    u16 renderer;
    u8 mode;
    u8 unknown_33[5];
    u16 field_38;
    u8 unknown_3A[4];
    u16 field_3E;
    u8 unknown_40[8];
    TransferResource *resource;
    u8 unknown_4C[0x80];
} TransferSlot;

typedef struct {
    u8 unknown_0000[0x954];
    TransferSlot slots[1];
} TransferState;

extern TransferState *g_state_03002810;
extern Renderer data_030009E0[];
extern u16 data_06008000[];

void func_08037C84(u32 slot, TransferResource *resource, u32 renderer, u32 column,
                   u32 row, u8 mode, u32 kind, u32 enabled)
{
    g_state_03002810->slots[slot].first_width = data_030009E0[renderer].width;
    g_state_03002810->slots[slot].first_height = data_030009E0[renderer].height;
    g_state_03002810->slots[slot].first_destination = data_06008000;
    g_state_03002810->slots[slot].first_source =
        data_030009E0[renderer].second_plane + data_030009E0[renderer].width * row + column;
    g_state_03002810->slots[slot].second_width = data_030009E0[renderer].width;
    g_state_03002810->slots[slot].second_height = data_030009E0[renderer].height;
    g_state_03002810->slots[slot].second_destination = data_06008000;
    g_state_03002810->slots[slot].second_source =
        data_030009E0[renderer].first_plane + data_030009E0[renderer].width * row + column;
    g_state_03002810->slots[slot].renderer = renderer;
    g_state_03002810->slots[slot].field_38 = 0;
    g_state_03002810->slots[slot].field_3E = 0;
    g_state_03002810->slots[slot].mode = mode;
    g_state_03002810->slots[slot].resource = resource;
    g_state_03002810->slots[slot].resource->kind = kind;
    g_state_03002810->slots[slot].resource->enabled = enabled;
}
