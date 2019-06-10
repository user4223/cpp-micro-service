
#pragma once

#include <cpprest/http_listener.h>
#include <cpprest/uri.h>
#include <pplx/pplxtasks.h>

#include "lib/api/include/IRouteRegistry.h"
#include "lib/api/include/IRouter.h"

namespace Common
{
  class CRouter : public API::IRouter
  {
  public:
    CRouter(web::uri baseUri, API::IRouteRegistry& registry);
    virtual ~CRouter();

  private:
    web::uri m_baseUri;
    web::http::experimental::listener::http_listener m_listener;
  };
} // namespace Common