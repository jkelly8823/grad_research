  bool IsAllowedHost(const std::string& host_with_port) const {
    std::string host = TrimPort(host_with_port);
    return host.empty() || IsIPAddress(host)
           || node::StringEqualNoCase(host.data(), "localhost");
  }

  bool parsing_value_;
  llhttp_t parser_;