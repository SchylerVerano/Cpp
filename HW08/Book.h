#ifndef BOOK_H
#define BOOK_H

#include "Exercise.h"

class Book {
private:
    Exercise* first_exercise;
    Exercise* last_exercise;

public:
    Book();
    ~Book();
    Book(const Book&) = delete;
    Book& operator=(const Book&) = delete;
    Book(Book&&) = delete;
    Book& operator=(Book&&) = delete;

    Exercise* getFirst() const;
    Exercise& addExercise(int chapter, int number);
    Exercise* getExercise(int chapter, int number) const;
    void printExercises() const;
    void printAllRequirements() const;
};

#endif
