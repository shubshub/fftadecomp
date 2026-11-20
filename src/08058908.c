/* 0x08058908..0x08058C0C, 772 bytes and 321 reachable Thumb instructions.
 * Target bytes:
 * f0b557464e464546e0b40006060e0904090c1206170e2e488246320191462d48504414182078
 * 632800d81ce100252a4a88180004030c2949d800c01a40184279520980791f210840c0001043
 * 632808d91906090e301c73f033fd0006000e051c7d43092d00d81fe11d4c2068de2252018018
 * 18210422d1f7abf92068194940189b21d2f7e3fd281c0a21eaf08df80004000c804648465044
 * 134a85182b7819090132841820787f27384002010a43404611180e4881421bdd0f2018407021
 * 0843287021788020404208403e2108431fe0000000027f2e000096feffff248c520828f40002
 * 14140000822e0000e703000042441204110c0f2001400901184008432870120d3a4021788020
 * 4042084010432070134b3401e018124947183d78ea09114e3618b4463178490011430f4a8618
 * 307803229146104042020a43404611180b48a246814215dd802028433870f320614608703178
 * f7380840012108431ee000000002832e0000842e0000852e0000e703000042441204110c0120
 * 0140c9017f20284008433870500c61460870520e484602403178042040420840104330700e48
 * 50440e4945182b7899080d4a841820781f26304082010a43404611180a48814213dd03201840
 * 9c210843287021782020404208400f21084318e000000002852e0000862e0000e70300004244
 * 1204110c3f20014089000320184008432870920d32402178202040420840104320700a485044
 * 0a49441823785909094a85182878c2000a4346469119074881420ddde020184320707c202870
 * 58e000000002862e0000872e0000e703000042441204110c0720014049011f20184008432070
 * d20c2a7043e0301c3a1c73f0e9fb0004010c207840182070002913d1074c2068de2149014018
 * 0c210422d1f7a1f82068034a80189d21d2f7d9fc28e028f4000214140000132913d8074c2068
 * de267601801920210422d1f78bf82068034940189c21d2f7c3fc12e028f40002141400000a4c
 * 2068de225201801818210422d1f777f82068064e80199b21d2f7affc38bc9846a146aa46f0bc
 * 01bc004728f4000214140000
 */
#include "ffta.h"

typedef struct {
    u16 field_00 : 5;
    u16 field_05 : 5;
    u16 field_0A : 5;
    u16 field_0F : 5;
    u16 field_14 : 5;
    u16 field_19 : 5;
    u16 field_1E : 5;
    u16 field_23 : 5;
    u16 field_28 : 5;
    u16 limit : 8;
    u16 unknown_35 : 3;
} __attribute__((packed)) ProgressionInfo;

typedef struct {
    u32 name;
    u8 unknown_04;
    u8 appearance;
    u16 field_06 : 8;
    u16 level : 8;
    u16 health : 10;
    u16 magic : 10;
    u16 attack : 11;
    u16 defense : 11;
    u16 power : 11;
    u16 resistance : 11;
} __attribute__((packed)) ProgressionRecord;

typedef struct {
    u8 unknown_0000[0x2E78];
    ProgressionRecord records[20];
} ProgressionState;

typedef struct {
    u8 unknown_00[0x7C];
    void *item;
    void *context;
    u8 unknown_84[0x1001];
    u8 field_1085;
    u8 field_1086;
    u8 unknown_1087;
    u8 field_1088;
} State08029CD8;

typedef struct {
    u8 unknown_000[0x79A];
    u8 value;
} State0802B554;

typedef struct {
    u8 unknown_0000[0x1414];
    State0802B554 message;
    u8 unknown_1BB0[0x1BC0 - 0x1414 - sizeof(State0802B554)];
    State08029CD8 control;
} MenuState;

extern ProgressionState g_state_02000000;
extern const ProgressionInfo data_08528C24[];
extern MenuState *data_0200F428;
extern void func_08029CD8(State08029CD8 *state, u8 first, u8 second);
extern void func_0802B554(State0802B554 *state, u8 value);
extern u16 func_080CC348(u8 category, u16 id, u8 count);
extern u32 func_080CC3C8(u8 category, u8 index);

static inline void show_message(u8 style, u8 message)
{
    func_08029CD8(&data_0200F428->control, style, 4);
    func_0802B554(&data_0200F428->message, message);
}

void func_08058908(u8 category, u16 id, u8 count)
{
    if (g_state_02000000.records[category].level > 99) {
        u32 gain = 0;
        u16 index = id - 0x16A;

        if (data_08528C24[index].limit > 99)
            gain = (u8)func_080CC3C8(category, index) * count;
        if (gain < 10) {
            show_message(32, 0x9C);
        } else {
            u16 increase;
            show_message(24, 0x9B);
            increase = gain / 10;
            if (g_state_02000000.records[category].attack + increase > 999)
                g_state_02000000.records[category].attack = 999;
            else
                g_state_02000000.records[category].attack += increase;
            if (g_state_02000000.records[category].defense + increase > 999)
                g_state_02000000.records[category].defense = 999;
            else
                g_state_02000000.records[category].defense += increase;
            if (g_state_02000000.records[category].power + increase > 999)
                g_state_02000000.records[category].power = 999;
            else
                g_state_02000000.records[category].power += increase;
            if (g_state_02000000.records[category].resistance + increase > 999)
                g_state_02000000.records[category].resistance = 999;
            else
                g_state_02000000.records[category].resistance += increase;
        }
    } else {
        u16 gain = func_080CC348(category, id, count);
        g_state_02000000.records[category].level += gain;
        if (!gain)
            show_message(12, 0x9D);
        else if (gain < 20)
            show_message(32, 0x9C);
        else
            show_message(24, 0x9B);
    }
}
