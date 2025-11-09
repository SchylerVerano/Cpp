#include "Exercise.h"
#include "Book.h"
#include <iostream>
#include <cstdlib>

Exercise::Exercise(Book& b, int chap, int num, Exercise* prev)
    : chapter(chap), number(num), next(nullptr), book(b),
      num_requirements(0), assigned(false)
{
    if (prev != nullptr)
        prev->next = this;
    for (int i = 0; i < MAX_REQS; ++i)
        requirements[i] = nullptr;
}

Exercise* Exercise::getNext() const { return next; }
int Exercise::getChapter() const { return chapter; }
int Exercise::getNumber() const { return number; }
Book& Exercise::getBook() const { return book; }
bool Exercise::isAssigned() const { return assigned; }

void Exercise::addRequirement(Exercise* req) {
    if (num_requirements < MAX_REQS)
        requirements[num_requirements++] = req;
}

void Exercise::assign() {
    if (assigned) return;
    assigned = true;
    for (int i = 0; i < num_requirements; ++i)
        if (requirements[i] != nullptr)
            requirements[i]->assign();
}

void Exercise::unassign() {
    if (!assigned) return;
    assigned = false;
    for (Exercise* ex = book.getFirst(); ex != nullptr; ex = ex->getNext())
        if (ex->dependsOn(this))
            ex->unassign();
}

bool Exercise::dependsOn(const Exercise* other) const {
    for (int i = 0; i < num_requirements; ++i)
        if (requirements[i] == other)
            return true;
    return false;
}

void Exercise::printRequirements() const {
    std::cout << *this << " requires: ";
    if (num_requirements == 0)
        std::cout << "none";
    else {
        for (int i = 0; i < num_requirements; ++i) {
            std::cout << *requirements[i];
            if (i < num_requirements - 1)
                std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

std::ostream& operator<<(std::ostream& out, const Exercise& ex) {
    if (ex.assigned)
        out << ex.chapter << "." << ex.number;
    else
        out << "*.*";
    return out;
}
