#include <iostream>
#include <fstream>
#include "Value.h"
#include "definitions.h"
#include "Board.h"
#include "MiniMax_Game.h"

/*
 * The main function. It scans the input file and stores the data in a char matrix. It then makes a MiniMax_Game
 * object and a Board object and uses the MiniMax_Game object to predict the winner of this board. It outputs
 * the result to an output file.
 */
int main() {

	std::ifstream ifile("input.txt", std::ios::in);
	if (!ifile.is_open()) {
		std::cout << "ERROR: could not open input file" << std::endl;
	} else {
		char** board = new char*[ROWS];
		for (int i = 0; i < ROWS; i++) {
			board[i] = new char[COLS];
		}

		char currChar;
		int i = 0;
		int j;
		while (i < ROWS) {
			j = 0;
			while (j < COLS) {
				ifile >> currChar;
				board[i][j] = currChar;
				j++;
			}
			i++;
		}
		MiniMax_Game mg;
		Board b(board);
		char winner = mg.predictWinner(b);
		std::fstream ofile("output.txt", std::ios::out);
		if (ofile.is_open()) {
			ofile << winner;
			ofile.close();
		} else {
			std::cout << "ERROR opening output file" << std::endl;
		}
		ifile.close();
	}
}
