#pragma once

#include <fstream>
#include "MovieDB.h"

/**~*~*
 * File loader that reads txt file and insert movie to MovieDB
*~**/
class FileLoader {
public:
    /**~*~*
     * Constructor
     * @param stream ifstream object that has been opened with movie file
    *~**/
    FileLoader(std::ifstream&& stream);
    ~FileLoader() = default;

    /**~*~*
     * Read the file and insert movies to MovieDB
     * @param db MovieDB reference
    *~**/
    void load(MovieDB& db);
private:
    std::ifstream file;
};
