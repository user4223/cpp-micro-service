
#include "lib/api/include/IRouteRegistry.h"

#include "cpprest/http_msg.h"
#include "cpprest/json.h"

namespace TestSupport
{
  namespace RequestHandler
  {
    auto uriParts(int id)
    {
      return [=](API::Method method, web::http::http_request request) {
        auto response = web::json::value::object();
        response["path"] =
            web::json::value::string(web::uri::decode(request.relative_uri().path()));
        response["query"] =
            web::json::value::string(web::uri::decode(request.relative_uri().query()));
        response["fragment"] =
            web::json::value::string(web::uri::decode(request.relative_uri().fragment()));
        response["id"] = web::json::value(id);
        request.reply(web::http::status_codes::OK, response);
      };
    }
  } // namespace RequestHandler
} // namespace TestSupport
