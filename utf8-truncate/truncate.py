import sys


def truncate(s: bytes, n: int) -> bytes:
    if n >= len(s):
        return s
    while n > 0 and (s[n] >> 6) == 0b10:
        n -= 1
    return s[:n]


with open("./cases", "rb") as f:
    while True:
        case = f.readline()
        if not case:
            break
        sys.stdout.buffer.write(truncate(case[1:-1], case[0]) + b"\n")
