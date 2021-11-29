#pragma once

#include <string>
#include <functional>
#include <vector>

#include "Movie.h"
#include "HashTable.h"
#include "MovieBST.h"

uint64_t movieIDHasher(const MovieID& id);

struct MovieDBDSStats {
    double hashTableLoadFactor;
    size_t hashTableBucketsCount;
    size_t hashTableNumCollisions;

    size_t bstHeight;
};

class MovieDB {
public:
    MovieDB();
    ~MovieDB();

    void addMovie(const Movie& movie);
    bool findMovieByID(const MovieID& id, Movie& movie);
    std::vector<Movie> findMovieByTitle(const std::string& title);
    std::vector<Movie> listMovieSortedByTitle();
    std::vector<Movie> getAllMovies();
    bool deleteMovieByID(const MovieID& id, Movie& deletedMovie);

    void reserveHashBuckets(size_t buckets);
    MovieDBDSStats getDataStructureStats() const;
private:
    HashTable<MovieID, Movie> hashTable;
    BinaryTree BST; 

};
