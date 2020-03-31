#pragma once
#include <optional>
#include <string>

#include <tl/optional.hpp>

#include <jaegertracing/Tracer.h>

#include <Poco/Data/Session.h>

#include "model/person.hpp"

namespace e4::people {
class repository {
public:
  repository();

  repository(const repository&) = delete;

  repository& operator=(const repository&) = delete;

  ~repository();

  tl::optional<model::person>
  get_person(std::string name, const opentracing::SpanContext* ctx) const;

private:
  mutable std::optional<Poco::Data::Session> session_;
};
} // namespace e4::people
