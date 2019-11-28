#include <gelfcpp/GelfMessage.hpp>
#include <gelfcpp/output/GelfJSONOutput.hpp>
#include <gelfcpp/GelfMessageStream.hpp>

#include <gelfcpp/decorator/StaticDecoratorSet.hpp>
#include <gelfcpp/decorator/Timestamp.hpp>
#include <gelfcpp/decorator/Host.hpp>

#include <iostream>

void hello() {
// define a nice decorator
    // - add hostname
    // - add current timestamp
    using Decorator = gelfcpp::decorator::StaticDecoratorSet<gelfcpp::decorator::CurrentTimestamp, gelfcpp::decorator::Host>;
    Decorator decorator;

    // explicitly set hostname, defaults to the hostname of the system
    decorator.get<gelfcpp::decorator::Host>().SetHost("explicit-hostname");

    // define an JSON output, printing directly to std::cout
    gelfcpp::output::GelfJSONOutput json(std::cout);

    // sending some messages
    GELF_MESSAGE(json)(decorator)
                              ("Test message to std::cout")
                              ("tagged_value", 1);

    std::cout << std::endl;
}