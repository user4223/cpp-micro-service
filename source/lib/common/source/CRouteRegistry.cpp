
#include "../include/CRouteRegistry.h"

namespace Common
{
  CRouteRegistry::CRouteRegistry()
      : m_routingMap()
  {}

  API::IRouteRegistry& CRouteRegistry::add(std::string endpoint, std::vector<API::Method> methods,
                                           HandlerFunctionType handler)
  {
    for (auto method : methods)
    {
      m_routingMap[method].insert(std::make_pair(endpoint, handler));
    }
    return *this;
  }

  std::vector<web::http::methods> CRouteRegistry::getMethods() const
  {
    return std::vector<web::http::methods>();
  }

  CRouteRegistry::EndpointMapType CRouteRegistry::getHandler(API::Method method) const
  {
    auto const iterator = m_routingMap.find(method);
    return iterator == m_routingMap.end() ? EndpointMapType() : iterator->second;
  }

} // namespace Common
