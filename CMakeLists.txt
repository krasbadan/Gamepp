cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_COMPILER "g++")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

file(READ "SFML_include_dir.txt" SFML_include_dir)
file(STRINGS "SFML_link_files.txt" SFML_link_files)

project(Gamepp)

add_executable(main)

target_sources(main
  PRIVATE
    "src/main.cpp"
    
    "src/Character.cpp"
    "src/MapObject.cpp"
    "src/NPC.cpp"
    "src/Player.cpp"
    "src/Tile.cpp"
    "src/TextureManager.cpp"
    "src/Utils.cpp"
    "src/World.cpp"
)

target_include_directories(main
  PRIVATE
    ${SFML_include_dir}
)

target_link_libraries(main
  PRIVATE
    ${SFML_link_files}
)