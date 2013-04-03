#ifndef __TASK_MANAGER_H
#define __TASK_MANAGER_H

#include "Task.h"
#include "Serializer.h"
#include "Printer.h"

#include <string>
#include <vector>
#include <list>

class TaskManager {
	public:
		TaskManager(const std::string& theName, Serializer* theSerializer, Printer* thePrinter);

		void listAll();
		void showOrderedByStatus();
		void add(const Task& task) const;
		void remove(const std::vector<int>& taskIndices) const;
		void changeStatus(const std::vector<int>& taskIndices, Status status) const;
		void changePriority(const std::vector<int>& taskIndices, Priority priority) const;
        void cleanup();

	private:
		std::string name;
		Serializer* serializer;
		Printer* printer;
};

#endif //__TASK_MANAGER_H

