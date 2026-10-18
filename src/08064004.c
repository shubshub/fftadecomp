// 0x08064004 - 96 bytes of code + a 2-word literal pool.
//
// Fills one record at 0x020020D0, pokes three bytes into the script state
// reached through 0x0200F450, and appends three opcodes to that state's run
// list.  Same state object as src/08064278.c; the type now lives in include/ffta.h.
#include "ffta.h"

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