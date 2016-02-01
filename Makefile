BUILD := build
LIBS := GL GLEW glfw stdc++
PREFIX := $(HOME)/dev

SOURCES := $(wildcard *.cpp)
OBJECTS := $(addprefix $(BUILD)/,$(SOURCES:.cpp=.o))

.PHONY: all
all: $(BUILD) $(BUILD)/voitures

$(BUILD):
	mkdir -p $@

$(BUILD)/voitures: $(OBJECTS)
	g++ -o $@ -L$(PREFIX)/lib $(addprefix -l,$(LIBS)) $(OBJECTS)

$(BUILD)/%.o:%.cpp
	g++ -o $@ -I$(PREFIX)/include --std=c++14 -c $<

.PHONY: clean
clean:
	rm -rf $(BUILD)
