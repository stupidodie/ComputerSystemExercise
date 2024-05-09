unsigned char quantize(unsigned char red, unsigned char green,
                       unsigned char blue) {
  return (red >> 5 << 5) + (green >> 5 << 2) + (blue >> 6);
}
