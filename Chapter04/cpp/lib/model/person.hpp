#pragma once
#include <string>

#include <drogon/HttpRequest.h>

namespace model {
/**
 * Type used to represent a person.
 */
class person {
public:
  /**
   * Deserializes a person from a string containing a corresponding JSON object.
   * @param json The string containing a corresponding JSON object.
   * @return The resulting person object.
   */
  static person from_json(const std::string& json);

  /**
   * This default constructor is required by drogon.
   */
  person();

  /**
   * Creates a new person object.
   * @param name The name to use.
   * @param title The title to use.
   * @param description The description to use.
   */
  person(std::string name, std::string title, std::string description);

  /**
   * Read accessor for the name.
   * @return The name.
   */
  const std::string& name() const noexcept;

  /**
   * Write accessor for the name.
   * @param s The new name to use.
   * @note Required by drogon.
   */
  void name(std::string&& s);

  /**
   * Read accessor for the title.
   * @return The title.
   */
  const std::string& title() const noexcept;

  /**
   * Write accessor for the title.
   * @param s THe new title to use.
   * @note Required by drogon.
   */
  void title(std::string&& s);

  /**
   * Read accessor for the description.
   * @return The description.
   */
  const std::string& description() const noexcept;

  /**
   * Write accessor for the description.
   * @param s The new description to use.
   * @note Required by drogon.
   */
  void description(std::string&& s);

  /**
   * Serializes this object to a string containing a JSON object.
   * @return The resulting string.
   */
  std::string to_json() const;

private:
  std::string name_;
  std::string title_;
  std::string description_;
};
} // namespace model

// This is required so that drogon can deserialize JSON objects
// transferred as strings in HTTP bodies to person objects.
namespace drogon {
template <>
inline ::model::person fromRequest(const HttpRequest& req) {
  auto json_shared_ptr = req.getJsonObject();
  auto& json = *json_shared_ptr;

  ::model::person p;
  p.name(json["name"].asString());
  p.title(json["title"].asString());
  p.description(json["description"].asString());

  return p;
}
} // namespace drogon
