#!/bin/bash
#g++ "main.cpp" "MapObject.cpp" "Player.cpp" "Tile.cpp" "World.cpp" -o "main"

g++ "src/main.cpp" -c -o "build/main.o"
g++ "src/TextureManager.cpp" -c -o "build/TextureManager.o"
g++ "src/Utils.cpp" -c -o "build/Utils.o"
g++ "src/MapObject.cpp" -c -o "build/MapObject.o"
g++ "src/Character.cpp" -c -o "build/Character.o"
g++ "src/Player.cpp" -c -o "build/Player.o"
g++ "src/Tile.cpp" -c -o "build/Tile.o"
g++ "src/World.cpp" -c -o "build/World.o"

g++ "build/main.o" "build/TextureManager.o" "build/Utils.o" "build/MapObject.o" "build/Character.o" "build/Player.o" "build/Tile.o" "build/World.o" -o "main" -lsfml-graphics -lsfml-window -lsfml-system 