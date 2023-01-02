AS = arm-linux-gnueabi-as
LD = arm-linux-gnueabi-ld
TARGET = a

all: $(TARGET).out

$(TARGET).out: $(TARGET).s
	$(AS) $(TARGET).s -o $(TARGET).o
	$(LD) -static -nostdlib $(TARGET).o -o $(TARGET).out
	./$(TARGET).out
