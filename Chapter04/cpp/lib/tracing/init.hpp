#pragma once
#include <string>

namespace tracing {
/**
 * Initializes the global jaegertracing Tracer singleton.
 * @param service What to call this service in the Tracer.
 */
void init(const std::string& service);
} // namespace tracing
