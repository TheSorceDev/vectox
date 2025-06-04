from PIL import Image
import sys
import os

def rgba_to_argb_hex(r, g, b, a):
    return f"{a:02X}{r:02X}{g:02X}{b:02X}"

def export_compact_bitmap_string(png_path, out_path):
    img = Image.open(png_path).convert("RGBA")
    pixels = list(img.getdata())
    width, height = img.size

    output = []
    last = rgba_to_argb_hex(*pixels[0])
    count = 1

    def flush():
        if count == 1:
            output.append(last)
        else:
            output.append(f"~{count:02X}{last}")

    for px in pixels[1:]:
        curr = rgba_to_argb_hex(*px)
        if curr == last and count < 255:
            count += 1
        else:
            flush()
            last = curr
            count = 1
    flush()

    bitmap_string = "".join(output)

    var_name = os.path.splitext(os.path.basename(png_path))[0].replace('.', '_').upper()

    with open(out_path, "w") as f:
        f.write(f"// Auto-generated from {os.path.basename(png_path)}\n")
        f.write(f"#define {var_name}_WIDTH {width}\n")
        f.write(f"#define {var_name}_HEIGHT {height}\n")
        f.write(f"const char* {var_name}_BITMAP =\n")
        line_len = 128
        for i in range(0, len(bitmap_string), line_len):
            chunk = bitmap_string[i:i + line_len]
            f.write(f"    \"{chunk}\"\n")
        f.write(";\n")

    print(f"Saved to {out_path}")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python png_to_bitmap_string.py input.png output.h")
    else:
        export_compact_bitmap_string(sys.argv[1], sys.argv[2])
