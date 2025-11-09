#include "Book.h"
#include <iostream>

Book::Book() : first_exercise(nullptr), last_exercise(nullptr) {}

Book::~Book() {
    Exercise* current = first_exercise;
    while (current != nullptr) {
        Exercise* next = current->getNext();
        delete current;
        current = next;
    }
}

Exercise* Book::getFirst() const { return first_exercise; }

Exercise& Book::addExercise(int chapter, int number) {
    if (first_exercise == nullptr) {
        first_exercise = new Exercise(*this, chapter, number, nullptr);
        last_exercise = first_exercise;
    } else {
        last_exercise = new Exercise(*this, chapter, number, last_exercise);
    }
    return *last_exercise;
}

Exercise* Book::getExercise(int chapter, int number) const {
    for (Exercise* ex = first_exercise; ex != nullptr; ex = ex->getNext())
        if (ex->getChapter() == chapter && ex->getNumber() == number)
            return ex;
    return nullptr;
}

void Book::printExercises() const {
    int currentChapter = -1;
    for (Exercise* ex = first_exercise; ex != nullptr; ex = ex->getNext()) {
        if (ex->getChapter() != currentChapter) {
            if (currentChapter != -1)
                std::cout << "\n";
            currentChapter = ex->getChapter();
        }
        std::cout << *ex << " ";
    }
    std::cout << "\n";
}

void Book::printAllRequirements() const {
    for (Exercise* ex = first_exercise; ex != nullptr; ex = ex->getNext())
        ex->printRequirements();
}
