cmake_minimum_required(VERSION 3.6)

project(test LANGUAGES CXX)

find_package(Arrow CONFIG REQUIRED)
find_package(lz4 CONFIG REQUIRED)
find_package(unofficial-brotli CONFIG REQUIRED)

add_executable(rw rw.cc)
target_link_libraries(rw PRIVATE ${ARROW_LIBRARIES} unofficial::brotli::brotlidec-static unofficial::brotli::brotlienc-static unofficial::brotli::brotlicommon-static lz4::lz4)
