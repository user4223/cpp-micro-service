#pragma once

#include <cpprest/http_msg.h>

namespace API
{

  enum class Method
  {
    Get
  };

  struct IRouteRegistry
  {
    typedef std::function<void(Method, web::http::http_request)> HandlerFunctionType;
    typedef std::map<std::string, HandlerFunctionType> EndpointMapType;

    virtual ~IRouteRegistry() = default;

    virtual IRouteRegistry&
    add(std::string endpoint, std::vector<Method> methods, HandlerFunctionType handler) = 0;

    virtual std::vector<web::http::methods>
    getMethods() const = 0;

    virtual EndpointMapType
    getHandler(Method method) const = 0;
  };
} // namespace API
