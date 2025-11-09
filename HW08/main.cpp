#include <iostream>
#include <string>
#include <cstdlib>
#include "Book.h"
#include "Exercise.h"
using namespace std;

int main() {
    Book myBook;

    Exercise& ex1 = myBook.addExercise(8, 3);
    Exercise& ex2 = myBook.addExercise(9, 2);
    Exercise& ex3 = myBook.addExercise(9, 3);
    Exercise& ex4 = myBook.addExercise(10, 1);
    Exercise& ex5 = myBook.addExercise(10, 2);

    ex3.addRequirement(&ex2);
    ex3.addRequirement(&ex1);
    ex4.addRequirement(&ex2);
    ex5.addRequirement(&ex3);

    cout << "Book initialized. You can type the following exercises:\n";
    for (Exercise* ex = myBook.getFirst(); ex != nullptr; ex = ex->getNext()) {
        cout << ex->getChapter() << "." << ex->getNumber() << " ";
    }
    cout << "\n\n";

    cout << "Type exercise numbers to assign or unassign.\n";
    cout << "Example: 9.3 assigns 9.3, -10.2 unassigns 10.2, 0 quits.\n\n";

    myBook.printExercises();

    while (true) {
        cout << "\nEnter exercise number (e.g., 9.3, -10.2, 0 to quit): ";
        string input;
        cin >> input;

        if (input == "0") {
            cout << "Exiting.\n";
            break;
        }

        bool assign = true;
        if (input[0] == '-') {
            assign = false;
            input = input.substr(1);
        }

        size_t dotPos = input.find('.');
        if (dotPos == string::npos) {
            cout << "Invalid format. Use chapter.number (e.g., 9.3).\n";
            continue;
        }

        int chap = stoi(input.substr(0, dotPos));
        int num  = stoi(input.substr(dotPos + 1));

        Exercise* ex = myBook.getExercise(chap, num);
        if (!ex) {
            cout << "Exercise " << chap << "." << num << " not found.\n";
            continue;
        }

        if (assign)
            ex->assign();
        else
            ex->unassign();

        myBook.printExercises();
    }

    return 0;
}
