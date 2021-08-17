cmake_minimum_required(VERSION 3.20)
project(app C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_COMPILER "${CMAKE_SOURCE_DIR}/3rdparty/gprolog-build/bin/gplc")

include(ExternalProject)
ExternalProject_Add(app
        GIT_REPOSITORY    "git@github.com:didoudiaz/gprolog.git"
        GIT_TAG           "master"
        SOURCE_DIR        "${CMAKE_SOURCE_DIR}/3rdparty/gprolog"
        BUILD_IN_SOURCE   true
        CONFIGURE_COMMAND cd src && ./configure --with-install-dir=${CMAKE_SOURCE_DIR}/3rdparty/gprolog-build --without-doc-dir --without-html-dir --without-examples-dir
        BUILD_COMMAND     cd src && make
        INSTALL_COMMAND   cd src && make install
)

# add_executable(app src/application.pro src/main.c)
include_directories(app "${CMAKE_SOURCE_DIR}/3rdparty/gprolog-build/include")
