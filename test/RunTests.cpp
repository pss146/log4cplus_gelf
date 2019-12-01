#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <log4cplus/initializer.h>
#include <iostream>

class Environment : public ::testing::Environment {
public:
    virtual ~Environment() {}

    // Override this to define how to set up the environment.
    void SetUp() override {
        std::cout << "SetUp" << std::endl;
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {
        std::cout << "TearDown" << std::endl;
    }
};

int main(int argc, char **argv) {
    log4cplus::Initializer initializer;

    ::testing::AddGlobalTestEnvironment(new Environment);

//    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    int result = RUN_ALL_TESTS();

    std::cout << "Exiting main()..." << std::endl;
    return result;
}
