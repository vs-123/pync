import pync

for _ in range(256):
   pync.increment()

print(f"[PYNC.PY] INCREMENT LOOP: {pync.get_number()}")

pync.increment()
pync.increment()
print(f"[PYNC.PY] INCREMENT TWICE: {pync.get_number()}")

pync.decrement()
print(f"[PYNC.PY] DECREMENT: {pync.get_number()}")

pync.reset()
print(f"[PYNC.PY] RESET: {pync.get_number()}")
