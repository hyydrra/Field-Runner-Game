#ifndef READTEXTFILE_H
#define READTEXTFILE_H

#include "rsdl.h"
#include <string>
#include <vector>

class ReadTextFile {
public:
    std::vector<std::vector<int>> read(std::vector<Point> &path);
    
private:
    std::vector<int> string_to_arr(std::string str);
    std::vector<Point> vector_int_to_point(std::vector<int> input);
    std::vector<int> enemy_count_to_list(std::vector<int>);
    std::vector<int> shuffle_list(std::vector<int> enemy_list);
};

#endif
