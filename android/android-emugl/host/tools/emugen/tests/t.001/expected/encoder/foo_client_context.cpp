// Generated Code - DO NOT EDIT !!
// generated by 'emugen'


#include <string.h>
#include "foo_client_context.h"


#include <stdio.h>

int foo_client_context_t::initDispatchByName(void *(*getProc)(const char *, void *userData), void *userData)
{
	fooAlphaFunc = (fooAlphaFunc_client_proc_t) getProc("fooAlphaFunc", userData);
	fooIsBuffer = (fooIsBuffer_client_proc_t) getProc("fooIsBuffer", userData);
	fooUnsupported = (fooUnsupported_client_proc_t) getProc("fooUnsupported", userData);
	fooDoEncoderFlush = (fooDoEncoderFlush_client_proc_t) getProc("fooDoEncoderFlush", userData);
	fooTakeConstVoidPtrConstPtr = (fooTakeConstVoidPtrConstPtr_client_proc_t) getProc("fooTakeConstVoidPtrConstPtr", userData);
	fooSetComplexStruct = (fooSetComplexStruct_client_proc_t) getProc("fooSetComplexStruct", userData);
	fooGetComplexStruct = (fooGetComplexStruct_client_proc_t) getProc("fooGetComplexStruct", userData);
	fooInout = (fooInout_client_proc_t) getProc("fooInout", userData);
	return 0;
}
