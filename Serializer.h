#ifndef __SERIALIZER_H
#define __SERIALIZER_H

#include "Task.h"

#include <list>

class Serializer {
	public:
		virtual void save(const Task& task) = 0;
		virtual void save(const std::list<Task>& tasks) = 0;
		virtual std::list<Task> load() = 0;
};

#endif //__SERIALIZER_H

