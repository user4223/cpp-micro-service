
#pragma once

#include "lib/api/include/IRouteRegistry.h"

#include <map>
#include <string>

namespace Common
{
  class CRouteRegistry : public API::IRouteRegistry
  {
    typedef std::map<API::Method, EndpointMapType> RoutingMapType;

  public:
    CRouteRegistry();

    virtual IRouteRegistry&
    add(std::string endpoint, std::vector<API::Method> methods,
        HandlerFunctionType handler) override;

    virtual std::vector<web::http::methods>
    getMethods() const override;

    virtual EndpointMapType
    getHandler(API::Method method) const override;

  private:
    RoutingMapType m_routingMap;
  };

} // namespace Common
