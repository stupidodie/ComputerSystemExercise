def hex_to_int(hex: bytes) -> int:
    result = 0
    for b in reversed(hex):
        result = (result << 8) + b
    return result


# print(pixels[0][0], pixels[0][width - 1])
# (0,0) -> (0,height-1)
# (x,0) -> (0,height-1-x)
# (height-1,0->(0,0)
# (0,width-1) -> (width-1,height-1)
# (height-1,width-1)->(width-1,0)
# (x,y)-> (y, height-1-x)


def right_rotate(pixels: list[list[list[int]]], width: int, height: int, deep: int):
    # tmp = [[[0 for _ in range(deep)] for _ in range(height)] for _ in range(width)]
    result = []
    for i in range(width):
        for j in range(height):
            for k in range(deep):
                # tmp[i][j][k] = pixels[j][height - 1 - i][k]
                result.append(pixels[j][height - 1 - i][k])
    return result


with open("teapot.bmp", "rb") as f:
    img = f.read()
assert img[0] == ord("B")
assert img[1] == ord("M")
size = hex_to_int(img[2:6])
start_point = hex_to_int(img[10:14])
width = hex_to_int(img[18:22])
height = hex_to_int(img[22:26])
deep = int(hex_to_int(img[28:30]) / 8)
pixels: list[list[list[int]]] = [
    [[0 for _ in range(deep)] for _ in range(width)] for _ in range(height)
]
for index in range(0, width * height):
    for deep_index in range(deep):
        pixels[int(index / width)][(index % width)][deep_index] = img[
            start_point + index * deep + deep_index
        ]

with open("tmp.bmp", "wb+") as f:
    new_img = []
    for byte in img[:start_point]:
        new_img.append(byte)
    new_img.extend(right_rotate(pixels, width, height, deep))
    f.write(bytes(new_img))
