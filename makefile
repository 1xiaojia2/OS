OS_NAME = R
OS_ARCH = x86
OS_BIN = $(OS_NAME).bin
OS_ISO = $(OS_NAME).iso
VIRTUAL_BOX_ISO_DIR = /mnt/d/graduation/os/iso

CC := i686-elf-gcc
AS := i686-elf-as
GDB := i686-elf-gdb

CONF_DIR := conf
GDB_CONF := $(CONF_DIR)/.gdbinit
BOCHS_CONF := $(CONF_DIR)/.bochsrc
BOCHS_DBG := $(CONF_DIR)/bochsrc.gdb

BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
BIN_DIR := $(BUILD_DIR)/bin
ISO_DIR := $(BUILD_DIR)/iso
ISO_BOOT_DIR := $(ISO_DIR)/boot
ISO_GRUB_DIR := $(ISO_DIR)/boot/grub

INCLUDE_DIR := src/include
INCLUDE := $(patsubst %,-I%,${INCLUDE_DIR})

O := -O0
DBG_FLAG := -g


CFLAGS := -ffreestanding $(O) -Wall -Wextra $(DBG_FLAG)
LDFLAGS := -ffreestanding $(O) -nostdlib -lgcc

SOURCE_FILES := $(shell find ./src -name "*.[csS]")
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
	$(CC) $(INCLUDE) -c $< -o $@ $(CFLAGS)

$(OBJ_DIR)/%.s.o: %.s
	@mkdir -p $(@D)
	$(CC) $(INCLUDE) -c $< -o $@ $(CFLAGS)

$(OBJ_DIR)/%.c.o: %.c
	@mkdir -p $(@D)
	$(CC) $(INCLUDE) -c $< -o $@ $(CFLAGS)

$(BIN_DIR)/$(OS_BIN): $(OBJ_DIR) $(BIN_DIR) $(SRC) linker.ld
	$(CC) -T linker.ld -o $(BIN_DIR)/$(OS_BIN) $(SRC) $(LDFLAGS)

$(BUILD_DIR)/$(OS_ISO): $(ISO_DIR) $(BIN_DIR)/$(OS_BIN)
	@cp $(BIN_DIR)/$(OS_BIN) $(ISO_BOOT_DIR)
	@cp conf/grub.cfg $(ISO_GRUB_DIR)/
	@grub-mkrescue -o $(BUILD_DIR)/$(OS_ISO) $(ISO_DIR)

.PHONY: all objdump clean qemu qemu-dbg bochs vscode-dbg

all: $(BUILD_DIR)/$(OS_ISO)

objdump: $(BUILD_DIR)/$(OS_ISO)
	objdump -d $(BIN_DIR)/$(OS_BIN) > $(BUILD_DIR)/$(OS_NAME)dump.txt

clean:
	rm -rf $(BUILD_DIR)

qemu: all
	qemu-system-i386 -cdrom $(BUILD_DIR)/$(OS_ISO) 

qemu-dbg: all
	@echo "Starting QEMU with debugging enabled..."
	@qemu-system-i386 -s -S -cdrom $(BUILD_DIR)/$(OS_ISO) &
	@sleep 1 
	@echo "Launching GDB for debugging..."
	@$(GDB) -x $(GDB_CONF) $(BIN_DIR)/$(OS_BIN)

bochs: all
	bochs -f $(BOCHS_CONF)

vscode-dbg: all
	@qemu-system-i386 -s -S -cdrom $(BUILD_DIR)/$(OS_ISO)

virtual-box: all
	@cp $(BUILD_DIR)/$(OS_ISO) $(VIRTUAL_BOX_ISO_DIR)

bochs-dbg: all
	bochs -f $(BOCHS_DBG)