set(target_name libspace)

# Создание библиотеки из исходных файлов
#add_library(my_library
#    hello.cpp
#)

add_library(${target_name} STATIC
        spacemodule.cc
        ${PROJECT_SOURCE_DIR}/include/libspace/libspace.hpp
        spacestation.cc
        ${PROJECT_SOURCE_DIR}/include/libspace/libspace.hpp)

include(CompileOptions)
set_compile_options(${target_name})

# Связывание библиотеки с исполняемым файлом
# target_include_directories(my_library PUBLIC /include)

target_include_directories(
        ${target_name}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include/
        ${PROJECT_SOURCE_DIR}/external
)

# пока не нужны библиотеки для библиотеки.
# target_link_libraries(
#         ${target_name}
#         PRIVATE
#         nlohmann_json
#         m
# )
