OS_NAME = R
OS_ARCH = x86
OS_BIN = $(OS_NAME).bin
OS_ISO = $(OS_NAME).iso

CC := i686-elf-gcc
AS := i686-elf-as

GRUB_CFG_DIR := conf
BOCHS_CFG_DIR := conf
BUILD_DIR := build
ISO_DIR := $(BUILD_DIR)/iso
ISO_BOOT_DIR := $(ISO_DIR)/boot
ISO_GRUB_DIR := $(ISO_DIR)/boot/grub

INCLUDE_DIR := src/include
INCLUDE := $(patsubst %,-I%,${INCLUDE_DIR})

O := -O2
CFLAGS := -std=gnu99 -ffreestanding $(O) -Wall -Wextra
LDFLAGS := -ffreestanding $(O) -nostdlib -lgcc

SOURCE_FILES := $(shell find src -name "*.[csS]")
OBJS := $(patsubst %, %.o, $(SOURCE_FILES))


$(ISO_DIR):
	@mkdir -p $(ISO_DIR)
	@mkdir -p $(ISO_BOOT_DIR)
	@mkdir -p $(ISO_GRUB_DIR)

%.S.o: %.S
	$(CC) $(INCLUDE) -c $< -o $@ $(CFLAGS)

%.s.o: %.s
	$(CC) $(INCLUDE) -c $< -o $@ $(CFLAGS)

%.c.o: %.c
	$(CC) $(INCLUDE) -c $< -o $@ $(CFLAGS)

$(OS_BIN): $(OBJS)
	$(CC) -T linker.ld -o $(BUILD_DIR)/$@ $(OBJS) $(LDFLAGS)

$(BUILD_DIR)/$(OS_ISO): $(ISO_DIR) $(OS_BIN)
	@cp $(BUILD_DIR)/$(OS_BIN) $(ISO_BOOT_DIR)
	@cp $(GRUB_CFG_DIR)/grub.cfg $(ISO_GRUB_DIR)/
	@grub-mkrescue -o $(BUILD_DIR)/$(OS_ISO) $(ISO_DIR)

all: $(BUILD_DIR)/$(OS_ISO)
	@rm -rf $(OBJS)

all-debug: $(BUILD_DIR)/$(OS_ISO)
	objdump -d $(BUILD_DIR)/$(OS_BIN) > $(BUILD_DIR)/$(OS_NAME)dump.txt
	@rm -rf $(OBJS)

clean:
	rm -rf $(BUILD_DIR)

qemu:
	qemu-system-i386 -cdrom $(BUILD_DIR)/$(OS_NAME).iso

bochs:
	bochs -f $(BOCHS_CFG_DIR)/.bochsrc