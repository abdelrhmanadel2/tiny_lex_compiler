#include <iostream>
#include <string>
#include <fstream>
#include<bits/stdc++.h>
using namespace std;

void getToken(string);
bool isDigit(char);
bool isLetter(char);
bool isSpace(char);
bool isSymbol(char);
bool isqouted(char s) ;
enum DFAstates { START, INCOMMENT, INNUM,qouted,INID,NESTED, INASSIGN, DONE };
DFAstates state = START; //set START to be intial state

string  RES_WORDS[8] = { "if","then","else","end","repeat","until","read","write" };

ofstream myfile,filla;
int main() {
	//reading sample tinys code from file
string s;

	ifstream file;
	int line =0;
	file.open("tiny_sample_code.txt");
	while (!file.eof()) {
		getline(file, s);
		line ++;

	}
	file.close();
	cout << line;


	 file.open("tiny_sample_code.txt");
	if (file.is_open())
	{/*
		size = file.tellg();
		memblock = new char[size];
		file.seekg(0, ios::beg);
		file.read(memblock, size);
		file.close();*/
		string content((std::istreambuf_iterator<char>(file)),
			(istreambuf_iterator<char>()));

		cout << "the entire file content is in memory \n";
   myfile.open("parser_input.txt");
    filla.open("pt.txt");
	getToken(content); // this is written to redir.txt
	myfile.close();
filla.close();
	}
	else cout << "Unable to open file";

	//writing scanner output to file











	//writing scanner output to file
	/*freopen("parser_input.txt", "w", stdout);
	getToken(code); // this is written to redir.txt
	fclose(stdout);
	file.open("parser_input.txt");
	while (!file.eof()) {
	getline(file, line);
		code += line;
	}

cout<<code;
*/
	return 0;
}

	struct tokeninfo {
		int line;
		std::string token;
		std::string type;
	};
bool isnl(char s) { return s == '\n'; }

void getToken(string l)
{
	struct  tokeninfo t[100];
	string mytoken;
	bool res_flag = 0;
	int i = 0;
	int j = 0;
	int tn=0;
	while (state != DONE) {
		switch (state) {
		case START:


			 if (isnl(l[i]) ) {
				i++;
				j++;
				cout << "\n"<<j<<" ";


				if (i == l.length()) state = DONE;
				else state = START;
			}
            else if (isSpace(l[i])) {
				i++;
				if (i == l.length()) state = DONE;
				else state = START;
			}
			else if (isDigit(l[i]) && !isLetter(l[i - 1])) {
				state = INNUM;
			}
			else if (isLetter(l[i])) {
				state = INID;
			}
			else if (l[i] == ':') {
				state = INASSIGN;
			}
			else if (l[i] == '{') {
				i++;

				state = INCOMMENT;
			}
			else if (isSymbol(l[i])) {
				switch (l[i]) {
				case ';': cout << l[i]; myfile << l[i];tn++;t[tn].token = ";";
					t[tn].type = "smicolne   ";
					t[tn].line = j; break;
				default: cout << l[i] << " ";myfile << l[i] << " ";tn++;t[tn].token = l[i];
					t[tn].type= "symbol     ";
					t[tn].line = j; break;
				}
				i++;
				if (i == l.length()) state = DONE;
				else state = START;
			}
			else state = DONE;
			break;

		case INCOMMENT:
			if (state == INCOMMENT) {
				while (l[i] != '}') {
					i++;
				}
				i++;
				if (i == l.length()) state = DONE;
				else state = START;
			}
			break;

		case INNUM:
			while (isDigit(l[i])) {
				mytoken += l[i];
				i++;
			}
			cout << "number" << " ";
			myfile << "number" << " ";
			tn++;
			t[tn].token= mytoken;
			t[tn].type = "number     ";
			t[tn].line = j;
			mytoken = "";
			if (i == l.length()) state = DONE;
			else state = START;
			break;

		case INID:
			while (isLetter(l[i])) {
				if (isdigit(l[i + 1])) {
					mytoken += l[i];
					mytoken += l[i + 1];
					i += 2;
				}
				else {
					mytoken += l[i];
					i++;
				}

			}
			for (int i = 0; i < 8; i++)
			{
				if (RES_WORDS[i] == mytoken) res_flag = 1;
			}
			if (res_flag) { cout << mytoken << " ";
                            myfile << mytoken << " ";
							tn++;
							t[tn].token = mytoken;
							t[tn].type = "keyword    ";
							t[tn].line = j;
			}
			else { cout << "identifier" << " " ;
			myfile << "identifier" << " ";
			tn++;
			t[tn].token = mytoken;
			t[tn].type = "identifier ";
			t[tn].line = j;
			}
			mytoken = "";
			res_flag = 0;
			if (i == l.length()) state = DONE;
			else state = START;
			break;

		case INASSIGN:
			if (l[i] == ':') {
				i += 2;
				cout << ":=" << " ";
				myfile << ":=" << " ";
				tn++;
				t[tn].token = ":=";
				t[tn].type = "assigenment";
				t[tn].line = j;
				state = START;
			}
			else {
				if (i == l.length()) state = DONE;
				else state = START;
			}
			break;
		case DONE:
			break;
		}

	}



	for (int h =1 ;h <= tn;h++) {
		filla<<t[h].token
		<<"\t\t"
		<< t[h].type
		<< "\t\t"
		<< t[h].line
		<< "\n";
	}

}

bool isDigit(char d) { return (d >= '0' && d <= '9'); }

bool isLetter(char l) { return (l >= 'a' && l <= 'z' || l >= 'A' && l <= 'Z'); }

bool isSpace(char s) { return (s == ' ' || s == '\t'); }

bool isSymbol(char c) { return (c == '+' || '-' || '*' || '/' || '=' || '<' || '(' || ')' || ';'); }


