file(GLOB SOURCES SDL2/*.cpp file/*.cpp)

add_library(lib_SDL2 ${SOURCES})

target_include_directories(lib_SDL2 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/file
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/SDL2
)

target_link_directories(lib_SDL2 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

target_link_libraries(lib_SDL2
    SDL2main
    SDL2
    SDL2_image
    SDL2_ttf
    SDL2_mixer
)
