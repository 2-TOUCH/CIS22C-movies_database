#include "FIleLoader.h"
#include "Util.h"

FileLoader::FileLoader(std::ifstream&& stream) : file(std::move(stream)) {
}

void FileLoader::load(MovieDB& db) {
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        lines.emplace_back(line);
    }

    db.reserveHashBuckets(lines.size()); // preallocate hash table; lines.size == movies.size

    for (const auto& line : lines) {
        auto tokens = split(line, "^");
        if (tokens.size() != 6) {
            throw std::runtime_error("Invalid file format: number of fields is invalid");
        }
        MovieID id = tokens[0];
        std::string title = tokens[1];
        std::string lang = tokens[2];
        int year = std::stoi(tokens[3]);
        std::string director = tokens[4];
        bool isAdult = static_cast<bool>(std::stoi(tokens[5]));
        Movie movie(id, title, lang, year, director, isAdult);
        db.addMovie(movie);
    }
}