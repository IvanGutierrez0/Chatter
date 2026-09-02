# Fonts documentation
## How to change fonts
Every font is a .h that includes an entire set of characters as a bitmap (hex). Then there is a data structure that contains for each character, the byte it starts on, dimensions (width and height), pixels to move the cursor after writing it and x and y offset:

```
const uint8_t Bitmap[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00....
}

const GFXglyph Glyphs[] PROGMEM = {
    {0, 0, 0, 2, 0, 1},     // 0x20 ' '
    {start_byte, width, height, cursor_move, x_off, y_off}
}

```

Every character starts at the beginning of one byte (fill with 0s untill the byte ends)

## Where to place the fonts file (.h)
The .h containing the font must be placed under the Adafruit GFX library folder, inside the fonts folder (in Ubuntu: home/Arduino/libraries/Adafruit_GFX_Library/Fonts)
