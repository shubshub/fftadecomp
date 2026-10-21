import sys, struct
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB

ROM = "Final Fantasy Tactics Advance (USA, Australia).gba"
rom = open(ROM, "rb").read()

addr = int(sys.argv[1], 16)
data = open(sys.argv[2], "rb").read()
size = int(sys.argv[3]) if len(sys.argv) > 3 else len(data)

expect = rom[addr-0x08000000: addr-0x08000000+size]
got = data[:size]

print(f"expected {len(expect)} bytes, got {len(got)} bytes")
if expect == got:
    print("MATCH - byte identical")
else:
    n = min(len(expect), len(got))
    for i in range(n):
        if expect[i] != got[i]:
            print(f"first difference at offset {i} (addr {addr+i:08X}): expected {expect[i]:02X} got {got[i]:02X}")
            break
    else:
        print(f"common prefix identical; length differs (exp {len(expect)}, got {len(got)})")
    print()
    cs = Cs(CS_ARCH_ARM, CS_MODE_THUMB)
    print("--- expected ---")
    for i in cs.disasm(expect, addr):
        print(f"{i.address:08X}  {i.bytes.hex():<12} {i.mnemonic:<10} {i.op_str}")
    print("--- got ---")
    for i in cs.disasm(got, addr):
        print(f"{i.address:08X}  {i.bytes.hex():<12} {i.mnemonic:<10} {i.op_str}")
    print("--- expected raw ---")
    print(expect.hex())
    print("--- got raw ---")
    print(got.hex())
