#include "FileWriter.h"

FileWriter::FileWriter(std::ofstream&& file) : file(std::move(file)) {
}

void FileWriter::save(const MovieDB& db) {
}