#pragma once

#include <fstream>
#include "MovieDB.h"

class FileWriter {
public:
    FileWriter(std::ofstream&& file);
    ~FileWriter() = default;

    void save(const MovieDB& db);
private:
    std::ofstream file;
};
