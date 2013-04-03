#include "Task.h"

#include <iostream>
#include <sstream>
#include <iomanip>

const char* Task::prio[LAST_PRIO] = {"low", "normal", "high"};
const char* Task::stat[LAST_STATUS] = {"new", "in progress", "complete"};


Task::Task() {

}

Task::Task(const std::string& theDescription, Priority thePriority, Status theStatus):
	description(theDescription), priority(thePriority), status(theStatus), idx(0) {

	}

const std::string Task::toString() const {
	std::string colorCode;
	if(priority == HIGH && status != COMPLETE) {
		colorCode = "31m";
	}
	else if(priority == NORMAL && status != COMPLETE) {
		colorCode = "32m";
	}
	else {
		colorCode = "37m";
	}

	std::ostringstream taskString;
	taskString << "\033[0;" << colorCode;
	taskString << std::left << std::setw(15) << stat[status];
	taskString << "\033[0m";
	taskString << "\033[0;" << colorCode;
	taskString << std::left << std::setw(12) << prio[priority];
	taskString << "\033[0m";
	taskString << "\033[0;" << colorCode;
	taskString << std::left << std::setw(100) << description;
	taskString << "\033[0m";
	//std::string sep(3+12+12+100+3, '_');
	//taskString << std::endl << sep;

	return taskString.str();
}

bool Task::operator<(const Task& theTask) const {
	if(status == theTask.status) {
		if(priority == theTask.priority) {
			return description < theTask.description;
		}
		return priority < theTask.priority;
	}
	return status < theTask.status;
}

