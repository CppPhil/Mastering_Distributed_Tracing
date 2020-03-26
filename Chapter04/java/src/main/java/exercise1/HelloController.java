package exercise1;

import lib.people.Person;
import lib.people.PersonRepository;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;

import java.util.Optional;

@RestController
public class HelloController {

    private final PersonRepository personRepository;

    public HelloController(final PersonRepository personRepository) {
        this.personRepository = personRepository;
    }

    @GetMapping("/sayHello/{name}")
    public String sayHello(@PathVariable final String name) {
        final Person person = getPerson(name);
        final String response = formatGreeting(person);
        return response;
    }

    private Person getPerson(final String name) {
        final Optional<Person> personOpt = personRepository.findById(name);
        if (personOpt.isPresent()) {
            return personOpt.get();
        }
        return new Person(name);
    }

    private String formatGreeting(final Person person) {
        String response = "Hello, ";
        if (!person.getTitle().isEmpty()) {
            response += person.getTitle() + " ";
        }
        response += person.getName() + "!";
        if (!person.getDescription().isEmpty()) {
            response += " " + person.getDescription();
        }
        return response;
    }
}
