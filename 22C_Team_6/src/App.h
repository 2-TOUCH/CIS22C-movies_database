#pragma once

#include <vector>
#include <stack>

#include "MovieDB.h"
#include "FileLoader.h"
#include "FileWriter.h"

class App {
public:
    App() = default;
    ~App() = default;

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

    void resetMovieDB() { movieDB = MovieDB(); }

    MovieDB movieDB;
    std::stack<Movie> deletedMovieStack;
};
