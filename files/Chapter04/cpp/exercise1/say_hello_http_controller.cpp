#include "say_hello_http_controller.hpp"

namespace e1 {
namespace 
{
std::string format_greeting(
    const std::string& name,
    const std::string& title, 
    const std::string& description
)
{
    std::string response = "Hello, ";

    if (!title.empty())
        response += title + " ";

    response += name + "!";

    if (!description.empty())
        response += " " + description;

    return response;
}

std::string say_hello(people::repository& repo, std::string&& name)
{
    const model::person person(repo.get_person(std::move(name)));

    return format_greeting(
        person.name(),
        person.title(),
        person.description()
    );
}
} // namespace

say_hello_http_controller::say_hello_http_controller(people::repository& repo)
    : repo_(repo) {}

void say_hello_http_controller::handle_say_hello(const drogon::HttpRequestPtr& req,
                          std::function<void (const drogon::HttpResponsePtr&)>&& callback, std::string&& name)
{
    auto resp = drogon::HttpResponse::newHttpResponse();
    resp->setBody(say_hello(repo_, std::move(name)));
    callback(resp);
};
} // namespace e1

