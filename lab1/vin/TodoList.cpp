#include "TodoList.h"

#include <fstream>

const std::string TODO_FILE_NAME = "todo.txt";

// Convert string to lowercase, letter by letter
std::string lowercaseString(const std::string &input) {
  std::string output;

  for (char a : input) {
    output.push_back(tolower(a));
  }

  return output;
}

TodoList::TodoList() { loadFromFile(TODO_FILE_NAME); }

TodoList::~TodoList() {
  writeToFile(TODO_FILE_NAME);
  todoItems.clear();
}

void TodoList::add(const std::string &dueDate, const std::string &task) {
  todoItems.push_back(new TodoItem(dueDate, task));
  writeToFile(TODO_FILE_NAME);
}

int TodoList::remove(const std::string &task) {
  for (auto i = 0; i < todoItems.size(); i++) {
    auto todoItem = todoItems.at(i);
    if (todoItem->getTask() == task) {
      todoItems.erase(todoItems.begin() + i);
      writeToFile(TODO_FILE_NAME);
      return 1;
    }
  }
  return 0;
}

void TodoList::printTodoList() {
  for (auto &todoItem : todoItems) {
    std::cout << "- " << todoItem->getTask() << ": due "
              << todoItem->getDueDate() << std::endl;
  }
}

void TodoList::printDaysTasks(const std::string &date) {
  std::cout << "tasks for day: " << date << std::endl;

  for (auto &todoItem : todoItems) {
    // Do lowercase comparison
    if (lowercaseString(todoItem->getDueDate()) != lowercaseString(date)) {
      continue;
    }

    std::cout << "- " << todoItem->getTask() << std::endl;
  }
  std::cout << std::endl;
}

void TodoList::loadFromFile(std::string path) {
  std::ifstream todoFileIn(path);

  if (todoFileIn.fail()) {
    std::cout << "\"todo.txt\" does not exist or is inaccessible. "
                 "Todo list will start empty."
              << std::endl
              << std::endl;
    // Don't exit, the file could just not exist
  }

  std::string line;
  int lineNumber = 0;
  std::string date;
  std::string task;

  while (std::getline(todoFileIn, line)) {
    if (lineNumber % 2 == 0) {
      date = line;
    } else {
      task = line;
      todoItems.push_back(new TodoItem(date, task));
    }

    lineNumber++;
  }

  todoFileIn.close();
}

void TodoList::writeToFile(std::string path) {
  std::ofstream todoFileOut(TODO_FILE_NAME);

  for (auto &todoItem : todoItems) {
    todoFileOut << todoItem->getDueDate() << std::endl
                << todoItem->getTask() << std::endl;
  }

  todoFileOut.close();
}