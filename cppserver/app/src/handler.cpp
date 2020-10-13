#include "../include/handler.h"

handler::handler(utility::string_t url) : listener(url) {
  listener.support(methods::GET, std::bind(&handler::handle_get, this,
                                           std::placeholders::_1));
  listener.support(methods::POST, std::bind(&handler::handle_post, this,
                                            std::placeholders::_1));
  listener.support(methods::DEL, std::bind(&handler::handle_delete, this,
                                           std::placeholders::_1));
}

std::vector<utility::string_t>
handler::requestPath(const http_request &message) {
  auto relativePath = uri::decode(message.relative_uri().path());
  return uri::split_path(relativePath);
}

void handler::handle_get(http_request message) {
  json::value jsonresponse;
  auto path = requestPath(message);
  if (path.size() > 0) {
    if (path[0] == "stream") {
      if (path.size() == 1) {
        return handle_get_stream(message);
      } else if (path.size() == 2) {
        return handle_get_stream_name(message, path[1]);
      }
    }
  }
  jsonresponse[U("success")] = json::value::string(U("false"));
  message.reply(status_codes::OK, jsonresponse);
};

void handler::handle_get_stream(http_request message) {
  auto path = requestPath(message);
  json::value jsonresponse;
  int count = 0;
  for (auto &c : cache) {
    jsonresponse[count++] = json::value::string(c.first);
  }
  message.reply(status_codes::OK, jsonresponse);
}

void handler::handle_get_stream_name(http_request &message, std::string &name) {
  auto path = requestPath(message);
  json::value jsonresponse;
  if (cache.find(name) != cache.end()) {
    if (cache[name].status == 0) {
      std::string cmd =
          "ffmpeg -re -stream_loop -1 -i " + cache[name].filepath +
          " -map 0 -c copy -f flv rtmp://localhost/stream/" + name + " &";
      int status = system(cmd.c_str());
      if (status == 0) {
        cache[name].status = 1;
        cache[name].rtmp = ("rtmp://localhost:1935/stream/" + name);
      }
    }
    jsonresponse[name] = json::value::string(name);
    jsonresponse["url"] = json::value::string(cache[name].url);
    jsonresponse["rtmp"] = json::value::string(cache[name].rtmp);
    jsonresponse["rtsp"] = json::value::string(cache[name].rtsp);
  }
  message.reply(status_codes::OK, jsonresponse);
}

void handler::handle_post(http_request message) {
  auto response = json::value::object();
  json::value jsonresponse;
  auto path = requestPath(message);

  if (path.size() > 0 &&
      message.headers().content_type() == "application/json" &&
      path[0] == "stream") {
    return handle_post_stream(message);
  }
  jsonresponse[U("success")] = json::value::string(U("false"));
  message.reply(status_codes::OK, jsonresponse);
};

void handler::handle_post_stream(http_request message) {
  json::value jsonresponse;
  try {
    json::value j_found = message.extract_json().get();
    std::string name = j_found[U("name")].as_string();
    std::string url = j_found[U("url")].as_string();
    if (!name.empty() && !url.empty() && cache.find(name) == cache.end()) {
      std::string cmd = "wget " + url + " -P " + "/var/www/";
      int status = system(cmd.c_str());
      if (status == 0) {

        std::string filename = url.substr(url.find_last_of("/\\") + 1);
        std::string filepath = "/var/www/" + filename;
        std::cout << "path: " << filepath << std::endl;
        VIDEO_DETAILS v(name, url, "", "", filepath, 0);
        cache[name] = v;
        std::cout << "status: " << status << std::endl;
        jsonresponse[U("success")] = json::value::string(U("true"));
        message.reply(status_codes::OK, jsonresponse);
        return;
      }
    }
    jsonresponse[U("success")] = json::value::string(U("false"));
    message.reply(status_codes::OK, jsonresponse);
  } catch (...) {
    jsonresponse[U("success")] = json::value::string(U("false"));
    message.reply(status_codes::OK, jsonresponse);
  }
}

void handler::handle_delete(http_request message) {
  json::value jsonresponse;
  auto path = requestPath(message);
  if (path.size() == 2) {
    if (path[0] == "stream") {
      if (cache.find(path[1]) != cache.end()) {
        cache.erase(path[1]);
        jsonresponse[U("success")] = json::value::string(U("true"));
        message.reply(status_codes::OK, jsonresponse);
        return;
      }
    }
  }
  jsonresponse[U("success")] = json::value::string(U("false"));
  message.reply(status_codes::OK, jsonresponse);
};