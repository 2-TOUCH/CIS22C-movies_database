#pragma once

#include <iostream>
#include <string>

using MovieID = std::string;

class Movie;  // Forward Decleration

// Overloaded << operator
std::ostream& operator<<(std::ostream&, const Movie&);

class Movie {
  public:
    /**
     * Constructors
     */
    Movie(const MovieID& id, const std::string& title, const std::string& lang,
          int year, const std::string& director, bool isAdult)
        : id(id), title(title), lang(lang), year(year), director(director), isAdult(isAdult) {
    }
    Movie() = default;

    /**
     * Setters
     */
    void setID(const MovieID& id) {
        this->id = id;
    }
    void setTitle(const std::string& title) {
        this->title = title;
    }
    void setLang(const std::string& lang) {
        this->lang = lang;
    }
    void setDirector(const std::string& director) {
        this->director = director;
    }
    void setYear(int year) {
        this->year = year;
    }
    void setIsAdult(bool isAdult) {
        this->isAdult = isAdult;
    }
    // Copy Constructor
    Movie(const Movie& mo) {
        id = mo.getID();
        title = mo.getTitle();
        lang = mo.getLang();
        year = mo.getYear();
        director = mo.getDirector();
        isAdult = mo.getIsAdult();
    }
    /**
     * Getters
     */
    MovieID getID() const {
        return id;
    }
    std::string getTitle() const {
        return title;
    }
    std::string getLang() const {
        return lang;
    }
    std::string getDirector() const {
        return director;
    }
    int getYear() const {
        return year;
    }
    bool getIsAdult() const {
        return isAdult;
    }
    bool operator>(const Movie& s1) const {
        return title > s1.title;
    }
    bool operator<(const Movie& s1) const {
        return title < s1.title;
    }
    //    Movie& operator = (const Movie& s1) const { return this = s1;}
    friend std::ostream& operator<<(std::ostream& os, const Movie& s1) {
        os << s1.title << std::endl;
        return os;
    }
    void vDisplay(std::ostream& os) const {
        os << "ID: " << id << std::endl;
        os << "Title: " << title << std::endl;
        os << "Language: " << lang << std::endl;
        os << "Year: " << year << std::endl;
        os << "Director: " << director << std::endl;
        os << "Is Adult: " << isAdult << std::endl;
    }

  private:
    MovieID id{ "" };
    std::string title{ "none" };
    std::string lang{ "none" };
    int year{};
    std::string director{ "none" };
    bool isAdult{ false };
};
