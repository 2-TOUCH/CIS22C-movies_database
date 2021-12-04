/**
File/IO Abdullah Malik

The following contains functions that help write a file similar to the one read.
It takes all the variables from each movie in the BST and adds them accordingly.
There were little challenges in this function as most of the additions could be 
made manually.

**/

#include "FileWriter.h"

FileWriter::FileWriter(std::ofstream&& file)
    : file(std::move(file)) {
}

void FileWriter::save(const MovieDB& db) {
    std::vector<Movie> allMovies = db.getAllMovies();
    for (int i = 0; i < allMovies.size(); i++) {
        file << allMovies[i].getID() << "^" << allMovies[i].getTitle()
             << "^" << allMovies[i].getLang() << "^" << std::to_string(allMovies[i].getYear())
             << "^" << allMovies[i].getDirector() << "^" << std::to_string(allMovies[i].getIsAdult()) << std::endl;
    }
}
