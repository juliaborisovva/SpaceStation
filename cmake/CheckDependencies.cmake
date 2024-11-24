find_program(CLANG_TIDY_EXE NAMES clang-tidy-14 clang-tidy)
if (NOT CLANG_TIDY_EXE)
    message(WARNING "clang-tidy not found")
else()
    execute_process(
            COMMAND ${CLANG_TIDY_EXE} --version
            OUTPUT_VARIABLE CLANG_TIDY_VERSION)
    message("clang-tidy found:\n" ${CLANG_TIDY_VERSION})
endif()

find_program(NINJA_EXE ninja)
if (NOT NINJA_EXE)
    message(FATAL_ERROR "Ninja not found. 
    Install ninja using commands 'sudo apt update', 'sudo apt install ninja-build' for Debian/Ubuntu 
    or 'brew install ninja' for macOS or the appropriate command for your system.")
else()
    execute_process(
            COMMAND ${NINJA_EXE} --version
            OUTPUT_VARIABLE NINJA_VERSION)
    message("ninja found:\n" ${NINJA_VERSION})
endif()