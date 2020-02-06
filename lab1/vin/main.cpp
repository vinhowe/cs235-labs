#include <iostream>
#include <string>

#include "TodoList.h"
using namespace std;

int main(int argc, char *argv[]) {
  TodoList *todo = new TodoList();
  if (argc > 1) {
    string command = argv[1];
    if (command == "add") {
      // cout << "Going to add something" << endl;
      if (argc > 3) {
        string duedate = argv[2];
        string task = argv[3];
        todo->add(duedate, task);
      } else {
        cout << "Too few parameters for add" << endl;
      }
    } else if (command ==
               "remove") {  // cout << "Going to remove something" << endl;

      if (argc > 2) {
        string task = argv[2];
        todo->remove(task);

      } else {
        cout << "Too few parameters for remove" << endl;
      }
    } else if (command == "printList") {  // cout << "Going to print the whole
                                          // list" << endl;
      todo->printTodoList();

    } else if (command ==
               "printDay") {  // cout << "Going to print a day" << endl;
      if (argc > 2) {
        string date = argv[2];
        todo->printDaysTasks(date);
      } else {
        cout << "Too few parameters for printDay" << endl;
      }

    } else {
      cout << "Unknown command" << endl;
    }

  } else {
    cout << "Too few arguments" << endl;
  }
  delete todo;
  return 0;
}

