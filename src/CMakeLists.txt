add_executable(test main.cpp)

target_compile_features(test PUBLIC cxx_std_20)
target_link_libraries(test PRIVATE Qt6::Core)
