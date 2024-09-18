                                 void* user_data) {
  Http2Session* session = static_cast<Http2Session*>(user_data);

  Debug(session, "invalid frame received, code: %d", lib_error_code);
  if (session->invalid_frame_count_++ > 1000 &&
      !IsReverted(SECURITY_REVERT_CVE_2019_9514)) {
    return 1;
  }