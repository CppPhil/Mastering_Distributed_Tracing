#include <jaegertracing/Tracer.h>

#include "tracing/create_span.hpp"

namespace tracing {
std::unique_ptr<opentracing::Span>
create_span(const tl::expected<std::unique_ptr<opentracing::SpanContext>,
                               util::error>& ctx,
            const std::string& operation_name) {
  return (!ctx.has_value() || *ctx == nullptr)
           ? opentracing::Tracer::Global()->StartSpan(operation_name)
           : opentracing::Tracer::Global()->StartSpan(
             operation_name, {opentracing::ChildOf(ctx->get())});
}
} // namespace tracing
