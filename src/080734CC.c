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
    u8 unknown_000[0xe5];
    u8 mode;
    u8 unknown_0e6[12];
    u16 tile_index;
    u8 unknown_0f4[8];
    u16 *first_plane;
    u16 *second_plane;
    u8 unknown_104[8];
    u8 stride;
    u8 rows;
    u8 unknown_10e[10];
    u8 width;
    u8 height;
    u8 unknown_11a[18];
    u8 first_enabled;
    u8 second_enabled;
    u8 first_margin;
    u8 second_margin;
} RendererState;

extern u8 data_02003CB0[];
extern RendererState data_030009E0;
extern u8 *data_03002740[];
extern SceneResources *data_03002818;

extern void func_0808A268(u32, u32, void *, void *, u8 *, u8 *,
                         u32, u32, u32, u32, u32, u32,
                         u32, u32, u32, u32, u32, u32);
extern void func_08016344(u16 *, u32, u32, u32, u32, u32, u32);
extern void func_08016560(u16 *, u32, u32, u32, u32, u32, u32);
extern u16 *func_0808B8E4(u32, u32, s32, s32);
extern u32 func_08018524(const u8 *, u32, u32);
extern void func_08035678(u16, u16 *, u32, u16);

/* Target: 0x080734CC..0x080735E0, 276 bytes including literal pools. */
void func_080734CC(void)
{
    const u8 *text = data_02003CB0;

    func_0808A268(3, 12,
                 data_03002818->second_resource,
                 data_03002818->first_resource,
                 data_03002740[3], data_03002740[3] + 0x90,
                 0, 0, 11, 3, 8, 9, 11, 3, 8, 9, 8, 9);

    data_030009E0.width = 11;
    data_030009E0.height = 3;
    data_030009E0.tile_index = 0x177;
    data_030009E0.mode = 0;
    data_030009E0.first_enabled = 1;
    data_030009E0.second_enabled = 1;
    data_030009E0.first_margin = 6;
    data_030009E0.second_margin = 6;

    func_08016344(data_030009E0.second_plane,
                  data_030009E0.stride, data_030009E0.rows, 0xc0,
                  data_030009E0.stride, 5, 12);
    func_08016560(data_030009E0.first_plane, 8, 9, 0xc0, 8, 1, 12);

    func_08035678(0xc03e, func_0808B8E4(3, 1, 1, 1),
                  func_08018524(text, 0x3e, 3), 1);
}
