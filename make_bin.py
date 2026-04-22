"""
make_bin.py  –  convert racingIMG.h image arrays to SD-card binary files.

Each .bin file format:
  Bytes 0-1  : width  (uint16_t, little-endian)
  Bytes 2-3  : height (uint16_t, little-endian)
  Bytes 4..  : pixel data (uint16_t RGB565, little-endian, row-major)

Usage:
  python3 make_bin.py images/racingIMG.h  [output_dir]

Copy the generated .bin files to the root of a FAT-formatted SD card.
"""

import re, struct, sys, os

# Known image dimensions (width, height).
# All track tiles are full-screen 128x160.
# BlueBall is a small sprite — pixel count determines size.
KNOWN_DIMS = {
    "T17_20":           (128, 160),
    "T1_2":             (128, 160),
    "T3_5":             (128, 160),
    "T6_9":             (128, 160),
    "T10_11":           (128, 160),
    "T11_BackStraight": (128, 160),
    "T12_17":           (128, 160),
}

def infer_dims(name, n_pixels):
    if name in KNOWN_DIMS:
        w, h = KNOWN_DIMS[name]
        assert w * h == n_pixels, (
            f"{name}: expected {w*h} pixels for {w}x{h}, got {n_pixels}")
        return w, h
    # Fall back: store as a 1-row strip so width = pixel count, height = 1.
    # The caller must pass correct dims to SDImage_Draw.
    print(f"  WARNING: {name} has {n_pixels} pixels — unknown dims, "
          f"storing as {n_pixels}x1 strip")
    return n_pixels, 1

def convert(src, dst_dir):
    os.makedirs(dst_dir, exist_ok=True)
    with open(src, "r") as f:
        text = f.read()

    # Match:  const unsigned short NAME[] = { ... };
    pattern = re.compile(
        r'const\s+unsigned\s+short\s+(\w+)\s*\[\s*\]\s*=\s*\{([^}]*)\}',
        re.DOTALL)

    count = 0
    for m in pattern.finditer(text):
        name = m.group(1)
        pixels = [int(x, 16) for x in re.findall(r'0x[0-9A-Fa-f]+', m.group(2))]
        w, h = infer_dims(name, len(pixels))

        out_path = os.path.join(dst_dir, name + ".bin")
        with open(out_path, "wb") as f:
            f.write(struct.pack("<HH", w, h))
            for p in pixels:
                f.write(struct.pack("<H", p))

        print(f"  {name}.bin  {w}x{h}  ({len(pixels)*2} bytes pixel data)")
        count += 1

    print(f"\nDone: {count} files written to '{dst_dir}/'")
    print("Copy all .bin files to the root of your FAT SD card.")

if __name__ == "__main__":
    src = sys.argv[1] if len(sys.argv) > 1 else "images/racingIMG.h"
    dst = sys.argv[2] if len(sys.argv) > 2 else "sdcard_images"
    convert(src, dst)
