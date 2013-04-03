#ifndef __CONSOLE_PRINTER_H
#define __CONSOLE_PRINTER_H

#include "Printer.h"

class ConsolePrinter : public Printer {
	public:
		virtual void print(const std::string& content) const;
};

#endif //__CONSOLE_PRINTER_H

