
#include "../include/CRouter.h"

#include <iostream>
#include <regex>

namespace Common
{
  CRouter::CRouter(web::uri baseUri, API::IRouteRegistry& registry)
      : m_baseUri(baseUri)
      , m_listener()
  {
    m_listener = web::http::experimental::listener::http_listener(web::uri(m_baseUri));
    /** @todo Add handlers for all registered methods.
     */
    auto const methods = registry.getMethods();
    m_listener.support(web::http::methods::GET, [this, &registry](auto request) {
      const auto handlerMap(registry.getHandler(API::Method::Get));
      const auto relativePath(web::uri::decode(request.relative_uri().path()));
      for (auto& handler : handlerMap)
      {
        if (std::regex_match(relativePath, std::regex(handler.first, std::regex_constants::icase)))
        {
          handler.second(API::Method::Get, request);
          return;
        }
      }
      request.reply(web::http::status_codes::NotFound);
    });
    m_listener.open().wait();
  }

  CRouter::~CRouter()
  {
    try
    {
      m_listener.close().wait();
    }
    catch (std::exception const& e)
    {
      ///< @todo Log it
    }
  }
} // namespace Common