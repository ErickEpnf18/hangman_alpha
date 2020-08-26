#include<iostream>
#include<algorithm>
#include<string>
#include<fstream>
#include<random>
#include<list>
#include <ctime>
#include "Graphics.cpp"

using namespace std;

class Hangman {
private:
    string word = "";
    string answer = "";
//    word_category = "";
    int countHang = 0;
    char ch = 0;
    bool active = true;
    string symbols = "+-_|.()/\\'\"`,|:;";
    string used_chars = "";
public:
    bool exit = false;

    Hangman() {
        active = 1;
        while (active) {
            cout << Graphics::start_game();
            cout << "Type something-->";
            cin >> ch;
            if (ch == '1') {
                active = 0;
                system("cls");
                get_word();
            } else if (ch == '0') {
                system("cls");
                active = 0;
                exit = true;
            } else {
                system("cls");
            }
        }
    };

    inline void get_word() {
        cout << Graphics::enter_word();
        cout << "Type something-->";
        cin >> word;
        transform(word.begin(), word.end(), word.begin(), tolower);
        cout << endl;
        system("cls");
//        cin.ignore();
//        cout << Graphics::enter_category();
//
//        getline(cin, word_category);
//        cout << endl;

        for (unsigned i = 0; i < word.length(); ++i)
            answer += "_";

        system("cls");
        start_game();
    }


    inline void start_game() {

        int i = 0;
        active = 1;

        while (active) {
            hang_check();
            for (unsigned i = 0; i < word.length(); ++i) {
                cout << answer[i] << " ";
            }
            cout << "\n\nNext letter -->";
            cin >> ch;
            if (check_char(ch, used_chars)) {
                used_chars.push_back(ch);

                if (ch <= 90 && ch >= 65)
                    ch += 32;

                i = word.find(ch);
                while (word.find(ch, i) != string::npos) {
                    answer[word.find(ch, i)] = ch;
                    i++;
                }

                if (word.find(ch) == string::npos) {
                    countHang++;
                }

                if (countHang == 10) {
                    system("cls");
                    end_game();
                } else if (answer == word) {
                    system("cls");
                    end_game();
                }
            }
            system("cls");
        }
    }

    inline void end_game() {
        active = 1;
        while (active) {
            if (countHang == 10) {
                cout << Graphics::get_stage(countHang) << endl;
            } else {
                cout << Graphics::get_stage(11) << endl;
            }
            cout << "The word was : " << word << endl;
            cout << "Type something-->";
            cin >> ch;
            if (ch == '1') {
                active = 0;

                system("cls");
                countHang = 0;
                word = "";
                answer = "";
//                word_category = "";
                get_word();
            } else if (ch == '0') {
                system("cls");
                active = 0;
                exit = 1;
            } else {
                system("cls");
            }
        }
    }

    inline void hang_check() {
        cout << modify_keyboard(Graphics::get_stage(countHang)) << endl;
    }

    inline string modify_keyboard(string keyboard_string) {
        for (int i = 0; i < keyboard_string.length(); i++) {
            for (int j = 0; j < used_chars.length(); j++) {
                if (check_char(keyboard_string[i], symbols) && used_chars[j] == keyboard_string[i]) {
                    keyboard_string[i] = '#';
                }
            }
        }
        return keyboard_string;
    }

    inline bool check_char(char ch, string check_symbols) {
        for (int i = 0; i < check_symbols.length(); ++i) {
            if (ch == check_symbols[i]) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    Hangman game;
    if (game.exit == 1) return 0;

    cin.get();
    return 0;
}