from PIL import Image
import numpy as np

input_image = "font.png"
output_header = "font_bitmap.h"
cell_width, cell_height = 16, 16

characters = list("ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                  "abcdefghijklmnopqrstuvwxyz"
                  "0123456789"
                  "+-*/_\\&%$\"?!'#~.,;:`=()[]{}")

img = Image.open(input_image).convert("RGB")
img_np = np.array(img)
cols = img.width // cell_width
rows = img.height // cell_height

characters += [f"unused{i}" for i in range(cols * rows - len(characters))]

def rgba_to_vcolor(r, g, b):
    r, g, b = int(r), int(g), int(b)
    if r == 0 and g == 0 and b == 0:
        return 0x00FFFFFF
    alpha = (r + g + b) // 3
    return (alpha << 24) | 0xFFFFFF

header_lines = [
    "#ifndef FONT_BITMAP_H\n",
    "#define FONT_BITMAP_H\n",
    '#include "drivers/video/utils/include/video_utils.h"\n',
    "typedef uint32_t VColor;\n"
]

footer_lines = [
    "#endif"
]

for index, char in enumerate(characters):
    col = index % cols
    row = index // cols
    x0 = col * cell_width
    y0 = row * cell_height
    cell = img_np[y0:y0+cell_height, x0:x0+cell_width]

    if len(char) == 1 and char.isalnum():
        varname = f"bitmap_char_{char}"
    elif len(char) == 1:
        varname = f"bitmap_char_{ord(char)}"
    else:
        varname = f"bitmap_char_{char}"

    header_lines.append(f"VColor {varname}[{cell_height}][{cell_width}] = {{")
    for row_pixels in cell:
        values = ", ".join(
            f"0x{rgba_to_vcolor(*px):08X}" for px in row_pixels
        )
        header_lines.append(f"    {{ {values} }},")
    header_lines.append("};\n")

header_lines.extend(footer_lines)
with open(output_header, "w") as f:
    f.write("\n".join(header_lines))

print(f"✔ Font exported to '{output_header}'")
