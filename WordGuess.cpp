#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

bool validWord(string input);
bool won(string input);
string guesses = "";

vector< vector<char> > board(6);
int countTurns;
string solution;

int main() {

    cout << "\nWelcome To Word Guess!\nGuess the five letter word in only six tries.\n\033[31mRed\033[0m letters are in the wrong location but exist in the word.\n\033[32mGreen\033[0m letters are in the correct location.\n\033[96mBlue\033[0m means the letter is in the right spot but that letter appears again!\nEnter \"q\" at any time to quit.\n" << endl;

    srand (time(0));
    int location = rand() % 5756 + 1;
    ifstream inFile;
    inFile.open("wordFile.txt");

    inFile.seekg(location * 6, ios::beg);
    getline(inFile, solution);

    inFile.close();

    string input;
    countTurns = 0;
    
    do {
        do {
        cout << "Enter your guess: ";
        cin >> input;
        cout << "\n";
        } while (!validWord(input));
    } while (!won(input) && countTurns != 6);

    cout << "You ran out of tries!\nThe word to guess was \"" + solution + "\"\n" << endl;
    exit(2);

}

bool validWord(string input) {

    if (input == "q") {
        exit(2);
    }

    if (input.length() != 5) {
        cout << "Make sure the word is 5 letters\n" << endl;
        return false;
    }

    string line;
    size_t pos;
    ifstream inFile;

    inFile.open("wordFile.txt");

    string:: iterator it;

    for (it = input.begin(); it != input.end(); it++) {
        *it = tolower(*it);
    }

    while(inFile.good())
    {
        getline(inFile,line);
        pos=line.find(input);
        if(pos!=string::npos)
        {
            inFile.close();
            return true;
        }
    }

    inFile.close();
    cout << "This word does not exist\n" << endl;
    return false;
}

bool won(string input) {

    for(int i = 0; i < 6; i++) {
        board[countTurns].push_back(input[i]);
        if (solution.find(input[i]) != string::npos) {
            if (input[i] == solution[i]) {
                if (count(solution.begin(), solution.end(), input[i]) > 1) {
                    guesses.append("\033[96m");
                    guesses.push_back(input[i]);
                    guesses.append("\033[0m");
                } else {
                    guesses.append("\e[32m");
                    guesses.push_back(input[i]);
                    guesses.append("\e[0m");
                }
            } else {
                guesses.append("\033[31m");
                guesses.push_back(input[i]);
                guesses.append("\033[0m");
            }
        } else {
            guesses.push_back(input[i]);
        }
    }
    guesses.append("\n");
    countTurns++;

    cout << "Current Guesses\n------------\n" << endl;
    cout << guesses << endl;
    cout << "------------\n" << endl;

    if (input == solution) {
        cout << "You guessed the word! It was \"" + input + "\"\n" << endl;
        exit(3);
        return true;
    }

    return false;
}