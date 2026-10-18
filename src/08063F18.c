// 0x08063F18 - 220 bytes of code + a 4-word literal pool (236 bytes as one
// ELF symbol).
//
// Copies a word out of the record at 0x020020D0 into the script state
// reached through 0x0200F450, pokes a byte and three halfwords into that
// state, then appends nine opcodes to the state's run list.  Same state
// object as src/08064004.c and src/08064278.c; the type now lives in include/ffta.h.
#include "ffta.h"

void func_08063F18(void)
{
    ScriptState *state;
    /* The slot is read twice: once for the two stores at the head, and once
     * more after them, which is where the run list starts.  Naming the two
     * reads differently is what puts the reload (ldr r2,[r2]) after the two
     * stores rather than folding the second read into the first; spelled as
     * two inline derefs instead, the stores' addresses come out in the
     * opposite order and the record's own pointer takes the register the
     * state pointer needs. */
    ScriptState *head = *(ScriptState **)0x0200F450;
    Record *rec = (Record *)0x020020D0;

    head->unknown_5c = rec->field_04;
    head->unknown_51 = 0x10;

    state = *(ScriptState **)0x0200F450;
    state->field_4e = 0xC5;
    state->field_64 = 0x9001;
    state->field_66 = 0x1234;

    state->current = 0x25;
    state->entries[state->count++] = state->current;
    state->current = 0x3C;
    state->entries[state->count++] = state->current;
    state->current = 0x39;
    state->entries[state->count++] = state->current;
    state->current = 0x27;
    state->entries[state->count++] = state->current;
    state->current = 0x34;
    state->entries[state->count++] = state->current;
    state->current = 0x33;
    state->entries[state->count++] = state->current;
    state->current = 0x21;
    state->entries[state->count++] = state->current;
    state->current = 0x2C;
    state->entries[state->count++] = state->current;
    state->current = 0x28;
    state->entries[state->count++] = state->current;
    state->current = 0x39;
}