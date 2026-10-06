# @category Greenwood
# @runtime PyGhidra

from collections import deque
from pathlib import Path

program = currentProgram
listing = program.getListing()
fm = program.getFunctionManager()
refmgr = program.getReferenceManager()

# Repo-relative: this script lives at tools/ghidra/Reachability.py.
ROOTS = str(Path(__file__).resolve().parents[2] / "symbols" / "functions-by-file.tsv")


def load_game_seeds():
    seeds = []
    with open(ROOTS) as fh:
        for line in fh:
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            try:
                seeds.append(int(line.split("\t")[0], 16))
            except ValueError:
                continue
    return seeds


def entry_seed():
    for sym in program.getSymbolTable().getAllSymbols(True):
        if sym.getName() == "entry":
            return sym.getAddress().getOffset()
    return None


def bfs(seeds):
    reached = {}
    hops = {}
    queue = deque()
    for seed in seeds:
        fn = fm.getFunctionContaining(toAddr(seed))
        if fn is None:
            continue
        key = fn.getEntryPoint().getOffset()
        if key in reached:
            continue
        reached[key] = fn
        hops[key] = 0
        queue.append((key, 0, 0))

    visited_data = set()
    while queue:
        addr, dist, kind = queue.popleft()
        if kind == 0:
            fn = reached.get(addr)
            if fn is None:
                continue
            for insn in listing.getInstructions(fn.getBody(), True):
                for ref in insn.getReferencesFrom():
                    try:
                        tgt = ref.getToAddress().getOffset()
                    except Exception:
                        continue
                    fn2 = fm.getFunctionContaining(toAddr(tgt))
                    if fn2 is not None:
                        key = fn2.getEntryPoint().getOffset()
                        if key not in reached:
                            reached[key] = fn2
                            hops[key] = dist + 1
                            queue.append((key, dist + 1, 0))
                    elif tgt not in visited_data:
                        visited_data.add(tgt)
                        queue.append((tgt, dist + 1, 1))
        else:
            for ref in refmgr.getReferencesFrom(toAddr(addr)):
                try:
                    tgt = ref.getToAddress().getOffset()
                except Exception:
                    continue
                fn2 = fm.getFunctionContaining(toAddr(tgt))
                if fn2 is not None:
                    key = fn2.getEntryPoint().getOffset()
                    if key not in reached:
                        reached[key] = fn2
                        hops[key] = dist + 1
                        queue.append((key, dist + 1, 0))
                elif tgt not in visited_data:
                    visited_data.add(tgt)
                    queue.append((tgt, dist + 1, 1))
    return reached, hops


game_reached, game_hops = bfs(load_game_seeds())
entry = entry_seed()
if entry is None:
    entry_reached, entry_hops = {}, {}
else:
    entry_reached, entry_hops = bfs([entry])

print("# SUMMARY game_seeds=%d game_reached=%d entry_reached=%d" % (
    len(load_game_seeds()), len(game_reached), len(entry_reached)))

for fn in fm.getFunctions(True):
    addr = fn.getEntryPoint().getOffset()
    body = fn.getBody()
    size = body.getNumAddresses() if body else 0
    gr = 1 if addr in game_reached else 0
    er = 1 if addr in entry_reached else 0
    print("%08x\t%08x\t%s\t%d\t%d\t%d\t%d" % (
        addr, size, fn.getName(), gr, game_hops.get(addr, -1), er, entry_hops.get(addr, -1)))
