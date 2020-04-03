#pragma once
#include <optional>
#include <string>

#include <jaegertracing/Tracer.h>

#include <Poco/Data/Session.h>

#include <pl/noncopyable.hpp>

#include "model/person.hpp"

namespace e5::people {
class repository {
public:
  PL_NONCOPYABLE(repository);

  repository();

  ~repository();

  model::person get_person(std::string name,
                           const opentracing::SpanContext* ctx) const;

private:
  mutable std::optional<Poco::Data::Session> session_;
};
} // namespace e5::people
