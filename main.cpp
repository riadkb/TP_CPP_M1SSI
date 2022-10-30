#include <iostream>
#include <fstream>
#include <string.h>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;


map<string, int> readFile(string filePath) {

    ifstream file;
    file.open(filePath);

    string line;
    map<string, int> fMap;

    while (getline(file, line)){
        int index = 0;
        string word = "";
        for (int i=0; i<line.length(); i++){
            string character = "";
            character += tolower(line[i]);
            if ((character != " ") & (int(line[i]) != 13) & (character.length() > 0)){
                word += character;
            } else{  // end word
                if (int(word[0]) != 0){  // not empty
                    if (fMap.count(word) == 1){  // already exist in map
                        fMap[word] ++;
                    }else{
                        fMap[word] = 1;
                    }
                    word = "";
                    index = i+1;
                }
            }
        }
        // last word
        if ((int(word[0]) != 13) & (int(word[0]) != 0)){  // not empyt or \n
            if (fMap.count(word) == 1){
                fMap[word] ++;
            }else{
                fMap[word] = 1;
            }
        }
    }
    file.close();
    return fMap;
}

//Main-----------------------------------------------------------------------
int main(int argc, char *argv[]) {
    f1 = readFile(argv[1]);
    f2 = readFile(argv[2]);
    vector<string> keys;
    for (auto it = f1.begin(); it != f1.end(); ++it) {
        if (find(keys.begin(), keys.end(), it->first) == keys.end()){
            // not found
            keys.push_back(it->first);
        }
    }
    for (auto it = f2.begin(); it != f2.end(); ++it) {
        if (find(keys.begin(), keys.end(), it->first) == keys.end()){
            // not found
            keys.push_back(it->first);
        }
    }
    int product, module1, module2 = 0;
    int effectif1, effectif2 = 0;
    for (int i=0; i<keys.size(); i++){
        if (f1.count(keys[i]) == 1){
            effectif1 = f1[keys[i]];}else effectif1 = 0;
        if (f2.count(keys[i]) == 1){
            effectif2 = f2[keys[i]];}else effectif2 = 0;
        product += effectif1*effectif2;
        module1 += pow(effectif1, 2);
        module2 += pow(effectif2, 2);
    }
    float similarity = (product / (sqrt(module1) * sqrt(module2))) * 100;
    cout << similarity << "%\n";
    return 0;
}