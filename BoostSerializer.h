#ifndef __BOOST_SERIALIZER_H
#define __BOOST_SERIALIZER_H

#include "Serializer.h"

class BoostSerializer : public Serializer {
	public:
		explicit BoostSerializer(const std::string& theFileName);
		virtual void save(const Task& task);
		virtual void save(const std::list<Task>& tasks);
		virtual std::list<Task> load();

	private:
		std::string fileName;
};

#endif //__BOOST_SERIALIZER_H

