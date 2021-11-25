// Specification file for the Movie class
// Written By: A. Student
// Changed By:
// IDE: Xcode

#ifndef MOVIES_H
#define MOVIES_H

#include <string>
#include <iostream>

using MovieID = std::string;

class Movie {
public:
    Movie(const MovieID& id, const std::string& title, const std::string& lang,
          int year, const std::string& director, bool isAdult) : id(id), title(title), lang(lang),
                                 year(year), director(director), isAdult(isAdult) {}
    Movie() = default;

    void setID(const MovieID& id) { this->id = id;}
    void setTitle(const std::string& title) { this->title = title;}
    void setLang(const std::string& lang) { this->lang = lang;}
    void setDirector(const std::string& director) { this->director = director; }
    void setYear(int year) { this->year = year;    }
    void setIsAdult(bool isAdult) { this->isAdult = isAdult; }

    MovieID getID() const { return id; }
    std::string getTitle() const { return title; }
    std::string getLang() const { return lang; }
    std::string getDirector() const { return director; }
    int getYear() const { return year; }
    bool getIsAdult() const { return isAdult; }

    void vDisplay(std::ostream& os) const {
        os << "ID: " << id << std::endl;
        os << "Title: " << title << std::endl;
        os << "Language: " << lang << std::endl;
        os << "Year: " << year << std::endl;
        os << "Director: " << director << std::endl;
        os << "Is Adult: " << isAdult << std::endl;
    }
private:
    MovieID id{""};
    std::string title{"none"};
    std::string lang{"none"};
    int year{};
    std::string director{"none"};
    bool isAdult{false};
};

#endif
