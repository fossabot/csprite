CXX := clang++
CC := clang
STD := c++17
LFLAGS := -lglfw -lm -ldl -I. -std=${STD} -Wall
CFLAGS := -Wall

#IMGUI v1.87

SRC=src
LIB=lib
OBJ=obj

SRCS=$(SRC)/main.cpp $(LIB)/glad.c $(LIB)/ImGuiFileDialog.cpp
SRCS += $(SRC)/imgui/imgui.cpp $(SRC)/imgui/imgui_impl_opengl3.cpp
SRCS += $(SRC)/imgui/imgui_impl_glfw.cpp $(SRC)/imgui/imgui_draw.cpp
SRCS += $(SRC)/imgui/imgui_tables.cpp $(SRC)/imgui/imgui_widgets.cpp

OBJS=$(OBJ)/main.o $(OBJ)/glad.o $(OBJ)/imgui.o $(OBJ)/ImGuiFileDialog.o
OBJS += $(OBJ)/imgui_impl_opengl3.o $(OBJ)/imgui_impl_glfw.o
OBJS += $(OBJ)/imgui_draw.o $(OBJ)/imgui_tables.o $(OBJ)/imgui_widgets.o
BIN=csprite

all: LFLAGS += -g -O0
all: $(BIN)

release: LFLAGS += -O2 -DNDEBUG
release: $(BIN)

.PHONY: clean
clean:
	rm obj/*.o $(BIN)

# For Compiling OBJ/* To Binary
$(BIN): $(OBJS)
	$(CXX) $(LFLAGS) $(OBJS) -o $@

# For Compiling Src/*.cpp
$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

# For Compiling Src/imgui/*.cpp
$(OBJ)/%.o: $(SRC)/imgui/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

# For Compiling Lib/*.c
$(OBJ)/%.o: $(LIB)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# For Compiling Lib/*.cpp
$(OBJ)/%.o: $(LIB)/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@
