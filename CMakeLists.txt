cmake_minimum_required(VERSION 3.26)
project("myperf")

set(C_STANDARD 23)

set(TCP_SOURCES       src/tcp/tcp.c             src/tcp/client.c src/tcp/server.c)
set(RAW_SOURCES       src/raw/raw.c)
set(ZERO_COPY_SOURCES src/zero_copy/zero_copy.c)
set(MODE_SOURCES ${TCP_SOURCES} ${RAW_SOURCES} ${ZERO_COPY_SOURCES})

add_compile_definitions(E4C_THREADSAFE)
set(EXCEPTIONS4C_SOURCES vendor/exceptions4c/src/e4c.c)
set(EXCEPTIONS4C_INCLUDE_DIRECTORIES vendor/exceptions4c/src)

set(VENDOR_SOURCES ${EXCEPTIONS4C_SOURCES})
set(VENDOR_INCLUDE_DIRECTORIES ${EXCEPTIONS4C_INCLUDE_DIRECTORIES})

set(SOURCES
    src/main.c src/program.c src/cli.c src/util.c
    ${MODE_SOURCES}
    ${VENDOR_SOURCES}
)

add_executable(myperf ${SOURCES})
target_include_directories(myperf PUBLIC ${VENDOR_INCLUDE_DIRECTORIES})