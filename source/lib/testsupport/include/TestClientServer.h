
#pragma once

#include <cpprest/http_client.h>
#include <cpprest/http_listener.h>
#include <cpprest/http_msg.h>
#include <cpprest/uri.h>

#include <memory>

namespace TestSupport
{
  struct TestClientServer
  {
  public:
    TestClientServer();

    web::http::http_response
    request(web::uri requestUri);

  private:
    web::uri m_baseUri;
    web::http::experimental::listener::http_listener m_listener;
    web::http::client::http_client m_client;
  };
} // namespace TestSupport
