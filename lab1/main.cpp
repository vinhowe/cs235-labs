#include <iostream>

#include "TodoList.h"

// (not) using namespace std;
// https://stackoverflow.com/questions/1452721/why-is-using-namespace-std-considered-bad-practice

struct Usage {
  std::string command;
  std::string usage;
};

const std::vector<Usage> USAGE_MAP = {
    {"add", "[date] [task]"},
    {"remove", "[task]"},
    // Never gets called, but I should do some kind of error checking here
    {"printList"},
    {"printDay", "[day]"}};

void printUsageMessage(const std::string &command, const std::string &usage = "") {
  std::cout << command;
  // Clang suggests using std::str.empty() instead of str == ""
  if (!usage.empty()) {
    std::cout << " " << usage;
  }

  std::cout << std::endl;
}

void printHelpMessage() {
  std::cout << "TODO by VIN" << std::endl << std::endl;
  std::cout << "Options:" << std::endl;
  for (const auto &usage : USAGE_MAP) {
    std::cout << "  ";
    printUsageMessage(usage.command, usage.usage);
  }
}

void printCommandUsage(const std::string &programName,
                       const std::string &command) {
  for (const auto &usage : USAGE_MAP) {
    if (usage.command == command) {
      // Doesn't end with a newline because we want it on the same line as the
      // usage output
      std::cout << "USAGE: " + programName + " ";
      printUsageMessage(usage.command, usage.usage);
      return;
    }
  }
}

int main(int argc, char *argv[]) {
  auto *todoList = new TodoList();

  if (argc <= 1) {
    printHelpMessage();
    return 1;
  }

  const std::string programName = argv[0];
  const std::string command = argv[1];

  if (command == "add") {
    if (argc < 4) {
      printCommandUsage(programName, command);
      return 1;
    }

    std::string date = argv[2];
    std::string task = argv[3];

    todoList->add(date, task);

    std::cout << "Added task \"" << task << "\" scheduled for " << date
              << std::endl;
  } else if (command == "remove") {
    if (argc < 2) {
      printCommandUsage(programName, command);
      return 1;
    }

    std::string task = argv[2];
    todoList->remove(task);
  } else if (command == "printList") {
    todoList->printTodoList();
  } else if (command == "printDay") {
    if (argc < 3) {
      printCommandUsage(programName, command);
      return 1;
    }

    std::string date = argv[2];
    todoList->printDaysTasks(date);
  } else {
    std::cout << "Not a valid argument" << std::endl << std::endl;
    printHelpMessage();
  }

  // Make sure to free memory. Wouldn't have thought of this without looking at
  // Dr. Dahl's main.cpp
  delete todoList;
}
