#pragma once

#include <fstream>
#include "MovieDB.h"

class FileLoader {
public:
    FileLoader(std::ifstream&& stream);
    ~FileLoader() = default;

    void load(MovieDB& db);
private:
    std::ifstream file;
};