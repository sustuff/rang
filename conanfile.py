import os

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout


class BasicConanfile(ConanFile):
    name = "rang"
    description = "Qt-based terminal file manager"
    homepage = "https://gitlab.akhcheck.ru/pir/rang"

    exports_sources = "CMakeLists.txt", "cmake/*", "src/*", "include/*"

    settings = "os", "compiler", "build_type", "arch"
    default_options = {
            "qt/*:gui": False,
            "qt/*:widgets": False
    }

    def layout(self):
        cmake_layout(self)

    # The purpose of generate() is to prepare the build, generating the necessary files, such as
    # Files containing information to locate the dependencies, environment activation scripts,
    # and specific build system files among others
    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    # This method is used to build the source code of the recipe using the desired commands.
    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    # The actual creation of the package, once it's built, is done in the package() method.
    # Using the copy() method from tools.files, artifacts are copied
    # from the build folder to the package folder
    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.bindirs = ["bin"]
        self.runenv_info.append("PATH", os.path.join(self.package_folder, "bin/"))
