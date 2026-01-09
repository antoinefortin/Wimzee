CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -Ivendor/spdlog/include -Ivendor/glm

SRC = $(shell find src -name '*.cpp')
OUT = wimzee

# Détection OS
ifeq ($(OS),Windows_NT)
    LIBS = -lglew32 -lglfw3 -lopengl32 -lgdi32
    OUT := $(OUT).exe
    RM = del
    SRC = $(shell dir /S /B src\*.cpp)
    SETUP = powershell -ExecutionPolicy Bypass -File setup/setup-dependencies-windows.ps1
else ifeq ($(shell uname),Darwin)
    LIBS = -lglfw -lGLEW -framework OpenGL
    RM = rm -f
    SETUP = ./setup/setup-dependencies-linux.sh
else
    LIBS = -lglfw -lGLEW -lGL
    RM = rm -f
    SETUP = ./setup/setup-dependencies-linux.sh
endif

setup:
	$(SETUP)

all: setup
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LIBS)

run: all
	$(OUT)

clean:
	$(RM) $(OUT)

.PHONY: all run clean setup