OS_NAME = LeeOS
OS_ARCH = x86
OS_BIN = $(OS_NAME).bin
OS_ISO = $(OS_NAME).iso

CC := i686-elf-gcc
AS := i686-elf-as

BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
BIN_DIR := $(BUILD_DIR)/bin
ISO_DIR := $(BUILD_DIR)/iso
ISO_BOOT_DIR := $(ISO_DIR)/boot
ISO_GRUB_DIR := $(ISO_DIR)/boot/grub

INCLUDE_DIR := include
INCLUDE := $(patsubst %,-I%,${INCLUDE_DIR})

O := -O2

CFLAGS := -std=gnu99 -ffreestanding $(O) -Wall -Wextra
LDFLAGS := -ffreestanding $(O) -nostdlib -lgcc

SOURCE_FILES := $(shell find . -name "*.[cS]")
SRC := $(patsubst ./%, $(OBJ_DIR)/%.o, $(SOURCE_FILES))

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(ISO_DIR):
	@mkdir -p $(ISO_DIR)
	@mkdir -p $(ISO_BOOT_DIR)
	@mkdir -p $(ISO_GRUB_DIR)

$(OBJ_DIR)/%.S.o: %.S
	@mkdir -p $(@D)
	$(CC) $(INCLUDE) -MD -c $< -o $@ $(CFLAGS)

$(OBJ_DIR)/%.c.o: %.c
	@mkdir -p $(@D)
	$(CC) $(INCLUDE) -MD -c $< -o $@ $(CFLAGS)

$(BIN_DIR)/$(OS_BIN): $(OBJ_DIR) $(BIN_DIR) $(SRC)
	$(CC) -T linker.ld -o $(BIN_DIR)/$(OS_BIN) $(SRC) $(LDFLAGS)

$(BUILD_DIR)/$(OS_ISO): $(ISO_DIR) $(BIN_DIR)/$(OS_BIN)
	@cp $(BIN_DIR)/$(OS_BIN) $(ISO_BOOT_DIR)
	@cp grub.cfg $(ISO_GRUB_DIR)/
	@grub-mkrescue -o $(BUILD_DIR)/$(OS_ISO) $(ISO_DIR)

all: clean $(BUILD_DIR)/$(OS_ISO) qemu

clean:
	rm -rf $(BUILD_DIR)

qemu:
	qemu-system-i386 -cdrom $(BUILD_DIR)/$(OS_NAME).iso

bochs:
	