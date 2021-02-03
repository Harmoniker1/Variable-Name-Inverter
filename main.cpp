/* 
 * Variable Name Inverter
 * 
 * Copyright © 2021 Howard C.
 * 
 * Changes variable names from "var_" to "_var",
 * assuming all variables with underscores are named this way
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

inline bool isAlphabet(char c)
{
    return ((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z'));
}

inline bool isNumber(char c)
{
    return (c >= '0') && (c <= '9');
}

inline bool inVariable(char c)
{
    return isAlphabet(c) || isNumber(c) || (c == '_');
}

int main()
{
    ifstream ifs;
    ofstream ofs;

    string file;
    cin >> file;
    ifs.open(file);
    if (!ifs.is_open()) {
        cout << "Cannot open file." << endl;
        return 0;
    }

    ofs.open("out-" + file);
    string buf;
    char c;
    while ((c = ifs.get()) != EOF) {
        if ((c == ' ') || (c == '\n')) {
            ofs << buf << c;
            buf.clear();
        } else if (c == '_') {
            char c2 = ifs.peek();
            if (inVariable(c2)) { // variable name not finished
                buf += c;
                continue;
            }

            int idx;
            for (idx = buf.size() - 1; idx >= 0; idx--) {
                if (!inVariable(buf[idx])) {
                    idx++;
                    break;
                }
            }
            if (idx == -1) {
                idx = 0;
            }

            if (isNumber(buf[idx])) {
                cout << "I think something's wrong here..." << endl;
                return 0;
            }

            ofs << buf.substr(0, idx) << '_' << buf.substr(idx, buf.size() - idx);
            buf.clear();
        } else {
            buf += c;
        }
    }

    ofs << buf;
    ifs.close();
    ofs.close();
    return 0;
}