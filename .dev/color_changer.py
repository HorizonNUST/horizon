from typing import Dict, Tuple
from PIL import Image


def replace_colors(
    input_path: str,
    output_path: str,
    color_map: Dict[Tuple[int, int, int], Tuple[int, int, int]]
) -> None:
    """
    Replace specific RGB colors in an image using a provided mapping.

    Args:
        input_path: Path to the input image.
        output_path: Path to save the modified image.
        color_map: Dict of (from_color: to_color), both as RGB tuples.
    """
    image = Image.open(input_path).convert("RGBA")
    pixels = image.load()

    width, height = image.size

    for y in range(height):
        for x in range(width):
            r, g, b, a = pixels[x, y]
            key = (r, g, b)
            if key in color_map:
                nr, ng, nb = color_map[key]
                pixels[x, y] = (nr, ng, nb, a)

    image.save(output_path)


if __name__ == "__main__":
    mapping = {
        (255, 0, 0): (0, 255, 0),
        (0, 0, 255): (255, 255, 0)
    }

    replace_colors(
        input_path="input.png",
        output_path="output.png",
        color_map=mapping
    )
