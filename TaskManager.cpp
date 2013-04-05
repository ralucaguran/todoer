#include "TaskManager.h"
#include "Task.h"

#include <iostream>
#include <iomanip>
#include <algorithm>

#include <boost/foreach.hpp>

TaskManager::TaskManager(const std::string& theName, Serializer* theSerializer, Printer* thePrinter):
	name(theName), serializer(theSerializer), printer(thePrinter) {
	}

void TaskManager::listAll() {
	std::list<Task> tasks = serializer->load();
	int idx = 0;
	BOOST_FOREACH(Task task, tasks) {
		std::cout << std::right << std::setw(3) << '[' << ++idx << ']';
		printer->print(task.toString());
	}
}

void TaskManager::showOrderedByStatus() {
	std::list<Task> tasks = serializer->load();
	tasks.sort();
	BOOST_FOREACH(Task task, tasks) {
		printer->print(task.toString());
	}
}

void TaskManager::add(const Task& task) const {
	std::list<Task> taskList = serializer->load();
	std::list<Task>::iterator iter = std::find(taskList.begin(), taskList.end(), task);
	if(iter == taskList.end()) {
		taskList.push_back(task);
		serializer->save(taskList);
	}
	else {
		std::cout << "Task " << task.getDescription() << " already exists!" << std::endl;
	}
}

void TaskManager::remove(const std::vector<int>& taskIndices) const {
	std::list<Task> taskList = serializer->load();
	std::vector<std::list<Task>::iterator> viter;
	BOOST_FOREACH(int idx, taskIndices) {
		if(idx > 0 && idx <= taskList.size()) {
			std::list<Task>::iterator iter = taskList.begin();
			advance(iter, idx - 1);
			viter.push_back(iter);
			std::cout << "Task " << idx << " -> " << iter->getDescription() << " removed from list." << std::endl;
		}
		else {
			std::cout << "Task " << idx << " cannot be removed because it doesn't exist." << std::endl;
		}
	}
	BOOST_FOREACH(std::list<Task>::iterator iter, viter) {
		taskList.erase(iter);
	}
	serializer->save(taskList);
}

void TaskManager::changeStatus(const std::vector<int>& taskIndices, Status status) const {
	std::list<Task> taskList = serializer->load();
	BOOST_FOREACH(int idx, taskIndices) {
		if(idx > 0 && idx <= taskList.size()) {
			std::list<Task>::iterator iter = taskList.begin();
			advance(iter, idx - 1);
			iter->setStatus(status);
			std::cout << "Task " << idx << " marked as " << Task::stat[status] << '.' << std::endl;
		}
		else {
			std::cout << "Task " << idx << " cannot be changed as because it doesn't exist." << std::endl;
		}
	}
	serializer->save(taskList);
}

void TaskManager::changePriority(const std::vector<int>& taskIndices, Priority priority) const {
	std::list<Task> taskList = serializer->load();
	BOOST_FOREACH(int idx, taskIndices) {
		if(idx > 0 && idx <= taskList.size()) {
			std::list<Task>::iterator iter = taskList.begin();
			advance(iter, idx - 1);
			iter->setPriority(priority);
			std::cout << "Task " << idx << " marked as " << Task::prio[priority] << " priority." << std::endl;
		}
		else {
			std::cout << "Task " << idx << " cannot be changed because it doesn't exist." << std::endl;
		}
	}
	serializer->save(taskList);
}

void TaskManager::cleanup() {
    std::list<Task> taskList = serializer->load();
    taskList.remove_if([] (const Task& t) { return t.getStatus() == COMPLETE; });
    serializer->save(taskList);
}

