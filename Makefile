BUILD := build
LIBS := GL GLEW glfw stdc++ png
PREFIX := $(HOME)/dev
DIRS := . graphics physic objects

SOURCES := $(foreach DIR,$(DIRS),$(wildcard $(DIR)/*.cpp))
OBJECTS := $(addprefix $(BUILD)/,$(notdir $(SOURCES:.cpp=.o)))

VPATH += $(DIRS)

.PHONY: all
all: $(BUILD) $(BUILD)/voitures

$(BUILD):
	mkdir -p $@
	echo $(OBJECTS)

$(BUILD)/voitures: $(OBJECTS)
	g++ -g -o $@ -L$(PREFIX)/lib $(addprefix -l,$(LIBS)) $(OBJECTS)

$(BUILD)/%.o:%.cpp
	g++ -g -o $@ -I$(PREFIX)/include --std=c++14 -c $<

.PHONY: clean
clean:
	rm -rf $(BUILD)
