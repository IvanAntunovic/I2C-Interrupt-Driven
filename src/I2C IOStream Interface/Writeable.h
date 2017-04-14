#pragma once
#ifndef _WRITEABLE_H_
#define _WRITEABLE_H_

class Writeable
{
	public:
		~Writeable() {}
		virtual unsigned int write(unsigned char* bytes, unsigned char offset, unsigned char length) = 0;
		virtual unsigned char availableForWrite() = 0;
};

#endif // !_WRITEABLE_H_

