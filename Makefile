TARGET 		:= dragonslave

SRC_DIR		:= src
INC_DIR		:= inc
BUILD_DIR	:= .build
DOC_DIR		:= doc

CC			:= clang++
CFLAGS		:= -std=c++14 -O0 -g
INCS		:= -I$(INC_DIR)
LIBS		:= -pthreads -lGL -lGLEW -lglfw -lassimp -lfreeimage
SOURCES		:= $(shell find $(SRC_DIR) -name '*.cpp' -type 'f' | sort)
HEADERS		:= $(shell find $(INC_DIR) -name '*.hpp' -type 'f' | sort)
OBJECTS		:= $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

new: clean $(TARGET)

doc:
	@doxygen $(DOC_DIR)/Doxyfile

.PHONY:
	clean
	new
	doc
