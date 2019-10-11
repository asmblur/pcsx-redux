PREFIX = mipsel-linux-gnu

CC = $(PREFIX)-gcc
AR = $(PREFIX)-ar

## If "TLOAD_ADDR" was specified in the Makefile, pass it to the linker.
ifneq ($(strip $(TLOAD_ADDR)),)
LDFLAGS += -Wl,--defsym,TLOAD_ADDR=$(TLOAD_ADDR)
endif

TARGETBASE = $(basename $(TARGET))

ARCHFLAGS = -march=mips1 -mabi=32 -EL -fno-pic -mno-shared -mno-abicalls -mfp32
ARCHFLAGS += -fno-stack-protector -nostdlib -ffreestanding
CPPFLAGS += -mno-gpopt -fomit-frame-pointer -ffunction-sections
CPPFLAGS += -fno-builtin
CPPFLAGS += $(ARCHFLAGS)
CPPFLAGS += -I..

LDFLAGS += -Wl,-Map=$(TARGETBASE).map -nostdlib -T$(LDSCRIPT) -static -Wl,--gc-sections
LDFLAGS += $(ARCHFLAGS) -L../ps1sdk

LDFLAGS += -g -Os
CPPFLAGS += -g -Os

OBJS += $(addsuffix .o, $(basename $(SRCS)))

all: $(TARGET)

../ps1sdk/libps1sdk.a:
	$(MAKE) -C ../ps1sdk all

clean:
	rm -f $(OBJS) $(TARGETBASE).psx $(TARGETBASE).elf $(TARGETBASE).map $(TARGETBASE).bin $(TARGET)

$(TARGETBASE).bin: $(TARGETBASE).elf
	$(PREFIX)-objcopy -O binary $< $@

$(TARGETBASE).psx: $(TARGETBASE).elf
	$(PREFIX)-objcopy -O binary $< $@

$(TARGETBASE).a: $(OBJS)
	$(AR) cru $@ $(OBJS)

$(TARGETBASE).elf: $(OBJS) $(LIBS)
	$(CC) $(LDFLAGS) -g -o $(TARGETBASE).elf $(OBJS) $(LIBS)

%.o: %.S
	$(CC) $(CPPFLAGS) -I.. -g -c -o $@ $<

%.o: %.s
	$(CC) $(ARCHFLAGS) -I.. -g -c -o $@ $<

