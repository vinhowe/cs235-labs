//
// Created by vin on 1/11/20.
//

#include "TodoItem.h"

#include <utility>

TodoItem::TodoItem(std::string dueDate, std::string task)
    : dueDate(std::move(dueDate)), task(std::move(task)) {}

std::string TodoItem::getDueDate() { return dueDate; }

std::string TodoItem::getTask() { return task; }
