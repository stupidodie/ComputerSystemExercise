def encode(number: int) -> bytes:
    byte_array = []
    while number > 0:
        res = number & 0x7F
        number = number >> 7
        if number == 0:
            byte_array.append(res)
        else:
            byte_array.append(res + 0x80)
    return bytes(byte_array)


def decode(bytes_array: bytes) -> int:
    result = 0
    shift = 0
    for byte in bytes_array:
        byte = byte & 0x7F
        result += byte << shift
        shift = shift + 7
    return result


assert encode(150) == b"\x96\x01"
assert decode(b"\x96\x01") == 150
for n in range(1 << 30):
    assert decode(encode(n)) == n
