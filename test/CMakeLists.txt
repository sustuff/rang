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

add_executable(terminal_test
        terminal_test.cpp
)

add_executable(keystroke_test
        keystroke_test.cpp
)

include(CTest)
include(Catch)

foreach(targetname tests terminal_test keystroke_test)
    target_link_libraries(${targetname} PRIVATE Catch2::Catch2WithMain rang-lib)
    target_compile_features(${targetname} PRIVATE cxx_std_20)
    catch_discover_tests(${targetname} REPORTER JUnit DISCOVERY_MODE POST_BUILD OUTPUT_DIR report OUTPUT_SUFFIX .xml)
endforeach()
