CC = gcc
CFLAGS = -Wall -Werror
LDFLAGS = -lm

SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_DIR = obj
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

TARGET = mikros

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< $(LDFLAGS)

clean:
	rm -f $(TARGET) $(OBJ_FILES)
