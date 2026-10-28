typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

typedef struct {
    u8 unknown_00[0x14];
    void *first_resource;
    void *second_resource;
} SceneResources;

typedef struct {
    u8 unknown_000[0x131];
    u8 mode;
    u8 unknown_132[12];
    u16 tile_index;
    u8 unknown_140[0x24];
    u8 width;
    u8 height;
    u8 unknown_166[18];
    u8 first_enabled;
    u8 second_enabled;
    u8 first_margin;
    u8 second_margin;
} RendererState;

extern RendererState data_030009E0;
extern u8 *data_03002740[];
extern SceneResources *data_03002818;

extern void func_0808A268(u32, u32, void *, void *, u8 *, u8 *,
                         u32, u32, u32, u32, u32, u32,
                         u32, u32, u32, u32, u32, u32);
extern u16 *func_0808B8E4(u32, u32, s32, s32);
extern void func_0808B7C0(s32, u16 *, u16, u16, u16);

/* Target: 0x08074CE8..0x08074DC4, 220 bytes including literal pools. */
void func_08074CE8(u32 width)
{
    s32 row;

    func_0808A268(4, 12,
                 data_03002818->second_resource,
                 data_03002818->first_resource,
                 data_03002740[4], data_03002740[4] + 0x16c,
                 0, 0, 16, 6, 14, 13, 16, 6, 14, 13, 14, 13);

    data_030009E0.width = width;
    data_030009E0.height = 6;
    data_030009E0.tile_index = 0x1a7;
    data_030009E0.mode = 0;
    data_030009E0.first_enabled = 1;
    data_030009E0.second_enabled = 1;
    data_030009E0.first_margin = 13;
    data_030009E0.second_margin = 10;

    for (row = 0; row < 10; row += 2) {
        func_0808B7C0(4, func_0808B8E4(4, 1, 1, row + 2),
                      0x1a7 + 13 * row, 13, 0xc000);
    }
}
