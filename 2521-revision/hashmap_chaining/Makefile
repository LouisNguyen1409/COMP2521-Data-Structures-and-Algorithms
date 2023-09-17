CC=clang
CFLAGS  =  -Wall -Werror -g -fsanitize=address,leak,undefined
EXECUTABLE_NAME = main
SOURCE_FILES=main.c hashmap_chaining.c
EXECUTABLE_FILES=$(EXECUTABLE_NAME:%=./%) 

build: $(EXECUTABLE_FILES)

$(EXECUTABLE_FILES) : $(SOURCE_FILES)
	@$(CC) $(CFLAGS) -o $@ $^
	@echo "Build successfully finished."


# $(OBJECT_FILES) : $(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# $(BUILD_DIR)/main.o : $(INC_DIR)/token.h $(INC_DIR)/AST.h $(INC_DIR)/lexer.h $(INC_DIR)/interpreter.h
# $(BUILD_DIR)/parser.o : $(INC_DIR)/token.h $(INC_DIR)/AST.h $(INC_DIR)/lexer.h 
# $(BUILD_DIR)/interpreter.o : $(INC_DIR)/token.h $(INC_DIR)/AST.h $(INC_DIR)/lexer.h
# $(BUILD_DIR)/lexer.o : $(INC_DIR)/token.h $(INC_DIR)/AST.h
# $(BUILD_DIR)/token.o : $(INC_DIR)/token.h

.PHONY : build clean
clean:
	rm $(EXECUTABLE_FILES) $(OBJECT_FILES)
