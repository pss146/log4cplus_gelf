function(create_all)
    message("Test: Adding 'all-in-one' test")

    file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

    add_executable(log4cplus_gelf_test_all ${sources})
    target_link_libraries(log4cplus_gelf_test_all PUBLIC log4cplus_gelf ${CONAN_LIBS_GTEST} ${CONAN_LIBS})

    add_test(NAME Log4cplusGelfTestAll
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
            COMMAND log4cplus_gelf_test_all)
endfunction()

create_all()
