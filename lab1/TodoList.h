#ifndef CS235_LABS_LAB1_TODOLIST_H_
#define CS235_LABS_LAB1_TODOLIST_H_
#include <iostream>
#include <string>
#include <vector>

#include "TodoItem.h"
#include "TodoListInterface.h"

class TodoList : public TodoListInterface {
 public:
  // Clang recommendation: "use '= default' to define a trivial default
  // constructor"
  TodoList();
  ~TodoList() override;

  void add(const std::string &dueDate, const std::string &task) override;

  int remove(const std::string &task) override;

  void printTodoList() override;

  void printDaysTasks(const std::string &date) override;

  void loadFromFile();

  void writeToFile();

 private:
  std::vector<TodoItem*> todoItems;
};
#endif  // CS235_LABS_LAB1_TODOLIST_H_