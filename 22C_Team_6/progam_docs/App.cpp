#include "App.h"

#include <iostream>
#include <vector>

// Function for the indented Tree display
void visit(Movie& item, int level) {
    for (int i = 1; i < level; i++)
        std::cout << "..";
    std::cout << level << "). " << item.getTitle() << std::endl;
}

int App::run() {
    bool quit = false;
    std::cout << "*****Welcome to Movies Database      *****" << std::endl;
    std::cout << "*****Abdullah, Arnesh, Sunho, Ulysses*****" << std::endl;
    while (!quit) {
        printMenu();
        char choice;
        std::cin >> choice;
        std::cin.ignore();
        switch (choice) {
            case 'l':
                processLoadFileCmd();
                break;
            case 'L':
                processLoadFileCmd();
                break;
            case 'p':
                processSearchByKeyCmd();
                break;
            case 'P':
                processSearchByKeyCmd();
                break;
            case 'd':
                processDeleteByKeyCmd();
                break;
            case 'D':
                processDeleteByKeyCmd();
                break;
            case 'I':
                processDisplayHashStatsCmd();
                break;
            case 'u':
                processUndoDeleteCmd();
                break;
            case 'U':
                processUndoDeleteCmd();
                break;
            case 's':
                processSearchByTitleCmd();
                break;
            case 'a':
                processDisplayAllKeyCmd();
                break;
            case 'e':
                quit = true;
                break;
            case 'A':
                processAddCmd();
                break;
            case 'S':
                processSaveFileCmd();
                break;
            case 'H':
                continue;
                break;
            case 'h':
                processDisplayAllMemCmd();
                break;
            case 'z':
                processDisplayIndentedTreeCmd();
                break;
            default:
                std::cout << "Invalid choice" << std::endl;
        }
    }
    return 0;
}

void App::printMenu() {
    std::cout << "Load file: L/l" << std::endl;
    std::cout << "Search movie by primary key: P/p" << std::endl;
    std::cout << "Delete by primary key: D/d" << std::endl;
    std::cout << "List all Movies: a" << std::endl;
    std::cout << "Search movie by secondary key: s" << std::endl;
    std::cout << "H -- for help: H" << std::endl;
    std::cout << "Add new Movie: A" << std::endl;
    std::cout << "Save Movie Database to a file: S" << std::endl;
    std::cout << "Show Table Statistics: I" << std::endl;
    std::cout << "Undo movie deletion: u" << std::endl;

    std::cout << "Exit: e" << std::endl;
}

// Function loads the input file
void App::processLoadFileCmd() {
    std::cout << std::endl;
    std::cout << "Input file name:";
    std::string fileName;
    std::cin >> fileName;

    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cout << "File not found" << std::endl;
        return;
    }

    try {
        // resetMovieDB();
        FileLoader fileLoader(std::move(file));
        fileLoader.load(movieDB);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << "File loaded" << std::endl
              << std::endl;
}

// Function saves the data into a file
void App::processSaveFileCmd() {
    std::cout << std::endl
              << "Input file name:";
    std::string fileName;
    std::cin >> fileName;

    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cout << "Invalid file name" << std::endl;
        return;
    }

    try {
        FileWriter fileWriter(std::move(file));
        fileWriter.save(movieDB);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << "File saved" << std::endl
              << std::endl;
}

// Function searches through the primary keys
void App::processSearchByKeyCmd() {
    std::cout << std::endl
              << "Input primary key:";
    std::string key;
    std::getline(std::cin, key);

    Movie movie;
    bool found = movieDB.findMovieByID(key, movie);
    if (found) {
        movie.vDisplay(std::cout);
        std::cout << std::endl;
    } else {
        std::cout << "Movie not found" << std::endl
                  << std::endl;
    }
}

// Function deletes Movie object from list
void App::processDeleteByKeyCmd() {
    std::cout << std::endl
              << "Input primary key:";
    std::string key;
    std::getline(std::cin, key);

    Movie movie;
    bool deleted = movieDB.deleteMovieByID(key, movie);
    if (deleted) {
        std::cout << "Movie deleted" << std::endl
                  << std::endl;
        deletedMovieStack.push(movie);
    } else {
        std::cout << "Movie not found" << std::endl
                  << std::endl;
    }
}

// Function undos delete
void App::processUndoDeleteCmd() {
    if (deletedMovieStack.empty()) {
        std::cout << "No more movie delete to undo" << std::endl;
        return;
    }
    Movie movie = deletedMovieStack.top();
    deletedMovieStack.pop();
    movieDB.addMovie(movie);
    std::cout << "Movie delete undone: " << std::endl;
    movie.vDisplay(std::cout);
}

// Function searches via secondary key
void App::processSearchByTitleCmd() {
    std::cout << std::endl
              << "Input Secondary key:";
    std::string key;
    std::getline(std::cin, key);
    std::vector<Movie> movieList = movieDB.findMovieByTitle(key);

    if (movieList.size() > 0) {
        for (int i = 0; i < movieList.size(); i++)
            movieList[i].vDisplay(std::cout);
        std::cout << std::endl;
    } else
        std::cout << "Movie not found" << std::endl
                  << std::endl;
}

// Adds a new movie into the list
void App::processAddCmd() {
    std::string primaryK;
    std::string title;
    std::string lang;
    int year;
    std::string direc;
    bool rating;
    std::cout << std::endl
              << "Enter Primary Key:";
    std::getline(std::cin, primaryK);
    std::cout << "Enter Title:";
    std::getline(std::cin, title);
    std::cout << "Enter Language:";
    std::getline(std::cin, lang);
    std::cout << "Enter release year:";
    std::cin >> year;
    std::cin.ignore();
    std::cout << "Enter Director:";
    std::getline(std::cin, direc);
    std::cout << "Enter rating(1=Adult/0=NoAdult):";
    std::cin >> rating;
    Movie movie(primaryK, title, lang, year, direc, rating);
    movieDB.addMovie(movie);

    std::cout << std::endl;
}

// Display all movies
void App::processDisplayAllKeyCmd() {
    std::cout << std::endl;
    std::cout << "All Movies In List" << std::endl;
    std::cout << "==================" << std::endl;

    std::vector<Movie> list;
    list = movieDB.listMovieSortedByTitle();
    for (int i = 0; i < list.size(); i++)
        std::cout << list[i];

    std::cout << std::endl;
}

// Display Team Members(Hidden Feature)
void App::processDisplayAllMemCmd() {
    std::cout << std::endl
              << std::endl
              << "Team 6 Members" << std::endl;
    std::cout << "Abdullah, Arnesh, Sunho, Ul" << std::endl;
    std::cout << "*****Abdullah, Arnesh, Sunho, Ulysses*****" << std::endl
              << std::endl;
}

// Display Hash Table Statistics
void App::processDisplayHashStatsCmd() const {
    MovieDBDSStats stats = movieDB.getDataStructureStats();
    std::cout << "Hash Table Statistics:" << std::endl;
    std::cout << "Load Factor: " << stats.hashTableLoadFactor << std::endl;
    std::cout << "Bucket Count: " << stats.hashTableBucketsCount << std::endl;
    std::cout << "Num of Collisions: " << stats.hashTableNumCollisions << std::endl;
}

void App::processDisplayIndentedTreeCmd() {
    movieDB.printIndentedTree(visit);
}
