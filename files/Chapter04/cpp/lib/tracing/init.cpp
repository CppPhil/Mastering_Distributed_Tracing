#include <string>

#include <jaegertracing/Config.h>
#include <jaegertracing/Constants.h>
#include <jaegertracing/Tracer.h>

#include "tracing/init.hpp"

namespace tracing {
void init(const std::string& service) {
  const auto is_disabled = false;

  const std::string sampler_type = jaegertracing::kSamplerTypeConst;
  const auto sampling_probability = 1.0;
  const jaegertracing::samplers::Config sampler(sampler_type,
                                                sampling_probability);

  const jaegertracing::reporters::Config reporter(
    /* queueSize */ jaegertracing::reporters::Config::kDefaultQueueSize,
    /* bufferFlushInterval */
    jaegertracing::reporters::Config::defaultBufferFlushInterval(),
    /* logSpans */ true);

  const jaegertracing::Config cfg(is_disabled, sampler, reporter);

  std::shared_ptr<opentracing::Tracer> tracer(jaegertracing::Tracer::make(
    service, cfg, jaegertracing::logging::consoleLogger()));

  opentracing::Tracer::InitGlobal(std::move(tracer));
}
} // namespace tracing
