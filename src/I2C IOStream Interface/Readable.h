#pragma once
#ifndef _READABLE_H_
#define _READABLE_H_

class Readable
{
	public:
		~Readable() {}
		virtual bool readByte(unsigned char* byte) = 0;
		virtual unsigned char readBytes(unsigned char* buffer, unsigned int length) = 0;
		virtual unsigned char* read() = 0;
		virtual unsigned int read(unsigned char* buffer) = 0;
		virtual unsigned char available() = 0;
};

#endif