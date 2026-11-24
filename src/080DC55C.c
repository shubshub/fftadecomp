#include "ffta.h"

/* Complete [0x080DC55C, 0x080DCAD2): 1398 bytes, 617 instructions, with the
 * literal words data_0836D4BC, 0x151 (twice), 0x7FFF and the address of the
 * 22-entry jump table at 0x080DC99C.
 * f0b557464e464546e0b486b082460591151c0988012900d1a4e2012902dc002905d09fe2
 * 8020400081421dd09ae2059841680868e8600879a8714879e87188792872c8796872074a
 * 281c103089681368142265f04ffe0599888a6880c88aa88080e20000bcd4360801229146
 * 6888061c002e02d00138688074e21023e95e0120404281421fd02888814208da686a0028
 * 19d0fff735fa6862002814d011e081420fd1e8680068a97caa79eb792c7a00946c7a0194
 * 0296039654460494fff7acfa6862002081461422a95e01204042814200d134e128888142
 * 3edaa86a002800d12de1fff70dfaa862002802d00024a14625e1a9888020000208400028
 * 00d01ee1e8680321ccf7faf80006002820d00021aa8801201040002801d0ff210ae00220
 * 1040002801d0012104e004201040002800d00221e86800680022534603f026f9a862a988
 * 80221202101c0843a880f4e0e86801f03bfef2e0814200d0ede0ea8a1624295f03204042
 * 81422fd1e868006814210091002101915146029100210222032303f08bf8a862aa880023
 * 08201040002801d089210be010201040002801d08b2105e020201040002800d1c5e00649
 * 02201040002865d104200240002a00d00223002b69d16ce0510100000420404281421ad1
 * e86800680824009400210191524602920122032303f058f8a8620c2103f00af9aa880023
 * 101c20400028c9d1102010400028cbd1cce70520404281420ad10021aa88012010400028
 * 79d10220104000287bd17ce00220404281423fd1e868291c1031fff7a5fe000600160028
 * 33dde86800685346009301210522002301f062fca862aa88002308201040002801d08921
 * 0ae010201040002801d08b2104e02020104000285fd0034902201040002803d0012308e0
 * 5101000004200240002a00d00223002b03d0181c64f0bafe4be0081c64f08efe47e00028
 * 45dab0e7074c1440002601221621685e802109020840002806d00126052c0cd104e00000
 * ff7f0000082c06d1e868291c1031fff751fe0006020e10060016002809dde86800685246
 * 0092311c221c002301f00cfc1ae0002819da0021aa8801201040002801d0ff210ae00220
 * 1040002801d0012104e004201040002800d00221e86800680022534603f04cf8a8620023
 * 99461821695601204042814200d1f7e00026081c864200dbf2e07100281c1c3042180024
 * 115f01204042814200d1dfe0081c2988884210dab100281c2c3044182068002800d1d3e0
 * fff7bcf82060002800d1cde000229146cae0884200d0c5e0012398460027e9688a89281c
 * 193080190478012c16d0012c02dc002c03d028e01a2c16d025e0101c43461840002801d0
 * cf8b95e002200240002a00d190e00f8c01248de002200240002a00d188e00f8c86e0081c
 * 00f024fe0006002800d19fe0ea681c24105f002800dc99e0978b002476e0802020400028
 * 72d0081c0321cbf76fff0006002800d08ae07f200440201f152865d88000024940180068
 * 874600009cc90d08f4c90d08fac90d0800ca0d0806ca0d080cca0d0812ca0d0818ca0d08
 * 1eca0d0824ca0d0858ca0d0858ca0d0858ca0d0858ca0d0858ca0d082aca0d0858ca0d08
 * 58ca0d0858ca0d0830ca0d0858ca0d0836ca0d0846ca0d08e86823211fe0e86824211ce0
 * e868272119e0e868282116e0e868222113e0e868162110e0e86817210de0e86815210ae0
 * e868002107e0e8680c2104e0e868092101e0e868252100f019fe0006002809d128e0e868
 * 262100f011fe0006002801d100208046414600291cd0e86800683a041214a98800910021
 * 019153460293211c1e2300f099fbb200291c2c31891808600024a146701c0006060e1820
 * 2856864200da0ce7288801302880484600280dd0e868062100f0ecfd0006002803d0e868
 * 006801f06bfc022005990880002006b038bc9846a146aa46f0bc02bc0847
 */

/* The effect owner the spawners (src/080DCF64.c, src/080DCFE4.c,
 * src/080DD8C4.c) pass as their first value.  flags and the three values
 * are func_080DC4E0's (src/080DC4E0.c). */
typedef struct Object080DC55C {
    void *value;
    u8 unknown_04[8];
    u16 flags;
    u8 unknown_0e[14];
    s16 value_1c;
    s16 value_1e;
    s16 value_20;
} Object080DC55C;

/* The 20-byte script the spawners pass as their second value, copied into
 * the task: the frames that start two fixed effects and up to three
 * selected ones.  count and selectors are func_080DC4E0's
 * Selection080DC4E0. */
typedef struct EffectScript080DC55C {
    s16 frame;
    u8 effect;
    u8 unknown_03;
    s16 second_frame;
    s16 action;
    s8 count;
    u8 selectors[3];
    s16 frames[3];
    u8 unknown_12[2];
} EffectScript080DC55C;

/* The spawners' Parameters080DCF64. */
typedef struct Parameters080DC55C {
    Object080DC55C *object;
    u8 kind;
    u8 unknown_05;
    u8 unknown_06;
    u8 unknown_07;
    const EffectScript080DC55C *script;
} Parameters080DC55C;

/* The spawners' SchedulerDescriptor080DCF64 (first, second). */
typedef struct SchedulerDescriptor080DC55C {
    u16 state;
    u8 unknown_02[2];
    const Parameters080DC55C *parameters;
    u8 unknown_08[12];
    u16 delay;
    u16 flags;
    u8 unknown_18[4];
} SchedulerDescriptor080DC55C;

/* The task's own 0x38 bytes: a frame counter, the spawn parameters, the
 * script and the task of each effect it started. */
typedef struct Payload080DC55C {
    u16 frame;
    u16 delay;
    u16 flags;
    u8 kind;
    u8 unknown_07;
    u8 unknown_08;
    u8 unknown_09;
    u8 unknown_0a[2];
    Object080DC55C *object;
    EffectScript080DC55C script;
    void *first_task;
    void *second_task;
    void *tasks[3];
} Payload080DC55C;

typedef void (*BufferCopier)(void *destination, const void *source, u32 size);

extern BufferCopier data_0836D4BC[];

extern void *func_080DBA5C(void *task);
extern void *func_080DBB74(void *value, u8 kind, u8 index, u16 first,
                           u16 second, u16 third, u16 delay, u32 unused,
                           void *parent);
extern u8 func_080A8858(const Object080DC55C *object, u8 selector);
extern void *func_080DF8E8(void *value, u8 side, u32 first, void *parent);
extern void func_080DE328(Object080DC55C *object);
extern void *func_080DF7F8(void *value, u8 first, u8 second, u8 third,
                           u16 fourth, u16 fifth, void *parent);
extern void func_080DF964(void *task, u16 value);
extern void *func_080DF92C(void *value, u8 side, u16 first, void *parent);
extern s8 func_080DC4E0(const Object080DC55C *object,
                        const EffectScript080DC55C *script);
extern void *func_080DE074(void *value, u8 mode, u16 action, u16 delay,
                           void *parent);
extern u8 func_080DD598(const Object080DC55C *object);
extern u8 func_080DD670(const Object080DC55C *object, u8 index);
extern void *func_080DD1AC(void *value, u8 effect, s16 amount, u8 delay,
                           u16 flags, u16 timer, void *parent);
extern u8 func_080DD684(const Object080DC55C *object, u8 selector);
extern void func_080DE390(void *value);
extern void func_08141570(u32 player_id, u16 song_id);
extern void func_08141520(u16 song_id);

/* The sound of the -3, -4 and -2 actions: func_080D8DC0 (src/080D8DC0.c)
 * with the song picked by flag bits 3-5 instead of a fixed 0x8D.  The ROM
 * keeps three copies (0x080DC6E4, 0x080DC750, 0x080DC7B2, cross-jumped into
 * one another), each reading the flags before it clears the player. */
static inline void play_action_sound(u16 flags)
{
    u32 player = 0;
    u16 song;

    if (flags & 8)
        song = 0x89;
    else if (flags & 0x10)
        song = 0x8B;
    else if (flags & 0x20)
        song = 0x151;
    else
        return;
    if (flags & 2)
        player = 1;
    else if (flags & 4)
        player = 2;
    if (player != 0)
        func_08141570(player, song);
    else
        func_08141520(song);
}

u32 func_080DC55C(void *task, SchedulerDescriptor080DC55C *descriptor,
                  Payload080DC55C *payload)
{
    switch (descriptor->state) {
    case 0: {
        const Parameters080DC55C *parameters = descriptor->parameters;

        payload->object = parameters->object;
        payload->kind = parameters->kind;
        payload->unknown_07 = parameters->unknown_05;
        payload->unknown_08 = parameters->unknown_06;
        payload->unknown_09 = parameters->unknown_07;
        data_0836D4BC[0](&payload->script, parameters->script,
                         sizeof(payload->script));
        payload->delay = descriptor->delay;
        payload->flags = descriptor->flags;
        break;
    }
    case 1:
        break;
    case 0x100: {
        u8 done = 1;
        u8 i;

        if (payload->delay != 0) {
            payload->delay--;
            break;
        }

        if (payload->script.frame != -1) {
            if (payload->script.frame < payload->frame) {
                if (payload->first_task != 0) {
                    payload->first_task = func_080DBA5C(payload->first_task);
                    if (payload->first_task != 0)
                        done = 0;
                }
            } else {
                if (payload->script.frame == payload->frame)
                    payload->first_task = func_080DBB74(
                        payload->object->value, payload->script.effect,
                        payload->kind, payload->unknown_07,
                        payload->unknown_08, payload->unknown_09, 0, 0, task);
                done = 0;
            }
        }

        if (payload->script.second_frame != -1) {
            if (payload->script.second_frame < payload->frame) {
                if (payload->second_task != 0) {
                    payload->second_task = func_080DBA5C(payload->second_task);
                    if (payload->second_task != 0) {
                        done = 0;
                    } else if (!(payload->flags & 0x8000)) {
                        if (func_080A8858(payload->object, 3)) {
                            u8 side = 0;

                            if (payload->flags & 1)
                                side = 0xFF;
                            else if (payload->flags & 2)
                                side = 1;
                            else if (payload->flags & 4)
                                side = 2;
                            payload->second_task = func_080DF8E8(
                                payload->object->value, side, 0, task);
                            payload->flags |= 0x8000;
                            done = 0;
                        } else {
                            func_080DE328(payload->object);
                        }
                    }
                }
            } else {
                if (payload->script.second_frame == payload->frame) {
                    /* Negative actions are fixed effects; any other is an
                     * effect id with a mode flag in bit 15.  The ROM reads
                     * the halfword zero-extended for the id (0x080DC6BA,
                     * masked at 0x080DC80C) and signed for the tests
                     * (0x080DC6BE, 0x080DC816). */
                    if (payload->script.action == -3) {
                        payload->second_task = func_080DF7F8(
                            payload->object->value, 0, 2, 3, 0x14, 0, task);
                        play_action_sound(payload->flags);
                    } else if (payload->script.action == -4) {
                        payload->second_task = func_080DF7F8(
                            payload->object->value, 0, 1, 3, 8, 0, task);
                        func_080DF964(payload->second_task, 0xC);
                        play_action_sound(payload->flags);
                    } else if (payload->script.action == -5) {
                        u8 side = 0;

                        if (payload->flags & 1)
                            side = 0xFF;
                        else if (payload->flags & 2)
                            side = 1;
                        else if (payload->flags & 4)
                            side = 2;
                        payload->second_task = func_080DF92C(
                            payload->object->value, side, 0, task);
                    } else if (payload->script.action == -2) {
                        s8 result = func_080DC4E0(payload->object,
                                                  &payload->script);

                        if (result > 0) {
                            payload->second_task = func_080DE074(
                                payload->object->value, 1, 5, 0, task);
                            play_action_sound(payload->flags);
                        } else if (result < 0) {
                            u8 side = 0;

                            if (payload->flags & 1)
                                side = 0xFF;
                            else if (payload->flags & 2)
                                side = 1;
                            else if (payload->flags & 4)
                                side = 2;
                            payload->second_task = func_080DF92C(
                                payload->object->value, side, 0, task);
                        }
                    } else {
                        u16 id = payload->script.action & 0x7FFF;
                        u8 mode = 0;
                        s8 result = 1;

                        if (payload->script.action & 0x8000) {
                            mode = 1;
                            if (id == 5)
                                result = func_080DC4E0(payload->object,
                                                       &payload->script);
                        } else if (id == 8) {
                            result = func_080DC4E0(payload->object,
                                                   &payload->script);
                        }
                        if (result > 0) {
                            payload->second_task = func_080DE074(
                                payload->object->value, mode, id, 0, task);
                        } else if (result < 0) {
                            u8 side = 0;

                            if (payload->flags & 1)
                                side = 0xFF;
                            else if (payload->flags & 2)
                                side = 1;
                            else if (payload->flags & 4)
                                side = 2;
                            payload->second_task = func_080DF92C(
                                payload->object->value, side, 0, task);
                        }
                    }
                }
                done = 0;
            }
        }

        if (payload->script.count != -1) {
            for (i = 0; i < payload->script.count; i++) {
                if (payload->script.frames[i] == -1)
                    continue;
                if (payload->script.frames[i] < payload->frame) {
                    if (payload->tasks[i] != 0) {
                        payload->tasks[i] = func_080DBA5C(payload->tasks[i]);
                        if (payload->tasks[i] != 0)
                            done = 0;
                    }
                } else {
                    if (payload->script.frames[i] == payload->frame) {
                        u8 ok = 1;
                        s16 amount = 0;
                        u16 flags = payload->object->flags;
                        u8 effect = payload->script.selectors[i];

                        switch (effect) {
                        case 0:
                            if (flags & 1) {
                                amount = payload->object->value_1e;
                            } else if (flags & 2) {
                                amount = payload->object->value_20;
                                effect = 1;
                            }
                            break;
                        case 1:
                            if (flags & 2)
                                amount = payload->object->value_20;
                            break;
                        case 0x1A:
                            if (func_080DD598(payload->object)
                                && payload->object->value_1c > 0) {
                                amount = payload->object->value_1c;
                                effect = 0;
                            } else {
                                ok = 0;
                            }
                            break;
                        default:
                            if (!(effect & 0x80))
                                break;
                            if (func_080A8858(payload->object, 3)) {
                                ok = 0;
                                break;
                            }
                            effect &= 0x7F;
                            switch (effect) {
                            case 4:
                                if (!func_080DD670(payload->object, 0x23))
                                    ok = 0;
                                break;
                            case 5:
                                if (!func_080DD670(payload->object, 0x24))
                                    ok = 0;
                                break;
                            case 6:
                                if (!func_080DD670(payload->object, 0x27))
                                    ok = 0;
                                break;
                            case 7:
                                if (!func_080DD670(payload->object, 0x28))
                                    ok = 0;
                                break;
                            case 8:
                                if (!func_080DD670(payload->object, 0x22))
                                    ok = 0;
                                break;
                            case 9:
                                if (!func_080DD670(payload->object, 0x16))
                                    ok = 0;
                                break;
                            case 10:
                                if (!func_080DD670(payload->object, 0x17))
                                    ok = 0;
                                break;
                            case 11:
                                if (!func_080DD670(payload->object, 0x15))
                                    ok = 0;
                                break;
                            case 12:
                                if (!func_080DD670(payload->object, 0))
                                    ok = 0;
                                break;
                            case 18:
                                if (!func_080DD670(payload->object, 0xC))
                                    ok = 0;
                                break;
                            case 22:
                                if (!func_080DD670(payload->object, 9))
                                    ok = 0;
                                break;
                            case 24:
                                if (!func_080DD670(payload->object, 0x25))
                                    ok = 0;
                                break;
                            case 25:
                                if (!func_080DD670(payload->object, 0x26))
                                    ok = 0;
                                break;
                            }
                            break;
                        }
                        /* An effect that does not apply ends the loop, as
                         * the ROM does (beq to 0x080DCA98 at 0x080DCA5C):
                         * a later selector due on this frame is never
                         * started, later running ones are stepped a frame
                         * late, and this frame's done = 0 is skipped. */
                        if (!ok)
                            break;
                        payload->tasks[i] = func_080DD1AC(
                            payload->object->value, effect, amount, 0x1E,
                            payload->flags, 0, task);
                    }
                    done = 0;
                }
            }
        }

        payload->frame++;
        if (done) {
            if (func_080DD684(payload->object, 6))
                func_080DE390(payload->object->value);
            descriptor->state = 2;
        }
        break;
    }
    }
    return 0;
}
