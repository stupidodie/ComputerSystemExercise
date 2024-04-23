import struct
import math


def conceal(s: str) -> float:
    assert len(str.encode(s)) <= 6
    bs = str.encode(s)
    first = b"\x7f"
    second = (0xF0 + len(bs)).to_bytes(1)
    padding = b"\x00" * (6 - len(bs))
    return struct.unpack(">d", first + second + padding + bs)[0]


def extract(x: float) -> str:
    bs = struct.pack(">d", x)
    n = bs[1] & 0x07
    return bs[-n:].decode()


x = "asdas"
assert x == extract(conceal(x))
assert math.isnan(conceal(x))
