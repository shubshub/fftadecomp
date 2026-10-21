import re, sys
for path in sys.argv[1:]:
    try:
        lines = open(path, errors="replace").read().split("\n")
    except OSError as e:
        print(f"!! {path}: {e}")
        continue
    pat = re.compile(sys.argv[0]) if False else None
print("use: tmp_grep.py <file> <regex> [ctx]")
