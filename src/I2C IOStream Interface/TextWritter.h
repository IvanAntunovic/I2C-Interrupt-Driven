#pragma once
#ifndef _TEXT_WRITER_H_
#define _TEXT_WRITER_H_

#include "Writeable.h"
#include <string.h>

class TextWriter
{
	private: 
		Writeable* writer;

	public:
		TextWriter(Writeable* writer)
		{
			this->writer = writer;
		}
		void write(const char* string)
		{
			this->writer->write((unsigned char*)string, 0, strlen(string));
		}
};

#endif