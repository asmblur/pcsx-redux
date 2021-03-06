PREFIX = mipsel-linux-gnu

CC = $(PREFIX)-gcc

ARCHFLAGS = -march=mips1 -mabi=32 -EL -msoft-float -Wa,-msoft-float -fno-pic -mno-shared -mno-abicalls
CPPFLAGS = -mno-gpopt -fomit-frame-pointer
CPPFLAGS += -fno-builtin
CPPFLAGS += $(ARCHFLAGS)
CPPFLAGS += -I..

LDFLAGS = -Wl,-Map=$(TARGET).map -nostdlib -T$(LDSCRIPT) -static -Wl,--gc-sections
LDFLAGS += $(ARCHFLAGS)

LDFLAGS += -g -O3 -flto
CPPFLAGS += -g -O3 -flto

OBJS += $(addsuffix .o, $(basename $(SRCS)))

all: $(TARGET).bin

clean:
	rm -f $(OBJS) $(TARGET).elf $(TARGET).map $(TARGET).bin

$(TARGET).bin: $(TARGET).elf
	$(PREFIX)-objcopy -O binary $< $@

$(TARGET).elf: $(OBJS)
	$(CC) $(LDFLAGS) -g -o $(TARGET).elf $(OBJS)

%.o: %.s
	$(CC) $(ARCHFLAGS) -I.. -g -c -o $@ $<
