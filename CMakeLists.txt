cmake_minimum_required(VERSION 3.20)
project(app NONE)

include(ExternalProject)

ExternalProject_Add(
    gprolog
    GIT_REPOSITORY    "git@github.com:didoudiaz/gprolog.git"
    GIT_TAG           "master"
    SOURCE_SUBDIR     "src"
    BUILD_IN_SOURCE   TRUE
    CONFIGURE_COMMAND ./configure --with-install-dir=<INSTALL_DIR> --without-doc-dir --without-html-dir --without-examples-dir --without-links-dir
    BUILD_COMMAND     make
    INSTALL_COMMAND   make install
)

ExternalProject_Get_Property(gprolog INSTALL_DIR)
configure_file(gplc.cmake "${INSTALL_DIR}" COPYONLY)
configure_file(gplc-override.cmake "${INSTALL_DIR}" COPYONLY)

ExternalProject_Add(
    app
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src"
    CMAKE_ARGS
      "-DCMAKE_TOOLCHAIN_FILE=${INSTALL_DIR}/gplc.cmake"
    CONFIGURE_HANDLED_BY_BUILD TRUE
    BUILD_COMMAND ${CMAKE_COMMAND} -E env "PATH=${INSTALL_DIR}/bin:$ENV{PATH}" ${CMAKE_COMMAND} --build <BINARY_DIR> --config $<CONFIG>
    INSTALL_COMMAND ""
)

ExternalProject_Add_StepDependencies(app configure gprolog)
