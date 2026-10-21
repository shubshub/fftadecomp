import re, sys
path = sys.argv[1]
pat = sys.argv[2]
ctx = int(sys.argv[3]) if len(sys.argv) > 3 else 3
try:
    lines = open(path, errors="replace").read().split("\n")
except OSError as e:
    print(f"!! {path}: {e}")
    sys.exit(1)
rx = re.compile(pat)
n = 0
for i, line in enumerate(lines):
    if rx.search(line):
        n += 1
        lo = max(0, i - ctx)
        hi = min(len(lines), i + ctx + 1)
        print(f"--- {path}:{i+1} ---")
        for j in range(lo, hi):
            print(f"{j+1}: {lines[j]}")
print(f"[{n} matches in {path}]")
