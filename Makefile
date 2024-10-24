FLAGS :=  -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -lmingw32 #-mwindows #sdl2-config --cflags --libs -lSDL2_ttf
CONSOLE_FLAG := -mwindows
LIBS := -I include -L lib
CC := g++

SRC_DIR := ./src
OUTPUT_DIR := ./output

SOURCE_FILES := $(SRC_DIR)/*.cpp
EXEC := $(OUTPUT_DIR)/game.exe

all: build run

test: build_test run

run: $(EXEC)
	start "$(OUTPUT_DIR)/game.exe"

build_test:
	$(CC) $(LIBS) $(wildcard $(SOURCE_FILES)) -o $(EXEC) $(FLAGS)

build:
	$(CC) $(LIBS) $(wildcard $(SOURCE_FILES)) -o $(EXEC) $(FLAGS) $(CONSOLE_FLAG)

clean:
	rm -f $(EXEC)