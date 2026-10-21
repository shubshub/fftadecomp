import json, sys, struct
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB

ROM = "Final Fantasy Tactics Advance (USA, Australia).gba"
rom = open(ROM, "rb").read()

# find callers: look for bl to target
def find_callers(target):
    cs = Cs(CS_ARCH_ARM, CS_MODE_THUMB)
    # scan whole rom code region 0x08000000-0x09000000 in thumb mode
    out = []
    base = 0x08000000
    end = 0x09000000
    for i in cs.disasm(rom[base-0x08000000:end-0x08000000], base):
        if i.mnemonic in ("bl", "blx") and i.op_str.startswith("#0x"):
            try:
                t = int(i.op_str[1:], 16)
            except ValueError:
                continue
            if t == target:
                out.append((i.address, i.bytes.hex()))
    return out

if __name__ == "__main__":
    t = int(sys.argv[1], 16)
    for a, b in find_callers(t):
        print(f"{a:08X}  {b}")
