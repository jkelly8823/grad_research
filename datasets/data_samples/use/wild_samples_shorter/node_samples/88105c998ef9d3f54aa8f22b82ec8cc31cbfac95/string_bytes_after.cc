                              size_t* chars_written) {
  uint16_t* const dst = reinterpret_cast<uint16_t*>(buf);

  size_t max_chars = buflen / sizeof(*dst);
  if (max_chars == 0) {
    return 0;
  }

  size_t nchars;
  size_t alignment = reinterpret_cast<uintptr_t>(dst) % sizeof(*dst);
  if (alignment == 0) {
    nchars = str->Write(dst, 0, max_chars, flags);