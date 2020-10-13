#ifndef GCC_HANDLER_H
#define GCC_HANDLER_H
#include <iostream>
#include "stdafx.h"
#include <map>

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

class handler {
public:
  typedef struct VIDEO_DETAILS {
    std::string name;
    std::string url;
    std::string rtmp;
    std::string rtsp;
    std::string filepath;
    int status;
    VIDEO_DETAILS(){};
    VIDEO_DETAILS(std::string n, std::string u, std::string rt, std::string rs, std::string f,
                  int s)
        : name(n), url(u), rtmp(rt), rtsp(rs), filepath(f), status(s) {
      ;
    };
  } VIDEO_DETAILS;

  std::map<std::string, VIDEO_DETAILS> cache;

  std::map<std::string, std::string> cache2;

  handler() = default;

  explicit handler(utility::string_t url);

  virtual ~handler() = default;

  pplx::task<void> open() { return listener.open(); }

  pplx::task<void> close() { return listener.close(); }

protected:
private:
  void handle_get(http_request message);

  void handle_post(http_request message);

  void handle_delete(http_request message);
  std::vector<utility::string_t> requestPath(const http_request &message);
  void handle_post_stream(http_request message);
  void handle_get_stream(http_request message);
  void handle_get_stream_name(http_request& message, std::string& name);
  http_listener listener;
};

#endif // GCC_HANDLER_H
