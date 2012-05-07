SRC = unitconv.c length.c area.c mass.c force.c pressure.c energy.c power.c temp.c calc.c
OBJ = $(SRC:%.c=%.o)
TARGET = unitconv

.PHONY: clean

$(TARGET): $(OBJ)
	gcc -o $@ $^

.c.o:
	gcc -c -O2 $<

unitconv.o: unitconv.h unitdata.h
calc.o: calc.h unitconv.h
length.o: calc.h unitconv.h unitdata.h
area.o: calc.h unitconv.h unitdata.h
mass.o: calc.h unitconv.h unitdata.h
force.o: calc.h unitconv.h unitdata.h
pressure.o: calc.h unitconv.h unitdata.h
energy.o: calc.h unitconv.h unitdata.h
power.o: calc.h unitconv.h unitdata.h
temp.o: calc.h unitconv.h unitdata.h

clean:
	-rm $(OBJ) $(TARGET)
