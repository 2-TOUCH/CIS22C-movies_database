#include "FileWriter.h"

FileWriter::FileWriter(std::ofstream&& file) : file(std::move(file)) {
}

void FileWriter::save(const MovieDB& db) {
  std::vector<Movie> allMovies = db.getAllMovies();
  for(int i = 0; i < allMovies.size(); i++)
   {
     file << allMovies[i].getID() << "^" << allMovies[i].getTitle() 
          << "^" << allMovies[i].getLang() << "^" << std::to_string(allMovies[i].getYear()) 
          << "^" << allMovies[i].getDirector() << "^" << std::to_string(allMovies[i].getIsAdult()) << std::endl; 
   }
}
 
