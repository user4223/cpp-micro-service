
#include "../include/CInterruptHandler.hpp"

#include <condition_variable>
#include <mutex>
#include <signal.h>

static std::condition_variable s_condition;
static std::mutex s_mutex;

void handler(int type)
{
  if (type == SIGINT)
  {
    s_condition.notify_one();
  }
}

struct HandlerRAII
{
  HandlerRAII()
      : m_old(signal(SIGINT, handler))
  {}

  ~HandlerRAII() { signal(SIGINT, m_old); }

private:
  void (*m_old)(int);
};

namespace Utility
{
  void awaitInterrupt()
  {
    HandlerRAII raii;

    std::unique_lock<std::mutex> lock{s_mutex};
    s_condition.wait(lock);
  };
} // namespace Utility
