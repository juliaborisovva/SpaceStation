set(target_name server)

add_executable(${target_name})

include(CompileOptions)
set_compile_options(${target_name})

target_sources(
        ${target_name}
        PRIVATE
        server.cc
)

target_link_libraries(
        ${target_name}
        PRIVATE
        #fts
        libspace
)

set(target_name_2 client)

add_executable(${target_name_2})

include(CompileOptions)
set_compile_options(${target_name_2})

target_sources(
        ${target_name_2}
        PRIVATE
        client.cc
)

# target_link_libraries(
#         ${target_name_2}
#         PRIVATE
#         #fts
#         libspace
# )
