if (BUILD_CATCH2)
    Include(FetchContent)

    FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG v3.4.0
    )

    FetchContent_MakeAvailable(Catch2)
    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
else ()
    find_package(Catch2 3 REQUIRED)
endif ()

add_executable(tests
        buffer_test.cpp
)

add_executable(ncurses_tests
        ncurses_test.cpp
)

include(CTest)
include(Catch)

foreach(targetname tests ncurses_tests)
    target_link_libraries(${targetname} PRIVATE Catch2::Catch2WithMain rang-lib)
    catch_discover_tests(${targetname} REPORTER JUnit DISCOVERY_MODE POST_BUILD OUTPUT_DIR report OUTPUT_SUFFIX .xml)
endforeach()
