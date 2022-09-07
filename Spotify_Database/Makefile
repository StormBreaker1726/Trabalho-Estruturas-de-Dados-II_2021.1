##Seguindo o template do professor José Camata
srcfiles := $(wildcard *.cpp) $(wildcard source/*.cpp)

objects := $(patsubst %.cpp, %.o, $(srcfiles))

CC = g++

CC_FLAGS = -g -I./include

RM = rm -rf

target := ./prog.exe

all: $(target)

$(notdir $(target)) : $(objects)
	@echo "Linking "$@"..."
	@$(CC) $(objects) -o $@

%.o: %.cpp
	@echo "Compiling C++ "$<"..."
	@$(CC) $(CC_FLAGS) -c $< -o $@

clean: 
	rm -rf $(objects) $(target) *~

.PHONY: all clean