#ifndef __PRINTER_H
#define __PRINTER_H

#include <string>

class Printer {
	public:
		virtual void print(const std::string& content) const = 0;
};

#endif //__PRINTER_H

