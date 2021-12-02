#pragma once

#include <vector>
#include <stack>

#include "MovieDB.h"
#include "FileLoader.h"
#include "FileWriter.h"

/**
 * App class that integrate all the other classes to implement the program
 * the main responsibility is dealing with user input and output
 */
class App {
public:
    App() = default;
    ~App() = default;

    /**
     * run the program
     */
    int run();
private:
    void printMenu();

    void processLoadFileCmd();
    void processSaveFileCmd();
    void processSearchByKeyCmd();
    void processSearchByTitleCmd();
    void processPrintSortedCmd();
    void processAddCmd();
    void processDeleteByKeyCmd();
    void processUndoDeleteCmd();
    void processDisplayAllKeyCmd();
    void processDisplayAllMemCmd();
    void processDisplayHashStatsCmd() const;   
    void processDisplayIndentedTreeCmd();
    void resetMovieDB() { movieDB = MovieDB(); }

    MovieDB movieDB;
    std::stack<Movie> deletedMovieStack;
};
