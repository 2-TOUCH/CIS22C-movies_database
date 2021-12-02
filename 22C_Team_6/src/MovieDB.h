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

/**
 * Movie database that internally uses both BST and hash table to support required operations efficiently.
 */
class MovieDB {
public:
    MovieDB();
    ~MovieDB();

    /**
     * Insert movie to the database.
     * @param movie Movie to be inserted.
     */
    void addMovie(const Movie& movie);
    /**
     * Find movie by its primary key.
     * @param id Movie's primary key.
     * @param movie output reference to be filled with the found movie.
     * @return true if found, false otherwise.
     */
    bool findMovieByID(const MovieID& id, Movie& movie);
    /**
     * Find movie by its secondary key (title)
     * @param title the title of the movie.
     * @return vector of movies with the same title.
     */
    std::vector<Movie> findMovieByTitle(const std::string& title);
    /**
     * List movie sorted by their secondary key (title)
     * @return vector of movies sorted by their titles.
     */
    std::vector<Movie> listMovieSortedByTitle();
    /**
     * List all movies using hash table
     * @return vector of movies
     */
    std::vector<Movie> getAllMovies() const;
    /**
     * Delete movie by it primary key.
     * @param id Movie's primary key.
     * @param movie output reference to be filled with the deleted movie.
     * @return true if found, false otherwise.
     */
    bool deleteMovieByID(const MovieID& id, Movie& deletedMovie);
    /**
     * Reserve hash table buckets.
     * @param buckets number of buckets to be reserved.
     */
    void reserveHashBuckets(size_t buckets);
    /**
     * Get statistics of the internal data structures of the database.
     * @returns stats
     */
    MovieDBDSStats getDataStructureStats() const;
    void printIndentedTree(void visit(Movie&, int)){BST.printTree(visit);}

private:
    HashTable<MovieID, Movie> hashTable;
    BinaryTree BST;

};
