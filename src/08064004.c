// 0x08064004 - 96 bytes of code + a 2-word literal pool.
//
// Fills one record at 0x020020D0, pokes three bytes into the script state
// reached through 0x0200F450, and appends three opcodes to that state's run
// list.  Same state object as src/08064278.c; the type is redeclared here
// because the shared header is not being edited.
#include "ffta.h"

/* The opcode script list.  current/count sit at +0/+2 and the appended
 * opcodes start at +4; everything else is at the offset the instructions
 * use, with no meaning attached - those come from the code, not from a
 * recovered layout. */
typedef struct {
    u16 current;         /* +0x00 */
    u16 count;           /* +0x02 */
    u16 entries[34];     /* +0x04 .. +0x47 */
    u8  unknown_48[5];   /* +0x48 .. +0x4C */
    u8  unknown_4d;      /* +0x4D */
    u8  unknown_4e[3];   /* +0x4E .. +0x50 */
    u8  unknown_51;      /* +0x51 */
    u8  unknown_52[10];  /* +0x52 .. +0x5B */
    u32 unknown_5c;      /* +0x5C */
} ScriptState;

/* The record written at 0x020020D0: a word at +4 copied out of the state,
 * a halfword at +0xC set to a constant. */
typedef struct {
    u32 unknown_00;
    u32 field_04;
    u16 unknown_08;
    u16 unknown_0a;
    u16 field_0c;
} Record;

void func_08064004(void)
{
    Record *rec = (Record *)0x020020D0;
    ScriptState *state;

    rec->field_04 = (*(ScriptState **)0x0200F450)->unknown_5c;
    rec->field_0c = 0x11;
    (*(ScriptState **)0x0200F450)->unknown_4d = 0x0B;
    (*(ScriptState **)0x0200F450)->unknown_51 = 0x90;

    /* The run-list half of the function keeps the state pointer in a
     * register; the four stores above re-read it instead.  That split is
     * what agbcc emits only when the two halves name the pointer
     * differently, hence the local here and the inline derefs above. */
    state = *(ScriptState **)0x0200F450;

    state->entries[state->count++] = state->current;
    state->current = 0x26;
    state->entries[state->count++] = state->current;
    state->current = 0x37;
    state->entries[state->count++] = state->current;
    state->current = 0x31;
}