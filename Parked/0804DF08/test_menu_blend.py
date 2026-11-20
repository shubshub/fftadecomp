"""Exercise the original menu allocation, fade initializer, both callers and signed division."""
import argparse
import os
from pathlib import Path
import struct
import sys
import unittest

KIT = Path(os.environ["FFTA_KIT"])
sys.path.insert(0, str(KIT / "tests"))
from test_battle_action_value import battle_environment, signed16


def trunc_div(value, divisor):
    magnitude = abs(value) // abs(divisor)
    return -magnitude if (value < 0) != (divisor < 0) else magnitude


def compile_candidate(root, rom):
    import addressed_signed_runtime_profile as profile
    import match
    from match_evidence import data_snapshot, mapping_snapshot
    addr = 0x0804DF08
    args = argparse.Namespace(cc=match.DEFAULT_CC, cpp=match.DEFAULT_CPP, assembler=match.DEFAULT_AS,
                              linker=match.DEFAULT_LD, objcopy=match.DEFAULT_OBJCOPY, flags=match.DEFAULT_FLAGS)
    runner = match.Runner(match.DEFAULT_CC, 'Ubuntu', match.DEFAULT_WSL_PATH, root=root, timeout=120)
    with runner.workspace() as workspace:
        _, _, image = match.compile_object(runner, workspace, args, root, addr, "src/0804DF08.c")
        body, *_ = profile.object_bytes(runner, workspace, args, image, addr, rom, mapping_snapshot(root),
                                        selector=profile.COMPILER_DATA_SELECTOR, data_mapping=data_snapshot(root))
    return body


class MenuBlendTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        root = Path(os.environ["FFTA_MENU_BLEND_ROOT"]).resolve()
        cls.rom = (root / "baserom.bin").read_bytes()
        cls.candidate = compile_candidate(root, cls.rom) if os.getenv("FFTA_MENU_BLEND_CANDIDATE") else None

    def setUp(self):
        from unicorn import UC_HOOK_CODE
        from unicorn.arm_const import UC_ARM_REG_R0, UC_ARM_REG_R1
        self.cpu, self.call, self.write, _ = battle_environment(self)
        if self.candidate is not None:
            self.assertEqual(len(self.candidate), 254)
            self.cpu.mem_write(0x0804DF08, self.candidate)
        self.cpu.mem_map(0x06000000, 0x18000)
        self.call(0x08006A7C, 0x03000880, 0x03002860, 0x03000EB8, 4)
        self.call(0x0804C8C4)
        base, = struct.unpack("<I", self.cpu.mem_read(0x0201F540, 4))
        self.blend = self.call(0x0804CAB0)
        self.assertTrue(0x0201F550 <= base < 0x02040000 - 0x394)
        self.assertEqual(self.blend, base + 4)
        self.write(0x03000990 + 12, "BB", 32, 32)
        self.write(0x03000990 + 16, "II", 0x06000000, 0x06008000)
        self.divisions = []
        def helper(cpu, address, size, _):
            self.divisions.append(tuple(struct.unpack("<i", struct.pack("<I", cpu.reg_read(r)))[0]
                                        for r in (UC_ARM_REG_R0, UC_ARM_REG_R1)))
        self.cpu.hook_add(UC_HOOK_CODE, helper, begin=0x081426B8, end=0x081426B8)

    def check_update(self, data, call):
        start, x0, y0, end, x1, y1, cursor = data
        self.divisions.clear()
        got = call()
        if start <= cursor < end:
            elapsed, duration = signed16(cursor-start), signed16(end-start)
            args = [((x1-x0)*elapsed, duration), ((y1-y0)*elapsed, duration)]
            expected = [(a+trunc_div(v,d)) & 255 for a, (v,d) in zip((x0,y0),args)]
            done = 0
        else:
            args, expected, done = [], [x1, y1], 1
        self.assertEqual(self.divisions, args)
        self.assertEqual(list(self.cpu.mem_read(0x0300098C, 2)), expected)
        self.assertEqual(struct.unpack("<hBBhBBh", self.cpu.mem_read(self.blend, 10)),
                         (*data[:6], signed16(cursor+1)))
        return got, done

    def test_real_callers(self):
        state = 0x02019000
        for initial, left, x0, x1 in ((6, 3, 16, 0), (7, 4, 0, 16)):
            self.write(state, "B", initial)
            self.call(0x0804D86C, 0, state)
            self.assertEqual(self.cpu.mem_read(state, 1)[0], left)
            self.assertEqual(struct.unpack("<hBBhBBh", self.cpu.mem_read(self.blend,10)),
                             (0, x0, 16-x0, 12, x1, 16-x1, 0))
            for cursor in range(13):
                _, done = self.check_update((0,x0,16-x0,12,x1,16-x1,cursor),
                                              lambda: self.call(0x0804D86C,0,state))
                self.assertEqual(self.cpu.mem_read(state,1)[0], (5 if left == 3 else 8) if done else left)

    def test_signed_edges(self):
        for start, end, cursor in ((0,0,0), (20,1,3), (5,10,4), (5,10,5), (5,10,9),
                                  (5,10,10), (-8,7,-3), (-32768,32767,0), (-32768,1,-1),
                                  (-32768,32767,32766), (0,32767,32767), (-32768,-32767,-32768)):
            with self.subTest(start=start,end=end,cursor=cursor):
                data = start, 255, 1, end, 1, 254, cursor
                self.write(self.blend, "hBBhBBh", *data)
                got, expected = self.check_update(data, lambda: self.call(0x0804DF08,0xdeadbeef,3,7,11))
                self.assertEqual(got, expected)

if __name__ == "__main__":
    unittest.main()
