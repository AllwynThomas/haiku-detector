#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cctype>
#include <unordered_map>

using namespace std;

unordered_map<string, int> dict;

// Function for counting syllables per line
string sylCounter(string line){
    stringstream ss;
    string inputWord = "";
    string sylLine;
    int wordSyl = 0;
    int lineSyl = 0;
    bool firstWord = true;
    bool lineError = false;
    ss << line;
    line = "";

    while (ss >> inputWord){
        bool wordError = false;
        wordSyl = dict[inputWord];
        if (wordSyl == 0 && firstWord){
            inputWord[0] = tolower(inputWord[0]);
            if ((wordSyl = dict[inputWord]) != 0){
                inputWord[0] = toupper(inputWord[0]);
            }
        }
        if (wordSyl == 0){
            wordError = true;
            lineError = true;
        }
        lineSyl += wordSyl;
        if (wordError){
            line += inputWord + "(?) ";
        }
        else {
            line += inputWord + "(" + to_string(wordSyl) + ") ";
        }
        firstWord = false;
    }
    if (!lineError){
        sylLine = to_string(lineSyl) + " : ";
    }
    else {
        sylLine = to_string(lineSyl) + "?: ";
    }
    sylLine += line;
    return sylLine;
}

int main(int argc, char *argv[]){
    // Reading text file words and adding word/syllable pairs to dictionary
    ifstream inFile;
    inFile.open("mhyph.txt");
    
    char ch;
    string word;
    int sylCount = 1;
    
    while ((ch = inFile.get()) != EOF){
        switch (ch){
        case '-':
            sylCount++;
            continue;
            break;
        case ' ':
        case '\n':
            dict[word] = sylCount;
            word = "";
            sylCount = 1;
            continue;
            break;
        default:
            word += ch;
            break;
        }
    }
    inFile.close();

    // Checking if user input is a haiku
    string line1;
    string line2;
    string line3;
    while (line1 != "/quit" && line2 != "/quit" && line3 != "/quit"){
        // Getting user input
        cout << "Enter your haiku with no punctuation in three separate lines by pressing enter after each line. (Type '/quit' to quit.)" << endl;
        getline(cin, line1);
        if (line1 == "/quit") {break;}
        getline(cin, line2);
        if (line2 == "/quit") {break;}
        getline(cin, line3);
        if (line3 == "/quit") {break;}

        bool fail = false;
        line1 = sylCounter(line1);
        line2 = sylCounter(line2);
        line3 = sylCounter(line3);
        cout << endl << line1 << endl << line2 << endl << line3 << endl << endl;

        // Checking for 5-7-5 syllable structure in the 3 lines
        if (line1.front() != '5'){
            cout << "Not a haiku: Line 1 has " << line1.front() << " syllables instead of 5 syllables." << endl;
            fail = true;
        } 
        else if (line1[1] == '?'){
            cout << "Not a haiku: Line 1 has unrecognized words marked with '(?)'." << endl;
            fail = true;
        }
        if (line2.front() != '7'){
            cout << "Not a haiku: Line 2 has " << line2.front() << " syllables instead of 7 syllables." << endl;
            fail = true;
        }
        else if (line2[1] == '?'){
            cout << "Not a haiku: Line 2 has unrecognized words marked with '(?)'." << endl;
            fail = true;
        }
        if (line3.front() != '5'){
            cout << "Not a haiku: Line 3 has " << line3.front() << " syllables instead of 5 syllables." << endl;
            fail = true;
        }
        else if (line3[1] == '?'){
            cout << "Not a haiku: Line 3 has unrecognized words marked with '(?)'." << endl;
            fail = true;
        }
        if (!fail){
            cout << "You wrote a haiku!" << endl;
        }
        cout << endl;
    }
    cout << "Quitting..." << endl;
    exit(0);
    return 0;
}