logic_test: logic_test.c input.c board.c logic.c score.c output.c gui.c minesweeper.h
	gcc -o logic_test --coverage logic_test.c input.c board.c logic.c score.c output.c gui.c -lm -lgtk-3 $(FLAG1) $(FLAG2)

score_test: score_test.c input.c board.c logic.c score.c output.c gui.c minesweeper.h
	gcc -o score_test --coverage score_test.c input.c board.c logic.c score.c output.c gui.c -lm -lgtk-3 $(FLAG1) $(FLAG2)

FLAG1 = `pkg-config --cflags gtk+-3.0`
FLAG2 = `pkg-config --libs gtk+-3.0`

minesweeper: minesweeper.c input.c board.c logic.c score.c output.c gui.c minesweeper.h
	gcc -o minesweeper minesweeper.c input.c board.c logic.c score.c output.c gui.c -lm -lgtk-3 $(FLAG1) $(FLAG2)