#include <iostream>
#include <string>
#include <vector>
#include "square.h"

using namespace std;

class Board{
	vector<Square> squares;

public:
	Board(int);
	void add(string, int);
	vector<Square> get_squares();
	char get_square_val(int);
	int num_wins(char);
};

Board::Board(int size){
	int i;
	for (i=0; i < size*size; i++){
		Square s(i);
		this->squares.push_back(s);
	}
}

void Board::add(string val, int pos){
	this->squares[pos].add(val);
}

vector<Square> Board::get_squares(){
	return this->squares;
}

char Board::get_square_val(int pos){
	return this->squares[pos].get_val(0);
}

int Board::num_wins(char c){
	int wins = 0;
	char val0 = this->squares[0].get_val(0);
	char val1 = this->squares[1].get_val(0);
	char val2 = this->squares[2].get_val(0);
	char val3 = this->squares[3].get_val(0);
	char val4 = this->squares[4].get_val(0);
	char val5 = this->squares[5].get_val(0);
	char val6 = this->squares[6].get_val(0);
	char val7 = this->squares[7].get_val(0);
	char val8 = this->squares[8].get_val(0);

	if (val0 == val1 && val1 == val2 && val0 == c){
		wins++;
	}
	if (val3 == val4 && val4 == val5 && val3 == c){
		wins++;
	}
	if (val6 == val7 && val7 == val8 && val6 == c){
		wins++;
	}
	if (val0 == val3 && val3 == val6 && val0 == c){
		wins++;
	}
	if (val1 == val4 && val4 == val7 && val1 == c){
		wins++;
	}
	if (val2 == val5 && val5 == val8 && val2 == c){
		wins++;
	}
	if (val0 == val4 && val4 == val8 && val0 == c){
		wins++;
	}
	if (val2 == val4 && val4 == val6 && val2 == c){
		wins++;
	}

	return wins;

}

/*int main()
{
	Board b(9);

	b.add("X1", 0);
	b.add("X2", 4);
	b.add("X4", 8);

	cout << b.num_wins('O');

    return 0;
}*/
