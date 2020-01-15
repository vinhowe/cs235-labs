//
// Created by vin on 1/11/20.
//

#ifndef CS235_LABS_LAB1_TODOITEM_H_
#define CS235_LABS_LAB1_TODOITEM_H_

#include <string>

class TodoItem {
 public:
  TodoItem(std::string dueDate, std::string task);
  // Notice that I don't provide setters--An individual instance of a data
  // object should be immutable
  std::string getDueDate();
  std::string getTask();
 private:
  std::string dueDate;
  std::string task;
};

#endif //CS235_LABS_LAB1_TODOITEM_H_
