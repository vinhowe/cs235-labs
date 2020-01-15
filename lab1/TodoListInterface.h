#ifndef CS235_LABS_LAB1_TODOLISTINTERFACE_H_
#define CS235_LABS_LAB1_TODOLISTINTERFACE_H_
#include <iostream>
#include <string>

class TodoListInterface {
 public:
  // Clang recommendation: "use '= default' to define a trivial default constructor"
  TodoListInterface() = default;
  virtual ~ TodoListInterface() = default;

  // Adds an item to the todo list with the data specified by the string "_duedate" and the task specified by "_task"
  virtual void add(const std::string &dueDate, const std::string &task) = 0;

  // Removes an item from the todo list with the specified task name
  // Returns 1 if it removes an item, 0 otherwise
  virtual int remove(const std::string &task) = 0;

  // Prints out the full todo list to the console
  virtual void printTodoList() = 0;

  // Prints out all items of a todo list with a particular due date (specified by _duedate)
  virtual void printDaysTasks(const std::string &date) = 0;
};

#endif // CS235_LABS__TODOLISTINTERFACE_H_