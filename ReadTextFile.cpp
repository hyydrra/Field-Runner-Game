#include "ReadTextFile.h"
#include "rsdl.h"
#include <fstream>
#include <algorithm>
#include <random>

using namespace std;

vector<vector<int>> ReadTextFile::read(vector<Point> &path) {

    string line;
    getline(cin, line);

    vector<vector<int>> enemy_list;
    path = vector_int_to_point(string_to_arr(line));
    while (getline(cin, line)){
        enemy_list.push_back(shuffle_list(enemy_count_to_list(string_to_arr(line))));
    }
    return enemy_list;
}

vector<int> ReadTextFile::enemy_count_to_list(vector<int> list){
    vector<int> seperated;
    for (int i=0; i<list.size(); i++){
        for(int j=0; j<list[i]; j++){
            seperated.push_back(i+1);
        }
    }
    return seperated;
}

vector<int> ReadTextFile::shuffle_list(vector<int> list){
    auto rng = std::default_random_engine {};
    shuffle(std::begin(list), std::end(list), rng);
    return list;
}

vector<int>  ReadTextFile::string_to_arr(string str)
{
    vector< int > arr;
    string word = "";
    for (auto x : str){
        if (x == ' ' || x == '\t'){
            if (word != ""){
                arr.push_back(stoi(word));
                word = "";
            }
        }
        else
            word = word + x;
    }
    if (word != ""){
        arr.push_back(stoi(word));
    }
    return arr;
}

vector<Point> ReadTextFile::vector_int_to_point(vector<int> input){
    vector<Point> path;
    for(int i=0; i<input.size()/2; i++){
        path.push_back(Point(input[2*i],input[2*i+1]));
    }
    return path;
}