
set(TEST_SRCS
        TestGelfAppender.cpp
        TestGelfAppenderRegistration.cpp
        )

#Run through each source
foreach (testSrc ${TEST_SRCS})
    #Extract the filename without an extension (NAME_WE)
    get_filename_component(testName ${testSrc} NAME_WE)

    #Add compile target
    add_executable(${testName} ${testSrc})

    #link to Boost libraries AND your targets and dependencies
    #target_link_libraries(${testName} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_SSL_LIBRARY} common-lib)
    target_link_libraries(${testName}
            PUBLIC log4cplus_gelf
            PRIVATE ${CONAN_LIBS_GTEST} ${CONAN_LIBS_BOOST}
    )

    #Finally add it to test execution -
    #Notice the WORKING_DIRECTORY and COMMAND
    add_test(NAME ${testName}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
            COMMAND ${testName})

endforeach (testSrc)
