SOURCE=$(wildcard ./src/*.c)
OBJECTS=$(patsubst ./src/%.c,./build/%.o,$(SOURCE))
DEPFILES=$(patsubst ./build/%.o,./build/%.d,$(OBJECTS))
INCDIR=-I "./include"
FLAGS=-g $(INCDIR) -MP -MD

advcalc: $(OBJECTS)
	gcc $(OBJECTS) -o advcalc

./build/%.o: ./src/%.c
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(DEPFILES) advcalc

-include $(DEPFILES)

.PHONY: clean
