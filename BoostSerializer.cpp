#include "BoostSerializer.h"

#include <fstream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/list.hpp>

BoostSerializer::BoostSerializer(const std::string& theFileName):
	fileName(theFileName) {

	}

void BoostSerializer::save(const Task& task) {

}

void BoostSerializer::save(const std::list<Task>& tasks) {
	// create and open a character archive for output
	std::ofstream ofs(fileName.c_str());
	// save data to archive
	{
		boost::archive::text_oarchive oa(ofs);
		// write class instance to archive
		oa << tasks;
		// archive and stream closed when destructors are called
	}	
}

std::list<Task> BoostSerializer::load() {
	std::ifstream ifs(fileName.c_str());
    std::list<Task> taskList;
    if (ifs.good()) {
        boost::archive::text_iarchive ia(ifs);
        ia >> taskList;
    }
    return taskList;
}

