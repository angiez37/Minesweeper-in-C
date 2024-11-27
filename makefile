logic_test: logic_test.c input.c board.c logic.c score.c minesweeper.h
	gcc -o logic_test --coverage logic_test.c input.c board.c logic.c score.c

main: main.c input.c board.c logic.c score.c minesweeper.h
	gcc -o main main.c input.c board.c logic.c score.c