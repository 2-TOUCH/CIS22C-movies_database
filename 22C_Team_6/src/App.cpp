#include "App.h"
#include <iostream>
#include <vector>

int App::run() {
    bool quit = false;
    std::cout << "*****Welcome to Movies Database      *****" << std::endl;
    std::cout << "*****Abdullah, Arnesh, Sunho, Ulysses*****" << std::endl;
    while(!quit) {
        printMenu();
        char choice;
        std::cin >> choice;
        std::cin.ignore();
        switch(choice) {
        case 'l':
            processLoadFileCmd();
            break;
        case 'p':
            processSearchByKeyCmd();
            break;
        case 'd':
            processDeleteByKeyCmd();
            break;
        case 'u':
            processUndoDeleteCmd();
            break;
/*  	case 's':
	    processSearchBySecKeyCmd();
	    break;*/
        case 'a':
	    processDisplayAllKeyCmd();
	    break;
        case 'e':
            quit = true;
	     break;
        default:
            std::cout << "Invalid choice" << std::endl;
        }
    }
    return 0;
}

void App::printMenu() {
    std::cout << "Load file: l" << std::endl;
    std::cout << "Search movie by primary key: p" << std::endl;
    std::cout << "Delete by primary key: d" << std::endl;
    std::cout << "List all Movies: a" << std::endl;
    std::cout << "Undo movie deletion: u" << std::endl;
    std::cout << "Exit: e" << std::endl;
}

void App::processAddCmd() {
}

void App::processSearchByTitleCmd() {
}

void App::processLoadFileCmd() {
    std::cout << "Input file name:";
    std::string fileName;
    std::cin >> fileName;

    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cout << "File not found" << std::endl;
        return;
    }

    try {
        //resetMovieDB();
        FileLoader fileLoader(std::move(file));
        fileLoader.load(movieDB);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << "File loaded" << std::endl;
}

void App::processSaveFileCmd() {
    std::cout << "Input file name:";
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
    std::cout << "File saved" << std::endl;
}

void App::processSearchByKeyCmd() {
    std::cout << "Input primary key:";
    std::string key;
    std::getline(std::cin, key);
    
    Movie movie;
    bool found = movieDB.findMovieByID(key, movie);
    if (found) {
        movie.vDisplay(std::cout);
    } else {
        std::cout << "Movie not found" << std::endl;
    }
}

void App::processDeleteByKeyCmd() {
    std::cout << "Input primary key:";
    std::string key;
    std::getline(std::cin, key);
    
    Movie movie;
    bool deleted = movieDB.deleteMovieByID(key, movie);
    if (deleted) {
        std::cout << "Movie deleted" << std::endl;
        deletedMovieStack.push(movie);
    } else {
        std::cout << "Movie not found" << std::endl;
    }
}

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
/*
void App::processSearchBySecKeyCmd(){
    
    std::cout << "Input Secondary key:";
    std::string key;
    std::getline(std::cin, key);
    
    Movie movie;
    bool found = movieDB.findMovieByID(key, movie);
    if (found) {
        movie.vDisplay(std::cout);
    } else {
        std::cout << "Movie not found" << std::endl;
    }
}
*/


void App::processDisplayAllKeyCmd(){
   std::vector<Movie> list; 
   list = movieDB.listMovieSortedByTitle();
   for(int i = 0; i < list.size(); i++)
     if(list[i].getTitle() != "none")
        std::cout << list[i];
}


