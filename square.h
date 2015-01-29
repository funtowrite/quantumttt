#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Square{
	vector<string> moves;
	int pos;
public:
	Square(int);
	int get_pos();
	vector<string> get_moves();
	void add(string);
	void clear();
	char get_val(int);
    string format_string();
};

Square::Square(int pos){
	this->pos = pos;
}

int Square::get_pos(){
	return this->pos;
}

void Square::add(string next){
	this->moves.push_back(next);
}

void Square::clear(){
	this->moves.clear();
}

vector<string> Square::get_moves(){
	return this->moves;
}

char Square::get_val(int i){
	if (this->moves.size() > i){
		return this->moves[i][0];
	}
	return 0;
}

string Square::format_string(){
	int i;
	string moves_list = "";

    for (i = 0; i < this->moves.size(); i++){
        moves_list += this->moves[i];

		if ((i + 1)%3 == 0){
			moves_list += "\n\n";
		}
		else {
			moves_list += "  ";
		}
	}
	return moves_list;
}
