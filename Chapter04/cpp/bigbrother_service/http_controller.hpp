#pragma once
#include <drogon/HttpController.h>

#include <pl/noncopyable.hpp>

namespace e5 {

namespace people {
class repository;
} // namespace people

/**
 * The HTTP controller type for the bigbrother_service.
 */
class http_controller : public drogon::HttpController<http_controller, false> {
public:
  PL_NONCOPYABLE(http_controller);

  /**
   * Default constructor.
   */
  http_controller();

  /**
   * Sets the repository pointer.
   * @param repo The repository to use.
   * @warning Must be called immediately after creation of this object.
   * @note drogon will only accept HTTP controller types that are
   *       default constructible.
   */
  void set_repo(const people::repository& repo);

  METHOD_LIST_BEGIN
    ADD_METHOD_TO(http_controller::handle_get_person, "/getPerson/{name}",
                  drogon::Get);
  METHOD_LIST_END

private:
  /**
   * Handles a /getPerson request.
   * @param req The HTTP request.
   * @param callback The callback.
   * @param name The name of the person to fetch from the database.
   */
  void handle_get_person(
    const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback,
    std::string&& name);

  const people::repository* repo_;
};
} // namespace e5
