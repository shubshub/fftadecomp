/* 0x081401C0 .. 0x08140310, 336 bytes, 157 instructions.
 * Target bytes:
 * f0b54f464646c0b487b0061cf220400031180a889146002a02d0012a03d089e00120088086e0f020
 * 4000801980460178007800060016052803dc481c414608703be0404ab718002038560b2835dc051c
 * c2f6f8fa00040014412102f099fb041c5834240424140020385600020c2102f043fa0006000ea900
 * 4919c900891980229200086124028c60a020c001c8600c6048608a61052048610022484608770021
 * 795688004018c0003018f021c901016038780130387041460a700022914621497018007800060016
 * 814533da0025341d371ca846207e00281fd020681a4a80182060381cc7f614fc207e002815d0301c
 * 0830404401680912301c0c30404402681212009501200190029503950495059506950e480023c1f6
 * 2dfe283428372820804401218944074ab0180078000600168145cfdb012007b018bc9846a146f0bc
 * 02bc0847e101000000feffff24933a08
 */
#include "ffta.h"

typedef struct {
    s32 target_x;
    s32 target_y;
    s32 current_x;
    s32 current_y;
    s32 angle;
    s32 turn_percent;
    s32 speed;
} MotionState;

typedef struct {
    MotionState motion;
    u8 active;
    u8 unknown_1d[11];
} MotionRecord;

typedef struct {
    MotionRecord records[12];
    s8 timer;
    s8 count;
    u8 unknown_1e2[2];
    u16 phase;
} State081401C0;

extern const u8 data_083A9324[];
extern u32 func_08002804(void);
extern s32 func_08142950(s32 dividend, s32 divisor);
extern s32 func_081426B8(s32 dividend, s32 divisor);
extern void func_08007AD0(MotionState *state);
extern void func_08001F34(const void *source, s32 x, s32 y, u8 variant,
                          u8 flip_x, u8 flip_y, u8 flag_28, u8 flag_29,
                          u32 value, u8 mode, const void *transform);

/* Places a record at pixel (x, y) heading along angle, with its target on
 * itself.  The record argument is formed after both calls (0x08140236 ..
 * 0x0814023C), the speed argument is materialised before the first store
 * (0x0814023E, stored at 0x08140252), and x and angle narrow to s16 and u8
 * at the argument (0x08140222, 0x08140232). */
static inline void record_init(MotionRecord *record, s16 x, s16 y, u8 angle,
                               s32 speed)
{
    record->motion.angle = angle;
    record->motion.current_x = x << 8;
    record->motion.current_y = y << 8;
    record->motion.target_x = x << 8;
    record->motion.target_y = y << 8;
    record->motion.speed = speed;
    record->motion.turn_percent = 5;
    record->active = 1;
}

s32 func_081401C0(State081401C0 *state)
{
    s32 index;

    switch (state->phase) {
    case 0:
        state->phase = 1;
        break;
    case 1:
        if (state->timer <= 5) {
            state->timer++;
        } else if (state->count <= 11) {
            record_init(&state->records[state->count],
                        func_08142950((s16)func_08002804(), 65) + 88, 0x50,
                        func_081426B8(state->count << 8, 12), 512);
            state->records[state->count].motion.target_x = 0x7800;
            state->count++;
            state->timer = 0;
        }

        for (index = 0; index < state->count; index++) {
            MotionRecord *record = &state->records[index];

            if (record->active) {
                record->motion.target_y -= 512;
                func_08007AD0(&record->motion);
                if (record->active) {
                    func_08001F34(data_083A9324,
                                  state->records[index].motion.current_x >> 8,
                                  state->records[index].motion.current_y >> 8,
                                  0, 0, 1, 0, 0, 0, 0, 0);
                }
            }
        }
        break;
    }
    return 1;
}
