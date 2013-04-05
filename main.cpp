#include "Task.h"
#include "TaskManager.h"
#include "BoostSerializer.h"
#include "ConsolePrinter.h"

#include <string>
#include <fstream>
#include <iostream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/program_options.hpp>
#include <boost/foreach.hpp>

using namespace boost;
namespace po = boost::program_options;


int main(int ac, char* av[]) {
	// Declare the supported options.
	po::options_description desc("Allowed options");
	desc.add_options()
		("help,h", "produce help message")
		("add,a", po::value< std::vector<std::string> >()->multitoken(), "add task(s) to list")
		("remove,r", po::value< std::vector<int> >()->multitoken(), "remove task(s) from list")
		("list,l", "list all taks")
		("sort", "sort by status")
        ("clean", "remove completed tasks")
		("complete", po::value< std::vector<int> >()->multitoken(), "mark task(s) as complete")
		("progress", po::value< std::vector<int> >()->multitoken(), "mark task(s) as in progress")
		("high", po::value< std::vector<int> >()->multitoken(), "mark task(s) as high priority")
		("low", po::value< std::vector<int> >()->multitoken(), "mark task(s) as low priority")
		;

	po::variables_map vm;
    try {
    	po::store(po::parse_command_line(ac, av, desc), vm);
    }
    catch (boost::program_options::invalid_command_line_syntax& e) {
        std::cerr << e.what() << std::endl; 
    }
    catch (boost::program_options::unknown_option& e) {
        std::cerr << e.what() << std::endl;
    }
	po::notify(vm);

	if(vm.count("help")) {
		std::cout << desc << std::endl;
		return 1;
	}

	const std::string todoFile("todo");
	TaskManager tm(todoFile, new BoostSerializer(todoFile), new ConsolePrinter());
	if(vm.count("add")) {
		std::vector<std::string> args(vm["add"].as< std::vector<std::string> >());
		BOOST_FOREACH(std::string description, args) {
			Task task(description);
			tm.add(task);
			std::cout << "added task to list -> " << description << std::endl;
		}
	}
	else if(vm.count("remove")) {
		std::vector<int> args = vm["remove"].as< std::vector<int> >();
		tm.remove(args);
	}
	else if(vm.count("complete")) {
		std::vector<int> args = vm["complete"].as< std::vector<int> >();
		tm.changeStatus(args, COMPLETE);
	}
	else if(vm.count("progress")) {
		std::vector<int> args = vm["progress"].as< std::vector<int> >();
		tm.changeStatus(args, IN_PROGRESS);
	}
	else if(vm.count("high")) {
		std::vector<int> args = vm["high"].as< std::vector<int> >();
		tm.changePriority(args, HIGH);
	}
	else if(vm.count("low")) {
		std::vector<int> args = vm["low"].as< std::vector<int> >();
		tm.changePriority(args, LOW);
	}
	else if(vm.count("list")) {
		tm.listAll();
	} 
	else if(vm.count("sort")) {
		tm.showOrderedByStatus();
	} 
    else if(vm.count("clean")) {
        tm.cleanup();
    }
	else {
		std::cout << desc << std::endl;
		return 1;
	}

	return 0;
}

