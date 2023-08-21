cmake_minimum_required(VERSION 3.26)
project("myperf")

set(C_STANDARD 23)

set(TCP_SOURCES       src/tcp/tcp.cpp             src/tcp/client.cpp src/tcp/server.cpp)
set(RAW_SOURCES       src/raw/raw.cpp)
set(ZERO_COPY_SOURCES src/zero_copy/zero_copy.cpp)
set(MODE_SOURCES ${TCP_SOURCES} ${RAW_SOURCES} ${ZERO_COPY_SOURCES})

set(SOURCES
    src/main.cpp src/program.cpp src/cli.cpp src/util.cpp
    ${MODE_SOURCES}
)

add_executable(myperf ${SOURCES})
target_include_directories(myperf PUBLIC ${VENDOR_INCLUDE_DIRECTORIES})