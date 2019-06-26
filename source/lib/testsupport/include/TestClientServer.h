
#pragma once

#include "lib/api/include/IRouteRegistry.h"
#include "lib/api/include/IRouter.h"

#include <cpprest/http_client.h>
#include <cpprest/http_msg.h>
#include <cpprest/uri.h>

#include <memory>

namespace TestSupport
{
  struct TestClientServer
  {
  public:
    TestClientServer(std::unique_ptr<API::IRouteRegistry> registry);

    web::http::http_response
    request(web::uri requestUri);

  private:
    web::uri m_baseUri;
    std::unique_ptr<API::IRouteRegistry> m_registry;
    std::unique_ptr<API::IRouter> m_router;
    web::http::client::http_client m_client;
  };
} // namespace TestSupport
