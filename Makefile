SRC = unitconv.c length.c calc.c
OBJ = $(SRC:%.c=%.o)
TARGET = unitconv

.PHONY: clean

$(TARGET): $(OBJ)
	gcc -o $@ $^

.c.o:
	gcc -c $<

unitconv.o: unitconv.h unitdata.h
calc.o: calc.h unitconv.h
length.o: calc.h unitconv.h unitdata.h

clean:
	-rm $(OBJ) $(TARGET)
