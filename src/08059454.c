#include "ffta.h"

/* Complete target: [0x08059454, 0x0805AAA8), 5716 bytes, 1696 instructions,
 * including the 256-entry jump table at 0x08059478 and the literal pools.
 * The unit list task of the menu context at data_0200F428: func_08058D40
 * installs it (state 254) and func_0805ADA4 returns to it (states 0x42 and
 * 0xFF).  It draws the unit list, pages it seven rows at a time, opens the
 * unit's detail screen (0xDC-0xDE) and a two-row options window (0x3E-0x47),
 * and hands back to func_08058D40 (0xFF) or func_0805ADA4 (0xFE).  The case
 * bodies reach the shared tails (0x0805AA34 `*state = *r0`, 0x0805AA82 byte
 * store, 0x0805AA84 exit) through agbcc's long same-function BL jumps.
 * f0b54f464646c0b484b00f1c3878ff2801d901f00dfb8000014940180068874678940508
 * 78980508f89805083499050884aa050884aa050884aa050884aa050884aa050884aa0508
 * 84aa050884aa050884aa050884aa050884aa050884aa050884aa050884aa050884aa0508
 * 84aa050884aa0508489905089899050898990508449b0508c09b050884aa050884aa0508
 * 84aa050884aa050884aa050884aa050884aa050884aa050884aa050884aa050884aa0508
 * 84aa050884aa050884aa050884aa0508e4a0050820a1050884aa050884aa05086ca10508
 * 98a1050800a2050884aa050884aa050884aa050884aa050884aa050884aa050884aa0508
 * 84aa050884aa050884aa050884aa050884aa050884aa05085ca20508c4a20508eca20508
 * 2ca3050864a4050808a5050824a505084ca5050878a50508b4a50508d0a505081ca60508
 * 84aa050884aa050884aa050884aa050884aa050884aa050884aa050884aa050830a60508
 * 4ca6050898a6050806a7050848a705086ca70508aca7050884aa050884aa050884aa0508
 * 84aa050884aa050884aa050884aa050884aa050884aa050884aa050884aa050884aa0508
 * 84aa0508d0a7050810a8050884aa050884aa050884aa050884aa050884aa050884aa0508
 * 84aa050884aa050884aa050884aa050884aa050884aa050884aa050884aa050884aa0508
 * 84aa050884aa050884aa050830a8050868a8050884aa050884aa050884aa050884aa0508
 * 84aa050884aa050884aa050884aa050884aa050884aa050884aa050884aa050884aa0508
 * 84aa050884aa050884aa050884aa050884aa050884aa050884aa050884aa050884aa0508
 * 84aa050884aa050884aa050884aa050884aa050884aa050884aa050884aa050884aa0508
 * 84aa050884aa050884aa050884aa050884aa050884aa050884aa050884aa050884aa0508
 * 84aa050884aa050884aa050884aa050884aa050884aa050884aa050884aa050884aa0508
 * 84aa050884aa050884aa050884aa050884aa050884aa050884aa050884aa050884aa0508
 * 90a8050884aa050884aa050884aa050884aa050884aa050884aa050884aa050884aa0508
 * 84aa050884aa050884aa050884aa050884aa050884aa050884aa050884aa050884aa0508
 * 84aa050884aa0508d8a8050884aa050884aa050884aa050884aa050884aa050884aa0508
 * 84aa050884aa050884aa050884aa050884aa050884aa050884aa050884aa050884aa0508
 * 84aa050884aa050884aa050884aa050804a90508aca9050824aa050884aa050884aa0508
 * 84aa050884aa050884aa050884aa050884aa050884aa050884aa050884aa050884aa0508
 * 84aa050884aa050884aa050884aa050884aa050884aa050884aa050884aa050884aa0508
 * 84aa050884aa050884aa050884aa050884aa050884aa050884aa050884aa050884aa0508
 * 84aa050884aa050848aa050868aa0508124d2868de21490140180421d0f74cfa28680f4a
 * 80180021017028680d4bc018017073f07bf90006002817d128680a4c00190421d1f746fe
 * 286800199221d1f74dfe0120387001f0e1f8000028f40002b41b0000b51b000014140000
 * 2868074c00190421d1f72efe286800199321d1f735fe0220387001f0c9f8000014140000
 * 0b4800680b4c0019d1f722fe0006000e052801d001f0baf80748418801200840002801d1
 * 01f0b2f8ff20387001f0aef828f40002141400000000000302480068024e801900f008ff
 * 28f40002141400000020002100220023d0f7b6fc0d4d28680d4c001911210091c0210191
 * 01210291022102220e23d0f745fc29680c1907480918201c0a220023d1f7f2fc15203870
 * 01f07cf828f40002f40c0000540b0000194989460868194a8018bdf7edfb0006002801d1
 * 01f06af8154c201c18210122d1f752fd4b461868104e85191149431821691148401a0028
 * 00da1f30c202120c281c191c1423bcf717fc4a461068d2231b01c218094c001901785183
 * 0678002080461d1c4de0000028f40002f40c0000b0080003680d000000c00006b51b0000
 * 0a4b30060215d118094e89190968061c00290fd0300e73f09bf84a4611684919221c0023
 * 02f0cafc22e0000000000002782e0000084958181018007800280dd0300e73f085f84a46
 * 11684919221c042302f0b4fc0ce000007c2e00002948983000684b4619684919221c0023
 * 02f0a6fc802464043019060e414608060019000e80464246100604164b4618684019bef7
 * 53f80004000c8442b2db1b4e3068d22424010019bef70cf83068184940181849184abcf7
 * 45f93168d4252d014819164a89180978bef768fa30680419401911214156201c0b22bef7
 * 01f810493068104bc018007800010f4c091940180078012102f0d8fc6420387030680b4e
 * 8019172100f0b3fff067550828f40002f40c0000817e0108057f0108b41b000000000002
 * b61b00007f2e0000a02c0000174c20681749421802211180164bc21816491160164e8219
 * 2433c11811600f60243682192821116012494218ff211160d42212018118d2231b01c018
 * 497c09060916bdf7efff21680b4a89180870206880180078fff722fc1820387000f070ff
 * 28f40002542c00004c2c0000d1920508502c0000782c0000b61b00000b4a518880204000
 * 0840002824d0094909480268094c1019007800014018084e8019006800280dd16b20e7f0
 * a9fc58e2000000030000000228f40002b61b0000782e00000349501818210170dc203870
 * 47e20000a02c000001200840002803d0381c00f087ff3ce2042008400004030c002b5dd0
 * 022002211a220623d0f740fb0b4e3068b9f7a4fb0a4935680a4aa818027810014018094b
 * c0180068002813d1074a084b281c2521bff710ff29e0000028f4000200000002b61b0000
 * 782e0000b008000390090003101c72f025ff041c2406240e3068104e8019007872f01cff
 * 011c0906090e201c00226ef061fc011c0a4809180904090c094a0a4b281cbff7e5fec820
 * 3870084800680849401818210170b4203870e4e1b61b000047020000b008000390090003
 * 28f40002d50c00001188802080000840002800d186e1918840200840002800d1ace0134d
 * 2a68134c11190878002823d1d42636019119487c002800d1bde1d22424011019497c0906
 * 0916ff22bdf7defe2868001900210b22bdf7d8fe286880190021bef731f9286880194021
 * b1e0000028f40002b51b000008780738002801da0b7000e0087003a900200880114d2868
 * 114a81180968114bc2181278104c0019007880004243520880204004024303a8e7f068fd
 * 2868163c0019d1f7b1f928680219084e801901785183067800208046271c45e028f40002
 * 2c0d0000350d0000360d0000b51b0000094b30060215d118084e89190968061c00290dd0
 * 300e72f0bffe2968c919221c002302f0effa1ee000000002782e00000749581810180078
 * 00280bd0300e72f0abfe2968c919221c042302f0dbfa0ae07c2e00000e48983000682968
 * c919221c002302f0cffa80225204b018060e434618068018000e80464446200604162868
 * c019bdf77dfe0004000c8442b8dbb8e0f067550880200840002800d1cee0174d2a681748
 * 111808780d282bd1d4231b01d118487c062800d10be1d22424011019497c09060916ff22
 * bdf72cfe2868001906210b22bdf726fe2868203400190621bef77ef8286800198021bef7
 * 7ff86d20e7f03efb00f0f0fdebe0000028f40002b51b0000087807300d2800dd0d200870
 * 03a900200880124d2868124e81190968114bc2181278114c001900788000424352088020
 * 4004024303a8e7f0affc2868163c0019d1f7f8f828680219084e80190178518306780020
 * 8046271c46e0000028f400022c0d0000350d0000360d0000b51b0000094b30060215d118
 * 084e89190968061c00290dd0300e72f005fe2968c919221c002302f035fa1ee000000002
 * 782e0000074958181018007800280bd0300e72f0f1fd2968c919221c042302f021fa0ae0
 * 7c2e00001a48983000682968c919221c002302f015fa80225204b018060e434618068018
 * 000e80464446200604162868c019bdf7c3fd0004000c8442b8db0d4d2868d22424010019
 * bdf77cfd28680419d4263601801911214156201c0b22bdf77ffd00f057fd6d20e7f0a0fa
 * 4fe00000f067550828f400022b4d2868d424240100190321bdf77efe2968284a8818284a
 * 284bc91800910121019180210023cff7a3ff28680419d2263601801911216156bdf790fd
 * 0006060e28681f494018017832061016814222d0100efff7bff92868194a801806701949
 * 2868801800780001174bc91840180078012102f01dfa2868d42424010119497c124e8019
 * 01702868d22212018118498b0f4bc0180170064c20680e4e8019bdf7bdfe206803494018
 * bcf7bef800f0e4fc28f40002f40c0000b1ab05084c2c0000b61b0000000000027f2e0000
 * b41b0000b51b0000540d00000a4c20680a4d411909780a4a801801702068094bc0180121
 * d0f7c8f87820387020684019292100f0bafc000028f40002a02c0000a12c0000f40c0000
 * 0e4c20680e4e8019bdf72af80006002801d100f0a7fc0b4802210091182101220323d1f7
 * d1f80020002100220023d0f70ff920680449401800f06cfc28f40002f40c0000b0080003
 * a12c0000074c2068074a80180121d0f78bf8782038702068044bc0182d2100f07cfc0000
 * 28f40002f40c0000a02c0000154d2868154c0019bcf7eeff0006002801d100f06bfc1248
 * 02210091182101220323d1f795f828680e4c00190021d1f7e9f9286800190121d1f7b4f9
 * 286800193621d1f7c7f9286800199421d1f7b6f92e20387000f04afc28f40002f40c0000
 * b008000314140000124d2868124e8019d1f79ef90006002801d000f037fc28680e4c0019
 * 11210091c021019101210291022102220e23cff7e5ff29680c1908480918201c0a220023
 * d1f792f81620387000f01cfc28f4000214140000f40c0000540b0000144d2868144c0619
 * 144988464044007872f034fc011c0906090e301cd1f784f9286800190021d1f78bf92868
 * 00190221d1f756f90a492868404400780001094a891840180078fef7f5fa3d20387000f0
 * ebfb000028f4000214140000b61b0000000000027f2e000007480068074bc018d1f73cf9
 * 0006000e052801d000f0d4fb3e20387000f0d0fb28f40002141400000d4d2868ef242401
 * 001907210091c021490001910021029109220a23cff778ff29680c19054e8919201c0322
 * 0023d1f725f83f203870afe328f40002540b0000114d2868ef2109014018bcf723ff0006
 * 002800d1a0e32868ef22120184180b4e83190b4801690b48401a002800da1f30c202120c
 * 201c191c0223bbf753ff00260548804619e0000028f40002640f0000b008000300d80006
 * f0675508201c27308000404400682968294a8918221c002302f01af8601c0006060e3006
 * 04162868234bc018bdf7cefb0004000c8442e5db204c20681e4d4019bdf788fb2068ef26
 * 360180191c490022bbf7c0fc20681b4940180321bdf79afc2068401900210b22bdf782fb
 * 2168164bca1802201080154c0a1915481060154e8a191c33c8181060076028340a194320
 * 106028368a19142010600f480a1801201080183bca180d481060183c09190f6040203870
 * 24e300001c0f000028f40002817e01083c0f0000542c00004c2c0000d1920508502c0000
 * 602c000031ad0508124841880420084000282fd0104d2868104b114a114e8119497c4900
 * 891809884900c91809880e4a0e4b02240094bff727fb2868b8f77affb8f7caff28680a49
 * 401840210170c82038701ee00000000328f400023ea152082c3839083c0f0000b0080003
 * 90090003d50c00000b480168ef22120188180a4bc918009102210191802100220023cff7
 * 47fd04480068ef2424010019bbf79cfec2e2000028f400024c2c000005480068ef263601
 * 80190021cff7bcfe42203870b2e2000028f40002074c2068ef2109014018bcf727fe0006
 * 002800d1a4e22068024a801878e2000028f40002a02c0000084c2068ef231b01c0180021
 * cff79afe2068054c00190621d0f7eaff442038708ae2000028f40002141400000b4c2068
 * ef2636018019bcf7fdfd0006002800d17ae2206806494018d0f7d8ff0006002800d071e2
 * 2068034a801845e228f4000214140000a02c000004480068044bc0180621d0f7bdff4620
 * 38705de228f4000214140000104c2068104e8019d0f7b6ff0006002800d04fe220688019
 * 0221d0f7bfff206880190121d0f7d2ff206880190121d0f79dff206880199921d0f7a4ff
 * 4720387038e2000028f40002141400000248006802494018c6e0000028f4000214140000
 * 04480068044a80180621d0f77fff512038701fe228f4000214140000104c2068104bc018
 * d0f778ff0006002800d011e220680c4e80193621d0f780ff206880190021d0f793ff2068
 * 80190121d0f75eff206880199521d0f765ff52203870f9e128f4000214140000114d2868
 * 114c0019d0f752ff0006000e052800d0eae1b8f767fe0006002819d1286800190421d0f7
 * 3dff286800199621d0f744ff286806494018007871f01cff53203870d2e1000028f40002
 * 14140000b61b0000286800190421d0f723ff286800199821d0f72aff55203870bee10d4d
 * 28680d4c0019d0f71bff0006000e052800d0b3e10948418801200840002800d1ace12868
 * 00190621d0f704ff54203870a4e1000028f40002141400000000000306480068064a8018
 * d0f7fafe0006002800d093e11420387090e1000028f40002141400000c4d28680c4c0019
 * d0f7e8fe0006000e052800d080e10948418801200840002800d179e1286800190621d0f7
 * d1fe5620387071e128f40002141400000000000306480068064bc018d0f7c8fe00060028
 * 00d061e13c2038705ee1000028f40002141400000a4c2068de2676018019cff7a7fa0006
 * 000e04280ed1206805494018007812210822fef7a7fd6520387043e128f40002b61b0000
 * 2068014a801813e1a02c0000064c2068de235b01c018cff787fa0006000e012800d02de1
 * 206801e128f40002094c2068de2676018019cff777fa0006000e01280ad1206880190221
 * cff768fa7920387016e1000028f40002206801494018e7e0a02c0000074c2068de225201
 * 8018cff75bfa0006000e042800d001e12068024bc018d5e028f40002a02c0000b6f7e6ff
 * 0004002800d1f3e08022d20411880948084010800020002100220023cff706fd054c2068
 * 054e8019b8f768fd206804494018b5e0ffdf000028f4000214140000d50c0000b6f7c2ff
 * 0004002800d1cfe0044c2068044a8018b8f750fd2068034bc0189de028f4000214140000
 * d50c00001f4d28681f4c00191f495022e9f074fd29681e4c08191e4e89190978fef792f9
 * 1c49286800190860d820c001c7f786ff2968194e8919086080204001c7f77eff2a681649
 * 884651180860154c206992191168d8229201e6f087ff606929684144096880221201e6f0
 * 7fff04201021c8f78dfa0c491b200870dd20387080e0000028f400029833000040090003
 * 84320000b61b0000f427000390330000943300009009000390f3000216480078202867d1
 * 154c2068154a904640440068144d2969d8229201e6f050ff2068124e8019006869698022
 * 1201e6f047ff206840440068c7f736ff206880190068c7f731ff0a4821680a4bc9185022
 * e9f0fefcde2038703ee0000090f3000228f4000290330000900900039433000040090003
 * 983300000548007800282bd104480068044c00190078387024e0000090f3000228f40002
 * a02c000004480068044e8019044a0021acf742f814e0000028f40002d80c0000a5ad0508
 * 0c4c20680c4940180c4a0021acf732f82068cf221201801801210170ac20542101f0d4fc
 * 04b018bc9846a146f0bc01bc0047000028f40002d80c0000418d0508
 */

typedef struct __attribute__((packed)) {
    u32 name;
    u8 unknown_04;
    u8 appearance;
    u8 unknown_06;
    u8 level;
    u32 health : 10;
    u32 magic : 10;
    u32 attack : 11;
    u32 defense : 11;
    u32 power : 11;
    u32 resistance : 11;
} UnitTemplate;

typedef struct {
    u8 unknown_0000[0x2E78];
    UnitTemplate templates[256];
} GameState;

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} MenuInput;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
    u16 *map;
} GraphicsState;

typedef struct {
    u8 *destination;
    u32 value;
    u32 state_value;
} ByteStore;

/* The ButtonAction, ByteStore, MenuList and MenuControls of
 * include/item_quantity_menu.h.  The action's argument is untyped here:
 * state 0x3F gives the second action func_0805AD30 and the state byte
 * itself (0x0805A42A-0x0805A432). */
typedef void (*MenuCallback)(void *argument);

typedef struct {
    MenuCallback callback;
    void *argument;
    u16 buttons;
    u16 unknown_0A;
} ButtonAction;

typedef struct {
    u8 unknown_00[8];
    u16 *dest;
    u16 *source;
    u8 unknown_10[5];
    u8 rows;
    u8 columns;
    u8 unknown_17;
    u16 count;
    s16 position;
    u16 first_tile;
    u8 stride;
    u8 palette;
} MenuList;

typedef struct {
    u8 unknown_00[0x11];
    u8 row;
    u8 unknown_12[2];
} MenuControls;

/* The context func_08058D40 and func_0805ADA4 share.  The layout follows
 * include/item_quantity_menu.h up to the list's cursor; the header is not
 * included because its content and message arrays cover the options window
 * at +0xEF0 and the saved selection and scroll at +0x1BB4/+0x1BB5 that
 * this screen uses (named as in src/0805AAA8.c; the header's saved_position
 * and saved_row are the item list's, at +0x1BBE/+0x1BBF).
 * The options window repeats the window/list/controls/cursor layout 0x1FC
 * bytes on.  The unit record at +0x3284, the two BG backups and the
 * control-flag copy play the roles of backup_first, backup_second and
 * control_flags in src/08055F10.c's states 100-102. */
typedef struct {
    u8 unknown_0000[0xB54];
    u8 text[0xCD4 - 0xB54];
    u8 phase;
    u8 resume;
    u8 unknown_0CD6[2];
    Table tasks;
    u32 handlers[2];
    u8 handler_flags[2];
    u8 unknown_0CF2[2];
    u8 window[0x2C];
    MenuList list;
    MenuControls controls;
    u8 cursor[0x14];
    u8 content[0xEF0 - 0xD68];
    u8 options_window[0x2C];
    MenuList options_list;
    MenuControls options_controls;
    u8 options_cursor[0x14];
    u8 options_content[0x1414 - 0xF64];
    u8 message[0x1BB4 - 0x1414];
    u8 saved_selection;
    u8 saved_scroll;
    u8 unit;
    u8 unknown_1BB7[9];
    u8 control[0x2C4C - 0x1BC0];
    ButtonAction actions[2];
    u8 unknown_2C64[0xC];
    ByteStore store;
    u8 unknown_2C7C[0x2CA0 - 0x2C7C];
    u8 next;
    u8 saved_next;
    u8 unknown_2CA2[0x3284 - 0x2CA2];
    u8 unit_record[0x338C - 0x3284];
    u8 unknown_338C[4];
    u8 *backup_first;
    u8 *backup_second;
    u8 control_flags[0x50];
} MenuContext;

extern MenuContext *data_0200F428;
extern GameState g_state_02000000;
extern MenuInput data_03000000;
extern GraphicsState data_030008B0;
extern GraphicsState data_03000990;
extern void *data_030027F4;
extern u8 data_0600C000[];
extern u8 data_0600D800[];
extern const u16 data_0852A13E[];
extern const u16 data_0839382C[];
extern const u32 g_table_085567F0[];
extern u8 g_state_0200F390;
extern u8 g_control_flags_03000940[];

extern void func_080592D0(void *store);
extern void func_0805AD30(void *state);
extern void func_08017E80(void *object);
extern void func_08017F04(void *object);
extern void func_0805ABB0(void);
extern void func_08058D40(u8 index, u8 *state);
extern void func_0805ADA4(u8 index, u8 *state);

extern void func_08006ADC(Table *tasks, u8 index, u32 callback);
extern u16 func_08011860(void);
extern s8 func_08013380(void);
extern void func_08013390(void *object);
extern void func_08013434(void);
extern void func_08015D58(void *window, void (*draw)(void *),
                          void (*cursor)(void *));
extern void func_08016210(void *window, const void *content, u16 first,
                          u16 second);
extern void func_08016234(void *window);
extern u8 func_08017180(void *window);
extern void func_08017AD8(MenuList *list);
extern void func_08017AF4(MenuList *list, s8 row, u8 value);
extern u16 func_08017B50(MenuList *list);
extern u16 func_08017B68(MenuList *list, s8 row);
extern void func_08017D18(MenuControls *controls, u8 mask);
extern void func_08017E28(void *cursor);
extern void func_08017FB0(MenuControls *controls, u8 row);
extern void func_08017FBC(MenuControls *controls, u32 direction);
extern void func_08019A8C(void *context, u16 value, void *first,
                          void *second);
extern void func_08019AE4(void *context, u16 value, void *first,
                          void *second, u8 mode);
extern void *func_08022840(u32 size);
extern void func_08022854(void *object);
extern void func_08022E90(u16 duration, u8 mode);
extern void func_08029D20(void *control, u8 mode);
extern u8 func_08029D2C(void *control);
extern void func_08029F7C(void *menu, u8 flags, MenuCallback scroll,
                          void *argument, ButtonAction *actions,
                          u8 action_count);
extern void func_0802A1FC(void *window, u8 a, u8 b, u8 c, u8 d, u16 value,
                          u8 selection);
extern void func_0802A290(void *window, u8 appearance);
extern void func_0802A2C0(u8 x, u8 y, u8 width, u8 height);
extern void func_0802A370(u8 x, u8 y, u8 width, u8 height);
extern void func_0802B108(MenuList *list);
extern void func_0802B2E8(GraphicsState *graphics, u8 x, u8 y, u8 width,
                          u8 height);
extern void func_0802B368(void *window, u8 *destination, u8 first,
                          u8 second);
extern void func_0802B460(GraphicsState *graphics, u8 x, u8 y);
extern void func_0802B53C(void *message, u8 value);
extern u8 func_0802B548(void *message);
extern void func_0802B554(void *message, u8 value);
extern void func_0802B56C(void *message, u8 value);
extern void func_0802B584(void *message, u8 value);
extern void func_0802B59C(void *message, u8 value);
extern void func_08058890(u8 value);
extern void func_08058C48(void *unit, u8 index);
extern void func_08059344(u8 index, u8 x, u8 y);
extern void func_080593E0(u8 index);
extern void func_0805AAA8(void);
extern void func_0805AB34(u8 *state);
extern void func_0805C3D4(u32 text, MenuList *list, s8 row, u8 style);
extern void func_0805C434(u16 x, u16 y);
extern void func_0805C4BC(u8 selector, u8 value);
extern u32 func_080C8570(u8 first, u8 second, u8 selector);
extern void func_080CC510(u8 index);
extern u8 func_080CCAD8(u8 index);
extern u32 func_080CCB68(u8 index);
extern u8 func_080CCB94(void);
extern void func_08141540(u16 song_id);
extern void func_0814186C(const void *source, void *destination,
                          u32 control);
extern void *func_081443FC(void *destination, const void *source,
                           u32 byte_count);

/* The cursor row is read through the controls record's address, as in
 * src/0805ADA4.c, src/08055F10.c and src/08054E14.c: each read adds the
 * record's offset to the context and loads [base, #0x11] (0x08059AE4,
 * 0x08059D1C, 0x08059E80, 0x08059FE8, 0x0805A088, 0x0805A47A); the folded
 * 0xD51 offset of a member chain appears nowhere. */
#define CURSOR_ROW(controls) ((controls)->row)

/* The unit list is drawn from saved_scroll by one block that the ROM
 * carries three times: 0x080599E2-0x08059AB0 (states 0x15/0x16) and
 * 0x08059DA6-0x08059E5C and 0x08059F18-0x08059FD0 (page up and page down).
 * Each copy forms the list's address and stores the top row at [list, #0x1A]
 * (0x080599F2, 0x08059DB0, 0x08059F22), reads saved_scroll again for the
 * unit index, and steps the index before the row (0x08059A8C, 0x08059E3A,
 * 0x08059FAE).  The row text is the one func_0805ABB0 (src/0805ABB0.c) draws
 * for a single row: the unit's name, the recruit's name in style 4, or
 * g_table_085567F0[38]. */
#define DRAW_UNIT_LIST(list)                                                \
    {                                                                       \
        (list)->position = data_0200F428->saved_scroll;                     \
        item = data_0200F428->saved_scroll;                                 \
        for (i = 0; i < func_08017B50(list); i++) {                         \
            if (g_state_02000000.templates[item].name)                      \
                func_0805C3D4(func_080CCB68(item), list, i, 0);     \
            else if (g_state_02000000.templates[item].unknown_04)           \
                func_0805C3D4(func_080CCB68(item), list, i, 4);     \
            else                                                            \
                func_0805C3D4(g_table_085567F0[38], list, i, 0);            \
            item++;                                                         \
        }                                                                   \
    }

/* plausible: LCD display control; 0x0805A8A0 clears its window 0 enable. */
#define REG_DISPCNT (*(volatile u16 *)0x04000000)

void func_08059454(u8 index, u8 *state)
{
    s8 i;
    s8 item;
    u16 fill;
    u16 *fill_source;

    switch (*state) {
    case 0x00:
        func_08029D20(data_0200F428->control, 4);
        data_0200F428->saved_selection = 0;
        data_0200F428->saved_scroll = 0;
        if (func_080CCB94() == 0) {
            func_0802B53C(data_0200F428->message, 4);
            func_0802B554(data_0200F428->message, 0x92);
            *state = 0x01;
        } else {
            func_0802B53C(data_0200F428->message, 4);
            func_0802B554(data_0200F428->message, 0x93);
            *state = 0x02;
        }
        break;
    case 0x01:
        if (func_0802B548(data_0200F428->message) == 5
            && (data_03000000.pressed & 1))
            *state = 0xFF;
        break;
    case 0x02:
        if (func_0802B548(data_0200F428->message) == 0)
            *state = 0x14;
        break;
    case 0x14:
        func_0802A2C0(0, 0, 0, 0);
        func_0802A1FC(data_0200F428->window, 2, 2, 0xE, 0x11, 0xC0, 1);
        func_0802B368(data_0200F428->window, data_0200F428->text, 10, 0);
        *state = 0x15;
        break;
    case 0x15:
    case 0x16:
        if (func_08017180(data_0200F428->window)) {
            func_0802B460(&data_030008B0, 0x18, 1);
            func_08016210(data_0200F428->window, data_0200F428->content,
                          (data_0600C000 - data_030008B0.tiles) / 32, 0x14);
            DRAW_UNIT_LIST(&data_0200F428->list);
            func_08017AD8(&data_0200F428->list);
            func_08015D58(data_0200F428->window, func_08017E80, func_08017F04);
            func_08017FB0(&data_0200F428->controls,
                          data_0200F428->saved_selection);
            func_08017AF4(&data_0200F428->list,
                          CURSOR_ROW(&data_0200F428->controls), 11);
            func_0805C4BC(g_state_02000000.templates[data_0200F428->unit].level, 1);
            *state = 0x64;
            data_0200F428->next = 0x17;
        }
        break;
    case 0x17:
        data_0200F428->actions[0].buttons = 2;
        data_0200F428->actions[0].callback = func_080592D0;
        data_0200F428->actions[0].argument = &data_0200F428->store;
        data_0200F428->store.destination = state;
        data_0200F428->store.value = 0x28;
        data_0200F428->store.state_value = 0xFF;
        {
            /* Controls before list (0x08059B78, 0x08059B7E), as
             * src/0805AB34.c and src/0805AAA8.c read them. */
            MenuControls *controls = &data_0200F428->controls;

            data_0200F428->unit = func_08017B68(&data_0200F428->list, controls->row);
        }
        func_080593E0(data_0200F428->unit);
        *state = 0x18;
        break;
    case 0x18:
        if (data_03000000.pressed & 0x100) {
            if (g_state_02000000.templates[data_0200F428->unit].name == 0) {
                func_08141540(0x6B);
            } else {
                data_0200F428->next = 0x18;
                *state = 0xDC;
            }
        } else if (data_03000000.pressed & 1) {
            func_0805AB34(state);
        } else if (data_03000000.pressed & 4) {
            func_0802A2C0(2, 2, 0x1A, 6);
            func_08013390(data_0200F428);
            if (g_state_02000000.templates[data_0200F428->unit].name == 0)
                func_08019A8C(data_0200F428, 0x25, &data_030008B0, &data_03000990);
            else
                func_08019A8C(data_0200F428,
                              func_080C8570(func_080CCAD8(data_0200F428->unit),
                                            func_080CCAD8(data_0200F428->unit), 0)
                                  + 0x247,
                              &data_030008B0, &data_03000990);
            /* Both state stores are in the ROM (0x08059CC4, 0x08059CD4). */
            *state = 0xC8;
            data_0200F428->resume = 0x18;
            *state = 0xB4;
        } else if ((data_03000000.held & 0x200)
                   && (data_03000000.repeated & 0x40)) {
            if (data_0200F428->saved_scroll == 0) {
                if (CURSOR_ROW(&data_0200F428->controls) != 0) {
                    func_08017AF4(&data_0200F428->list,
                                  CURSOR_ROW(&data_0200F428->controls), 0xFF);
                    func_08017AF4(&data_0200F428->list, 0, 11);
                    func_08017FB0(&data_0200F428->controls, 0);
                    func_08017FBC(&data_0200F428->controls, 0x40);
                    func_08141540(0x6D);
                    func_0805AAA8();
                }
            } else {
                if (data_0200F428->saved_scroll - 7 < 0)
                    data_0200F428->saved_scroll = 0;
                else
                    data_0200F428->saved_scroll -= 7;
                /* CpuFill16(0, list.source, rows * columns * 4): the SDK's
                 * vu16 temporary, spelled through a pointer until
                 * fftadecomp-kit#164 (0x08059D6E-0x08059D72 form the slot's
                 * address before the zero), and the byte size halved with
                 * lsrs (0x08059D8E), as src/0806E170.c writes it. */
                fill_source = &fill;
                *fill_source = 0;
                func_0814186C(fill_source, data_0200F428->list.source,
                              0x01000000 | ((u32)(data_0200F428->list.rows
                                                  * (data_0200F428->list.columns << 2)) >> 1));
                func_0802B108(&data_0200F428->list);
                DRAW_UNIT_LIST(&data_0200F428->list);
                func_08017AD8(&data_0200F428->list);
                func_08017AF4(&data_0200F428->list,
                              CURSOR_ROW(&data_0200F428->controls), 11);
                func_0805AAA8();
                func_08141540(0x6D);
            }
        } else if ((data_03000000.held & 0x200)
                   && (data_03000000.repeated & 0x80)) {
            if (data_0200F428->saved_scroll == 13) {
                if (CURSOR_ROW(&data_0200F428->controls) != 6) {
                    func_08017AF4(&data_0200F428->list,
                                  CURSOR_ROW(&data_0200F428->controls), 0xFF);
                    func_08017AF4(&data_0200F428->list, 6, 11);
                    func_08017FB0(&data_0200F428->controls, 6);
                    func_08017FBC(&data_0200F428->controls, 0x80);
                    func_08141540(0x6D);
                    func_0805AAA8();
                }
            } else {
                if (data_0200F428->saved_scroll + 7 > 13)
                    data_0200F428->saved_scroll = 13;
                else
                    data_0200F428->saved_scroll += 7;
                /* As above: 0x08059EE0-0x08059EE4, lsrs at 0x08059F00. */
                fill_source = &fill;
                *fill_source = 0;
                func_0814186C(fill_source, data_0200F428->list.source,
                              0x01000000 | ((u32)(data_0200F428->list.rows
                                                  * (data_0200F428->list.columns << 2)) >> 1));
                func_0802B108(&data_0200F428->list);
                DRAW_UNIT_LIST(&data_0200F428->list);
                func_08017AD8(&data_0200F428->list);
                func_08017AF4(&data_0200F428->list,
                              CURSOR_ROW(&data_0200F428->controls), 11);
                func_0805AAA8();
                func_08141540(0x6D);
            }
        } else {
            func_08017D18(&data_0200F428->controls, 3);
            func_08029F7C(data_0200F428->window, 0x80,
                          (MenuCallback)func_0805ABB0, 0,
                          data_0200F428->actions, 1);
            {
                /* Controls before list again (0x0805A038, 0x0805A03E), and
                 * the unit index item holds the selection across
                 * func_080593E0 (r6, 0x0805A04A-0x0805A068), as item does in
                 * src/08051DB4.c (and as src/08092784.c reuses its i in
                 * case 64). */
                MenuControls *controls = &data_0200F428->controls;

                item = func_08017B68(&data_0200F428->list, controls->row);
            }
            if (data_0200F428->unit != item) {
                func_080593E0(item);
                data_0200F428->unit = item;
                func_0805C4BC(g_state_02000000.templates[data_0200F428->unit].level, 1);
                data_0200F428->saved_selection =
                    CURSOR_ROW(&data_0200F428->controls);
                {
                    /* [list, #0x1A] at 0x0805A09A, as src/0805AAA8.c reads
                     * the scroll through its panel. */
                    MenuList *list = &data_0200F428->list;

                    data_0200F428->saved_scroll = list->position;
                }
            }
        }
        func_08017E28(data_0200F428->cursor);
        func_08016234(data_0200F428->window);
        break;
    case 0x28:
        data_0200F428->saved_next = data_0200F428->next;
        func_0802A290(data_0200F428->window, 1);
        *state = 0x78;
        data_0200F428->next = 0x29;
        break;
    case 0x29:
        if (func_08017180(data_0200F428->window)) {
            func_0802B2E8(&data_030008B0, 0x18, 1, 3, 2);
            func_0802A370(0, 0, 0, 0);
            *state = data_0200F428->saved_next;
        }
        break;
    case 0x2C:
        func_0802A290(data_0200F428->window, 1);
        *state = 0x78;
        data_0200F428->next = 0x2D;
        break;
    case 0x2D:
        if (func_08017180(data_0200F428->window)) {
            func_0802B2E8(&data_030008B0, 0x18, 1, 3, 2);
            func_0802B59C(data_0200F428->message, 0);
            func_0802B53C(data_0200F428->message, 1);
            func_0802B56C(data_0200F428->message, 0x36);
            func_0802B554(data_0200F428->message, 0x94);
            *state = 0x2E;
        }
        break;
    case 0x2E:
        if (func_0802B548(data_0200F428->message) == 0) {
            func_0802A1FC(data_0200F428->window, 2, 2, 0xE, 0x11, 0xC0, 1);
            func_0802B368(data_0200F428->window, data_0200F428->text, 10, 0);
            *state = 0x16;
        }
        break;
    case 0x3C:
        func_0802B584(data_0200F428->message, func_080CCAD8(data_0200F428->unit));
        func_0802B59C(data_0200F428->message, 0);
        func_0802B53C(data_0200F428->message, 2);
        func_08058890(g_state_02000000.templates[data_0200F428->unit].level);
        *state = 0x3D;
        break;
    case 0x3D:
        if (func_0802B548(data_0200F428->message) == 5)
            *state = 0x3E;
        break;
    case 0x3E:
        func_0802A1FC(data_0200F428->options_window, 0, 9, 10, 7, 0x180, 0);
        func_0802B368(data_0200F428->options_window, data_0200F428->text, 3, 0);
        *state = 0x3F;
        break;
    case 0x3F:
        if (func_08017180(data_0200F428->options_window)) {
            func_08016210(data_0200F428->options_window,
                          data_0200F428->options_content,
                          (data_0600D800 - data_030008B0.tiles) / 32, 2);
            /* The row counter is item again (r6, 0x0805A3A4). */
            for (item = 0; item < func_08017B50(&data_0200F428->options_list); item++)
                func_0805C3D4(g_table_085567F0[item + 39],
                              &data_0200F428->options_list, item, 0);
            func_08017AD8(&data_0200F428->options_list);
            func_08015D58(data_0200F428->options_window, func_08017E80, 0);
            func_08017D18(&data_0200F428->options_controls, 3);
            func_08017AF4(&data_0200F428->options_list, 0, 11);
            data_0200F428->actions[0].buttons = 2;
            data_0200F428->actions[0].callback = func_080592D0;
            data_0200F428->actions[0].argument = &data_0200F428->store;
            data_0200F428->store.destination = state;
            data_0200F428->store.value = 0x43;
            data_0200F428->store.state_value = 0x14;
            data_0200F428->actions[1].buttons = 1;
            data_0200F428->actions[1].callback = func_0805AD30;
            data_0200F428->actions[1].argument = state;
            *state = 0x40;
        }
        break;
    case 0x40:
        if (data_03000000.pressed & 4) {
            func_08019AE4(data_0200F428,
                          data_0852A13E[data_0839382C[CURSOR_ROW(&data_0200F428->options_controls)]],
                          &data_030008B0, &data_03000990, 2);
            func_08013390(data_0200F428);
            func_08013434();
            data_0200F428->resume = 0x40;
            *state = 0xC8;
        } else {
            func_08029F7C(data_0200F428->options_window, 0x80, 0, 0,
                          data_0200F428->actions, 2);
        }
        func_08016234(data_0200F428->options_window);
        break;
    case 0x41:
        func_0802A290(data_0200F428->options_window, 0);
        *state = 0x42;
        break;
    case 0x42:
        if (func_08017180(data_0200F428->options_window))
            *state = data_0200F428->next;
        break;
    case 0x43:
        func_0802A290(data_0200F428->options_window, 0);
        func_0802B53C(data_0200F428->message, 6);
        *state = 0x44;
        break;
    case 0x44:
        if (func_08017180(data_0200F428->options_window)
            && func_0802B548(data_0200F428->message) == 0)
            *state = data_0200F428->next;
        break;
    case 0x45:
        func_0802B53C(data_0200F428->message, 6);
        *state = 0x46;
        break;
    case 0x46:
        if (func_0802B548(data_0200F428->message) == 0) {
            func_0802B56C(data_0200F428->message, 2);
            func_0802B59C(data_0200F428->message, 1);
            func_0802B53C(data_0200F428->message, 1);
            func_0802B554(data_0200F428->message, 0x99);
            *state = 0x47;
        }
        break;
    case 0x47:
        if (func_0802B548(data_0200F428->message) == 0)
            *state = 0x3C;
        break;
    case 0x50:
        func_0802B53C(data_0200F428->message, 6);
        *state = 0x51;
        break;
    case 0x51:
        if (func_0802B548(data_0200F428->message) == 0) {
            func_0802B56C(data_0200F428->message, 0x36);
            func_0802B59C(data_0200F428->message, 0);
            func_0802B53C(data_0200F428->message, 1);
            func_0802B554(data_0200F428->message, 0x95);
            *state = 0x52;
        }
        break;
    case 0x52:
        if (func_0802B548(data_0200F428->message) == 5) {
            if (func_08013380() == 0) {
                func_0802B53C(data_0200F428->message, 4);
                func_0802B554(data_0200F428->message, 0x96);
                func_080CC510(data_0200F428->unit);
                *state = 0x53;
            } else {
                func_0802B53C(data_0200F428->message, 4);
                func_0802B554(data_0200F428->message, 0x98);
                *state = 0x55;
            }
        }
        break;
    case 0x53:
        if (func_0802B548(data_0200F428->message) == 5
            && (data_03000000.pressed & 1)) {
            func_0802B53C(data_0200F428->message, 6);
            *state = 0x54;
        }
        break;
    case 0x54:
        if (func_0802B548(data_0200F428->message) == 0)
            *state = 0x14;
        break;
    case 0x55:
        if (func_0802B548(data_0200F428->message) == 5
            && (data_03000000.pressed & 1)) {
            func_0802B53C(data_0200F428->message, 6);
            *state = 0x56;
        }
        break;
    case 0x56:
        if (func_0802B548(data_0200F428->message) == 0)
            *state = 0x3C;
        break;
    case 0x64:
        if (func_08029D2C(data_0200F428->control) == 4) {
            func_08059344(data_0200F428->unit, 0x12, 8);
            *state = 0x65;
        } else {
            *state = data_0200F428->next;
        }
        break;
    case 0x65:
        if (func_08029D2C(data_0200F428->control) == 1)
            *state = data_0200F428->next;
        break;
    case 0x78:
        if (func_08029D2C(data_0200F428->control) == 1) {
            func_08029D20(data_0200F428->control, 2);
            *state = 0x79;
        } else {
            *state = data_0200F428->next;
        }
        break;
    case 0x79:
        if (func_08029D2C(data_0200F428->control) == 4)
            *state = data_0200F428->next;
        break;
    case 0xB4:
        if (func_08011860()) {
            REG_DISPCNT &= ~0x2000;
            func_0802A2C0(0, 0, 0, 0);
            func_08013390(data_0200F428->message);
            *state = data_0200F428->resume;
        }
        break;
    case 0xC8:
        if (func_08011860()) {
            func_08013390(data_0200F428->message);
            *state = data_0200F428->resume;
        }
        break;
    case 0xDC:
        func_081443FC(data_0200F428->control_flags, g_control_flags_03000940, 0x50);
        func_08058C48(data_0200F428->unit_record, data_0200F428->unit);
        data_030027F4 = data_0200F428->unit_record;
        data_0200F428->backup_first = func_08022840(0x6C00);
        data_0200F428->backup_second = func_08022840(0x1000);
        func_0814186C(data_03000990.tiles, data_0200F428->backup_first, 0x3600);
        func_0814186C(data_03000990.map, data_0200F428->backup_second, 0x800);
        func_08022E90(4, 16);
        g_state_0200F390 = 0x1B;
        *state = 0xDD;
        break;
    case 0xDD:
        if (g_state_0200F390 == 0x20) {
            func_0814186C(data_0200F428->backup_first, data_03000990.tiles, 0x3600);
            func_0814186C(data_0200F428->backup_second, data_03000990.map, 0x800);
            func_08022854(data_0200F428->backup_first);
            func_08022854(data_0200F428->backup_second);
            func_081443FC(g_control_flags_03000940, data_0200F428->control_flags, 0x50);
            *state = 0xDE;
        }
        break;
    case 0xDE:
        if (g_state_0200F390 == 0)
            *state = data_0200F428->next;
        break;
    case 0xFE:
        func_08006ADC(&data_0200F428->tasks, 0, (u32)func_0805ADA4);
        break;
    case 0xFF:
        func_08006ADC(&data_0200F428->tasks, 0, (u32)func_08058D40);
        data_0200F428->handler_flags[0] = 1;
        break;
    }
    func_0805C434(0xAC, 0x54);
}
