file(GLOB SOURCES SDL2/*.cpp file/*.cpp)

add_library(lib_SDL2 ${SOURCES})

target_include_directories(lib_SDL2 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/file
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/SDL2
)

target_link_libraries(lib_SDL2
    "-l SDL2main"
    "-l SDL2"
    "-l SDL2_image"
    "-l SDL2_ttf"
    "-l SDL2_mixer"
)
