# Boot LCD shadow initialization at 080032B0

The 72-byte USA owner spans 080032B0 through 080032F7. The boot BL at
080002A2 calls it without preparing arguments. The following instruction calls
0800323C. The original uses no incoming arguments and restores SP and R4
before returning. Exactly 26 instructions are reachable from the entry.

The ROM word at 0836D4B8 holds the Thumb pointer 03005E79. The boot installer
at 08002768 copies 08A38A2C..08A38ADC to 03005E78 with CpuSet. The BL at
080032BC calls the BX R2 veneer at 0814224C with R0 = 03000940, R1 = 80,
and R2 = 03005E79. The installed callback clears the entire 80-byte LCD
shadow using 20 aligned word stores. The five subsequent halfword stores
set display to 0060 and BG2PC, BG2PA, BG3PC and BG3PA to 0100 in that
order. The six halfword reads are at offsets 1E, 1E, 1A, 2E, 2E and 2A.
The shared control_flags.h declares those four members as volatile bitfields.

The adjacent C candidate uses the actual callback and shared shadow
declarations. Default agbcc -mthumb-interwork -O2 emits 60 bytes, with two
fewer reachable instructions. Both linked bodies were executed from the real
boot call with installed Thumb code, using a CpuSet model for the preceding
installer. Both preserved R4, restored SP, returned to 080002A6, issued the
same reads and writes, and left both neighboring halfword canaries unchanged.
The candidate SHA-256 is
23b278ab9b3a8abc45d412967062f7c8c93131cb6d43d20715e3610dbd511806.
The 72-byte original SHA-256 is
5ca0c6e2724bc1e451d71f5f6d88c18c7b817f0025ecf083b6ee84eadae1143b.

After the clear the original branches from 080032C0 to 080032CE, skipping
alignment, two literal words and E7FE at 080032CC. It reloads the shadow
address at 080032CE from a third literal. The candidate instead keeps the
shadow in R4. The only 16-bit immediate branch to 080032CC is the self-branch.
All 16 MiB contain one encoded direct Thumb BL to 080032B0, none to 080032CC,
and no raw Thumb pointer to either address, including unaligned words. The
two other main-code examples with a similar branch over a self-loop each
have a separate reachable conditional edge into the loop. The original
provides no corresponding guard for this initializer.

The ordinary matcher refuses the shorter complete symbol. The canonical
thunk and mixed-return inert-spin selectors did not yield a match either.
A source-level condition explaining the isolated self-branch remains
unresolved. No MATCH report was issued.
