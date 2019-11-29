set(HEADERS
        )

set(SOURCES
        library.cpp
        GelfAppender.cpp
        )

foreach(SRC ${HEADERS})
    list(APPEND SOURCES "${HEADERS_DIR}/${SRC}")
endforeach()


# Create library ###############################################################
if (NOT BUILD_SHARED_LIBS)
    add_library(${PROJECT_NAME} STATIC
            ${SOURCES}
            )
else()
    add_library(${PROJECT_NAME} SHARED
            ${SOURCES}
            )
endif()

target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        PRIVATE
        ${CONAN_INCLUDE_DIRS}
        )

target_link_libraries(${PROJECT_NAME}
        ${CONAN_LIBS}
        )

