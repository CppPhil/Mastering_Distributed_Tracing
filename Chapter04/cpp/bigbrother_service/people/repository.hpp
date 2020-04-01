#pragma once
#include <optional>
#include <string>

#include <jaegertracing/Tracer.h>

#include <Poco/Data/Session.h>

#include <pl/noncopyable.hpp>

#include "model/person.hpp"

namespace e4::people {
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
} // namespace e4::people
