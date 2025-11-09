#ifndef EXERCISE_H
#define EXERCISE_H

#include <iostream>
class Book;

class Exercise {
private:
    int chapter;
    int number;
    Exercise* next;
    Book& book;
    static const int MAX_REQS = 16;
    Exercise* requirements[MAX_REQS];
    int num_requirements;
    bool assigned;

public:
    Exercise(Book& b, int chap, int num, Exercise* prev = nullptr);
    Exercise* getNext() const;
    int getChapter() const;
    int getNumber() const;
    Book& getBook() const;
    bool isAssigned() const;
    void addRequirement(Exercise* req);
    void assign();
    void unassign();
    bool dependsOn(const Exercise* other) const;
    void printRequirements() const;
    friend std::ostream& operator<<(std::ostream& out, const Exercise& ex);
};

#endif
