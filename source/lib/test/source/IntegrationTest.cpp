
#include <gtest/gtest.h>

#include "lib/common/include/CRouteRegistry.h"

#include "lib/testsupport/include/RequestHandler.h"
#include "lib/testsupport/include/TestClientServer.h"

using web::http::status_codes;
using web::json::value;

TEST(PathMatch, Integration)
{
  auto registry = std::make_unique<Common::CRouteRegistry>();
  (*registry)
      .add("/car", {API::Method::Get}, TestSupport::RequestHandler::uriParts(42))
      .add("/cat/.*", {API::Method::Get}, TestSupport::RequestHandler::uriParts(5))
      .add("/car/.*", {API::Method::Get}, TestSupport::RequestHandler::uriParts(23));

  auto response = TestSupport::TestClientServer(std::move(registry))
                      .request(web::uri_builder().append_path("car/delorean").to_uri());

  EXPECT_EQ(response.status_code(), status_codes::OK);
  auto json = response.extract_json().get();
  EXPECT_EQ(json.at("path").as_string(), "/car/delorean");
  EXPECT_EQ(json.at("id").as_integer(), 23);
}

TEST(NoMatch, Integration)
{
  auto registry = std::make_unique<Common::CRouteRegistry>();
  (*registry)
      .add("/fox.*", {API::Method::Get}, TestSupport::RequestHandler::uriParts(42))
      .add("/rabbit.*", {API::Method::Get}, TestSupport::RequestHandler::uriParts(5))
      .add("/cat.*", {API::Method::Get}, TestSupport::RequestHandler::uriParts(23));

  auto response = TestSupport::TestClientServer(std::move(registry))
                      .request(web::uri_builder().append_path("car").to_uri());

  EXPECT_EQ(response.status_code(), status_codes::NotFound);
}
