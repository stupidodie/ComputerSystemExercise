import re


def hex_to_number(rgb_hex: str) -> int:
    return int(rgb_hex, 16)


def hex_to_rgb(color: str) -> str:
    number_size = len(color)
    if number_size == 7:
        step = 2
        number_color = "rgb("
        for i in range(1, number_size, step):
            if i != 1:
                number_color += " "
            number_color += str(hex_to_number(color[i : i + step]))
        number_color += ")"
        return number_color
    elif number_size == 9:
        step = 2
        number_color = "rgba("
        for i in range(1, number_size - step, step):
            if i != 1:
                number_color += " "
            number_color += str(hex_to_number(color[i : i + step]))
        number_color += " / "
        number_color += str(hex_to_number(color[7:9]) / 255)[0:7]
        number_color += ")"
        return number_color
    elif number_size == 4:
        number_color = "rgb("
        for i in range(1, 4, 1):
            if i != 1:
                number_color += " "
            number_color += str(hex_to_number(color[i] + color[i]))
        number_color += ")"
        return number_color
    elif number_size == 5:
        number_color = "rgba("
        for i in range(1, 4, 1):
            if i != 1:
                number_color += " "
            number_color += str(hex_to_number(color[i] + color[i]))
        number_color += " / "
        number_color += str(hex_to_number(color[4] + color[4]) / 255)[0:7]
        number_color += ")"
        return number_color

    raise ValueError(f"can not handle arg {color}")


assert hex_to_rgb("#00ff00") == "rgb(0 255 0)"


def convert(match_obj):
    return hex_to_rgb(match_obj.group())


file_list = ["simple", "advanced"]
for file in file_list:
    with open(f"{file}.css", "r", encoding="utf-8") as read_css:
        css_text = read_css.read()
        converted_css = re.sub(r"#[0-9a-fA-F]+", convert, css_text)
        with open(f"{file}_expected.css", "r", encoding="utf-8") as expected_css:
            expected_text = expected_css.read()
            assert expected_text == converted_css
