
#include "lib/utility/include/CInterruptHandler.hpp"

#include "pplx/threadpool.h"

#include <cpprest/http_listener.h>
#include <cpprest/uri.h>

#include <iostream>
#include <map>
#include <memory>
#include <string>

#include <boost/program_options.hpp>

static const std::map<std::string, std::string> carEngineMap =
    { ///< TODO Move out to persistence service
        {"delorean", "flux capacitor"},
        {"prius", "hybrid"},
        {"mustang", "v8"}};

int
main(int argc, char const** argv)
{
  namespace bpo = boost::program_options;

  bpo::options_description general("General options");
  general.add_options()("help,h", "This help message")(
      "hostname,n", bpo::value<std::string>()->default_value("localhost"), "Hostname to listen on");

  bpo::variables_map vm;
  bpo::store(bpo::parse_command_line(argc, argv, general), vm);
  bpo::notify(vm);

  if (vm.count("help"))
  {
    std::cout << general << "\n";
    return 0;
  }

  crossplat::threadpool::initialize_with_threads(
      1); ///< Just avoid 40 threads created by http::listener by default

  auto uri = web::uri_builder("http://")
                 .set_host(vm["hostname"].as<std::string>())
                 .set_port(std::to_string(6565))
                 .set_path("v1.0");
  auto listener = web::http::experimental::listener::http_listener(
      web::uri(uri.append_path("/car/.*").to_uri()));
  listener.support(web::http::methods::GET, [](auto request) {
    const auto path = web::uri::decode(request.relative_uri().path());
    std::cout << "Got request on: " << path << std::endl;

    const auto parts = web::uri::split_path(path);
    if (parts.size() < 2)
    {
      return request.reply(web::http::status_codes::NotFound);
    }

    const auto engine = carEngineMap.find(parts[1]);
    if (engine == carEngineMap.end())
    {
      return request.reply(web::http::status_codes::NotFound);
    }

    auto response = web::json::value::object();
    response["engine"] = web::json::value(engine->second);
    return request.reply(web::http::status_codes::OK, response);
  });
  listener.open().wait();
  std::cout << "Listening on: " << uri.to_string() << std::endl;

  Utility::awaitInterrupt();

  listener.close().wait();
  std::cout << "Got signal, terminating..." << std::endl;
  return 0;
}
