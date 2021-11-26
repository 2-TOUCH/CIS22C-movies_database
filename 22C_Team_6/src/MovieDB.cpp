#include "MovieDB.h"

const static size_t DEFAULT_HASH_BUCKETS_COUNT = 1;

// Hash movie id using fnv hash function
const static uint64_t fnvSeed = 14695981039346656037ull;
const static uint64_t fnvPrime = 1099511628211ull;
uint64_t movieIDHasher(const MovieID& movieID) {
    uint64_t result = fnvSeed;
    size_t alignedSize = movieID.size() - movieID.size() % 8;
    // Hash each 8-byte chunk of the movie id
    for (size_t i = 0; i < alignedSize; i+=8) {
        result ^= *reinterpret_cast<const uint64_t*>(movieID.data() + i);
        result *= fnvPrime;
    }
    // Hash unaligned part
    for (size_t i = alignedSize; i < movieID.size(); ++i) {
        result ^= movieID[i];
        result *= fnvPrime;
    }
    return result;
}

MovieDB::MovieDB() : hashTable(movieIDHasher, DEFAULT_HASH_BUCKETS_COUNT) {
}

MovieDB::~MovieDB() {
}

void MovieDB::addMovie(const Movie& movie) {
    hashTable.add(movie.getID(), movie);
    BST.insert(movie);
    if (hashTable.getLoadFactor() > 0.75) {
        hashTable.rehash(hashTable.getBucketsCount() * 2);
    }
}

bool MovieDB::deleteMovieByID(const MovieID& id, Movie& deletedMovie) {
    return hashTable.remove(id, deletedMovie);
}

bool MovieDB::findMovieByID(const MovieID& id, Movie& movie) {
    return hashTable.find(id, movie);
}


void MovieDB::reserveHashBuckets(size_t buckets) {
    hashTable.rehash(buckets);
}
void MovieDB::listMovieSortedByTitle()
{
  BST.inOrder();
}

MovieDBDSStats MovieDB::getDataStructureStats() const {
    MovieDBDSStats stats;
    stats.hashTableBucketsCount = hashTable.getBucketsCount();
    stats.hashTableLoadFactor = hashTable.getLoadFactor();
    stats.hashTableNumCollisions = hashTable.getNumberOfCollisions();
    return stats;
}
