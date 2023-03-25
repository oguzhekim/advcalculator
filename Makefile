advcalc: main.o lexer.o shunting.o validator.o variables.o stack.o calculator.o
	gcc ./build/main.o ./build/lexer.o ./build/shunting.o ./build/validator.o ./build/variables.o ./build/stack.o ./build/calculator.o -o advcalc

main.o: ./src/main.c
	gcc -I "./include" -c ./src/main.c -o ./build/main.o

lexer.o: ./src/lexer.c
	gcc -I "./include" -c ./src/lexer.c -o ./build/lexer.o

shunting.o: ./src/shunting.c
	gcc -I "./include" -c ./src/shunting.c -o ./build/shunting.o

validator.o: ./src/validator.c
	gcc -I "./include" -c ./src/validator.c -o ./build/validator.o

variables.o: ./src/variables.c
	gcc -I "./include" -c ./src/variables.c -o ./build/variables.o

stack.o: ./src/stack.c
	gcc -I "./include" -c ./src/stack.c -o ./build/stack.o

calculator.o: ./src/calculator.c
	gcc -I "./include" -c ./src/calculator.c -o ./build/calculator.o

clean:
	rm  ./build/*.o advcalc

