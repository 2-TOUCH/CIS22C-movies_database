/**
File/IO Abdullah Malik

The following helps write the data in the BST to a new text file
**/

#pragma once

#include <fstream>

#include "MovieDB.h"

/**
 * File writer that writes txt file based on movies in MovieDB
 */
class FileWriter {
  public:
    /**
     * Constructor
     * @param file ofstream object that has been opened with output file
     */
    FileWriter(std::ofstream&& file);
    ~FileWriter() = default;

    /**
     * Write the file based on specified MovieDB
     * @param db MovieDB reference
     */
    void save(const MovieDB& db);

  private:
    std::ofstream file;
};
