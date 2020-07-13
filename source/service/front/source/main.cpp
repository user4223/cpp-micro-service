#include "lib/common/include/CRouteRegistry.h"
#include "lib/common/include/CRouter.h"
#include "lib/utility/include/CInterruptHandler.hpp"

#include "pplx/threadpool.h"

#include <map>
#include <memory>
#include <string>

static const std::map<std::string, std::string> carEngineMap =
    { ///< TODO Move out to persistence service
        {"delorean", "flux capacitor"},
        {"prius", "hybrid"},
        {"mustang", "v8"}};

int
main(int argc, char const** argv)
{

  crossplat::threadpool::initialize_with_threads(
      1); ///< Just avoid 40 threads created by http::listener by default

  auto handler = std::make_unique<Common::CRouteRegistry>();
  handler->add("/car/.*", {API::Method::Get},
               [](API::Method method, web::http::http_request request) {
                 const auto path = web::uri::decode(request.relative_uri().path());

                 std::cout << "Got request on: " << path << std::endl;

                 const auto parts = web::uri::split_path(path);
                 if (parts.size() < 2) return request.reply(web::http::status_codes::NotFound);

                 const auto engine = carEngineMap.find(parts[1]);
                 if (engine == carEngineMap.end())
                   return request.reply(web::http::status_codes::NotFound);

                 auto response = web::json::value::object();
                 response["engine"] = web::json::value(engine->second);
                 return request.reply(web::http::status_codes::OK, response);
               });

  // TODO Validate host argument
  const auto uri =
      web::uri_builder("http://").set_host(argv[1]).set_port(std::to_string(6565)).set_path("v1.0");
  auto router = std::make_unique<Common::CRouter>(uri.to_uri(), *handler);
  std::cout << "Listening on: " << uri.to_string() << std::endl;

  Utility::awaitInterrupt();

  std::cout << "Got signal, terminating..." << std::endl;
  return 0;
}
