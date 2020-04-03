#pragma once
#include <optional>
#include <string>

#include <jaegertracing/Tracer.h>

#include <Poco/Data/Session.h>

#include <pl/noncopyable.hpp>

#include "model/person.hpp"

namespace e5::people {
/**
 * Type for the people repository.
 */
class repository {
public:
  PL_NONCOPYABLE(repository);

  /**
   * Default constructor.
   */
  repository();

  /**
   * Destructor.
   */
  ~repository();

  /**
   * Fetches a person from the database.
   * @param name The name to find the person by.
   * @param ctx The tracing SpanContext to use to create a child span from
   * @return The resulting person.
   * @note If there's no tuple in the database with name `name` the person
   *       returned won't have a title or description.
   */
  model::person get_person(std::string name,
                           const opentracing::SpanContext* ctx) const;

private:
  mutable std::optional<Poco::Data::Session> session_;
};
} // namespace e5::people
