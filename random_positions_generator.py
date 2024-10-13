import random

line = list(range(0, 9))
for _ in range(8):
    random.shuffle(line)
    print(*line)
