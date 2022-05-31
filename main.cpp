#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
using namespace std;

void CreatePuzzle();
void OpenPuzzle();
void SolvePuzzle();


int main() {
	int option = 0;
	bool flag = true;
	cout << "Choose an option: " << endl
		<< "(1) Create a new puzzle" << endl
		<< "(2) Open an existing puzzle" << endl
		<< "(3) Solve an existing puzzle" << endl
		<< "(4) Exit" << endl;
	do
	{
		cout << "Option : ";
		cin >> option;
		switch (option)
		{
		case 1:
			CreatePuzzle();
			break;
		case 2:
			OpenPuzzle();
			break;
		case 3:
			SolvePuzzle();
			break;
		case 4:
			cout << "Program end" << endl;
			exit(1);
		default:
			cout << "Invalid value";
			break;
		}
	} while (flag);
}


void CreatePuzzle() {
	char ans;
	int words_num = 0, row = 0, col = 0, len = 0;
	cout << "How many words would you like to enter?" << endl
		<< "Words : ";
	cin >> words_num;
	string* words_array = new string[words_num];
	for (int i = 0; i < words_num; i++) {
		cin >> words_array[i];
		if (len < words_array[i].length()) {
			len = words_array[i].length() * 3;
		}
	}
	row = len;
	col = len;
	char** alpha = new char* [row];
	for (int i = 0; i < row; i++) {
		alpha[i] = new char[col];
	}
	char** solution = new char* [row];
	for (int i = 0; i < row; i++) {
		solution[i] = new char[col];
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			alpha[i][j] = 'a' + rand() % 26;
			solution[i][j] = ' ';
		}
	}

	int theRow = 0, theCol = 0;
	for (int index = 0; index < words_num; index++) {
		int count = 0;
		if (words_array[index].length() % 2 == 0) {
			for (int i = 0; words_array[index][i] != '\0'; i++, theCol++) {
				alpha[theRow][theCol] = words_array[index][i];
				solution[theRow][theCol] = words_array[index][i];
				count++;
			}
			theCol = theCol - count + 1;
			theRow++;
		}
		else {
			for (int i = 0; words_array[index][i] != '\0'; i++, theRow++) {
				alpha[theRow][theCol] = words_array[index][i];
				solution[theRow][theCol] = words_array[index][i];
				count++;
			}
			theRow = theRow - count + 1;
			theCol++;
		}
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << alpha[i][j];
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "Solutions" << endl << endl;
	for (int i = 0; i < words_num; i++) {
		for (int j = 0; words_array[i][j] != '\0'; j++) {
			cout << words_array[i][j];
		}
		cout << endl;
		cout << endl;
	}

	cout << "Would you like to save this? (y/n) : ";
	cin >> ans;
	if (ans == 'y' || ans == 'Y') {
		string fileName;
		cout << "Enter the file name : ";
		cin >> fileName;
		fstream fileData1, fileData2;
		fileData1.open(fileName + ".txt", ios::out);
		if (fileData1.is_open()) {
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					fileData1 << alpha[i][j];
					fileData1 << " ";
				}
				fileData1 << endl;
			}
			fileData1 << endl;
			fileData1 << "Solutions" << endl << endl;
			for (int i = 0; i < words_num; i++) {
				for (int j = 0; words_array[i][j] != '\0'; j++) {
					fileData1 << words_array[i][j];
				}
				fileData1 << endl;
				fileData1 << endl;
			}
		}
		fileName += "Solutions";
		fileData2.open(fileName + ".txt", ios::out);
		if (fileData2.is_open()) {
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					fileData2 << solution[i][j];
					fileData2 << " ";
				}
				fileData2 << endl;
			}
		}
	}
}

void OpenPuzzle() {
	string fileName;
	cout << "Enter the file name : ";
	cin >> fileName;
	fstream fileData;
	fileData.open(fileName + ".txt", ios::in);
	if (fileData.is_open()) {
		string data;
		while (getline(fileData, data)) {
			cout << endl;
			cout << data;
		}
	}
	else {
		cout << "File opening failed" << endl;
	}
}

void SolvePuzzle() {
	string fileName;
	cout << "Enter the file name : ";
	cin >> fileName;
	fileName += "Solutions";
	fstream fileData;
	fileData.open(fileName + ".txt", ios::in);
	if (fileData.is_open()) {
		string data;
		while (getline(fileData, data))
		{
			cout << data << endl;
		}
	}
}