input_file = "minion2.gif"
output_file = "minion2.h"

with open(input_file, "rb") as f:
    byte_data = f.read()

with open(output_file, "w") as f:
    f.write("// gif_image.h\n")
    f.write("#ifndef GIF_IMAGE_H\n#define GIF_IMAGE_H\n\n")
    f.write("const unsigned char gif_image[] = {\n")
    for i, byte in enumerate(byte_data):
        if i % 12 == 0:
            f.write("\n  ")
        f.write(f"0x{byte:02X}, ")
    f.write("\n};\n\n")
    f.write(f"const unsigned int gif_image_len = {len(byte_data)};\n\n")
    f.write("#endif // GIF_IMAGE_H\n")
