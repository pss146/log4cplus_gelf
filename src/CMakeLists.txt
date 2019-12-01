set(PRIVATE_HEADERS
        include/AbstractTransport.h
        include/UdpTransport.h
        include/TransportFactory.h
        )

set(SOURCES
        GelfAppender.cpp
        UdpTransport.cpp
        )

foreach(SRC ${PRIVATE_HEADERS})
    list(APPEND SOURCES ${SRC})
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

