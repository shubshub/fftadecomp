/* Target: 0x0800B0AC, 144 bytes. */
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;

typedef struct {
    u8 unknown_00[8];
    u8 type;
    u8 unknown_09[15];
    s16 screen_x;
    s16 screen_y;
    u8 id;
    u8 unknown_1d;
    s16 center_x;
    s16 center_y;
    u8 unknown_22[6];
} Record;

typedef struct {
    int x, y;
    s16 screen_x, screen_y;
    s16 scale_x, scale_y;
    u16 angle;
} AffineSource;

typedef struct {
    s16 pa, pb, pc, pd;
    int x, y;
} AffineDestination;

extern Record g_records_02009000[];
extern void func_08141864(const AffineSource *, AffineDestination *, int);
extern void func_080032F8(const AffineDestination *, u8);
extern void func_08003508(s16, u8);
extern void func_08003558(s16, u8);

void func_0800B0AC(u8 index)
{
    AffineSource source;
    AffineDestination destination;
    Record *record = &g_records_02009000[index];
    int x = record->center_x;
    int y = record->center_y;
    u8 id;
    u8 type;

    x -= record->screen_x;
    y -= record->screen_y;
    id = record->id;
    type = record->type;

    if (id != 0xff) {
        if (type == 1) {
            source.x = record->center_x << 8;
            source.y = record->center_y << 8;
            source.screen_x = record->screen_x;
            source.screen_y = record->screen_y;
            source.scale_x = 0x100;
            source.scale_y = 0x100;
            source.angle = 0;
            func_08141864(&source, &destination, 1);
            func_080032F8(&destination, id);
        } else {
            func_08003508(x, id);
            func_08003558(y, id);
        }
    }
}
