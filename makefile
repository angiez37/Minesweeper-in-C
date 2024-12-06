logic_test: logic_test.c input.c board.c logic.c score.c output.c gui.c minesweeper.h
	gcc -o logic_test --coverage logic_test.c input.c board.c logic.c score.c output.c gui.c -lm -lgtk-3 $(FLAG1) $(FLAG2)

score_test: score_test.c input.c board.c logic.c score.c output.c gui.c minesweeper.h
	gcc -o score_test --coverage score_test.c input.c board.c logic.c score.c output.c gui.c -lm -lgtk-3 $(FLAG1) $(FLAG2)

FLAG1 = `pkg-config --cflags gtk+-3.0`
FLAG2 = `pkg-config --libs gtk+-3.0`

minesweeper: minesweeper.c input.c board.c logic.c score.c output.c gui.c minesweeper.h
	gcc -o minesweeper minesweeper.c input.c board.c logic.c score.c output.c gui.c -lm -lgtk-3 $(FLAG1) $(FLAG2)

board_test: ./board_tests/board_test.c board.c ./board_tests/board.h 
	gcc -o board_test --coverage ./board_tests/board_test.c board.c

output_test: output_test.c board.c logic.c output.c minesweeper.h
	gcc -o output_test --coverage output_test.c board.c logic.c output.c
