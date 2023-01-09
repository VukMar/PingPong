# Specify the compiler and flags
CXX = g++
VUI_PATH = "D:\VS Code Vuk\C++\SFMLUI"

LIBS = -L$(VUI_PATH) -lV-UI -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lcomdlg32

CPPFLAGS = -Wall -O2 -Iinclude -MMD -lm

TARGET = Pong.exe
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(patsubst src/%.cpp,obj/%.o,$(SOURCES))
DEPS = $(patsubst src/%.cpp,obj/%.d,$(SOURCES))

# Default target
all: $(TARGET)

# Rule to build the target
$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(CPPFLAGS) $(LIBS)

# Rule to build the object files
obj/%.o: src/%.cpp
	$(CXX) $(CPPFLAGS) -c -o $@ $< $(LIBS)

# Rule to include dependencies
-include $(DEPS)

# Rule to clean up the project
clean:
	del *.exe obj\*.o obj\*.d

# Rule to rebuild the project from scratch
rebuild: clean all

# Phony targets
.PHONY: all clean rebuild