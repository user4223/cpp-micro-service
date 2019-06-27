#include "lib/common/include/CRouteRegistry.h"
#include "lib/common/include/CRouter.h"
#include "lib/utility/include/CInterruptHandler.hpp"

#include "pplx/threadpool.h"

#include <map>
#include <memory>

static const auto carEngineMap = []() { ///< TODO Move out to persistence service
  std::map<std::string, std::string> m;
  m.insert(std::make_pair("delorean", "flux capacitor"));
  m.insert(std::make_pair("prius", "hybrid"));
  m.insert(std::make_pair("mustang", "v8"));
  return m;
}();

int
main(int argc, char const** argv)
{
  crossplat::threadpool::initialize_with_threads(
      1); ///< Just avoid 40 threads created by http::listener by default

  auto handler = std::make_unique<Common::CRouteRegistry>();
  handler->add(
      "/car/.*", {API::Method::Get}, [](API::Method method, web::http::http_request request) {
        const auto parts = web::uri::split_path(web::uri::decode(request.relative_uri().path()));
        if (parts.size() < 2) return request.reply(web::http::status_codes::NotFound);

        const auto engine = carEngineMap.find(parts[1]);
        if (engine == carEngineMap.end()) return request.reply(web::http::status_codes::NotFound);

        auto response = web::json::value::object();
        response["engine"] = web::json::value(engine->second);
        request.reply(web::http::status_codes::OK, response);
      });

  const auto uri = web::uri("http://localhost:6565/v1.0");
  auto router = std::make_unique<Common::CRouter>(uri, *handler);
  std::cout << "Listening on: " << uri.to_string() << std::endl;

  Utility::awaitInterrupt();

  std::cout << "Got signal, terminating..." << std::endl;
  return 0;
}
