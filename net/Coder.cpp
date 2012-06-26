#include "Coder.h"

static const size_t EncodeBufferSize = 1024 * 1024;
static string s_encodeBuffer;

DataBuffer Coder::encode(Message* msg)
{
	if (s_encodeBuffer.capacity() <= EncodeBufferSize)
		s_encodeBuffer.reserve(EncodeBufferSize);

	s_encodeBuffer = "";
	if (msg->SerializeToString(&s_encodeBuffer))
		return DataBuffer(s_encodeBuffer.c_str(), s_encodeBuffer.size(), true) ;
	
	return DataBuffer();
}
