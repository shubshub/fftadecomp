import json, sys, struct
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB

ROM = "Final Fantasy Tactics Advance (USA, Australia).gba"
rom = open(ROM, "rb").read()

def disasm(start, length=0x100):
    cs = Cs(CS_ARCH_ARM, CS_MODE_THUMB)
    cs.detail = False
    base = start
    for i in cs.disasm(rom[start-0x08000000:start-0x08000000+length], base):
        print(f"{i.address:08X}  {i.bytes.hex():<12} {i.mnemonic:<10} {i.op_str}")

if __name__ == "__main__":
    start = int(sys.argv[1], 16)
    length = int(sys.argv[2], 16) if len(sys.argv) > 2 else 0x100
    disasm(start, length)
