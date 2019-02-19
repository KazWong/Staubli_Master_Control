#include "stdafx.h"

#include "Staubli_Master.h"
#include "Form1.h"
#include <vcclr.h>

using namespace System;
using namespace Staubli_Master;
using namespace std;

FileHandle::FileHandle() {

}

FileHandle::~FileHandle() {

}

char *FileHandle::SysString_StdString(System::String ^Source){
	char *ch;
	pin_ptr<const wchar_t> wch = PtrToStringChars(Source);

	int len = (( Source->Length+1) * 2);

	ch = new char[ len ];

	if (wcstombs( ch, wch, len ) != -1)
		return ch;
	else
		return ERROR;
}

FILE *FileHandle::FileRead(char *file_path) {
	FILE *fp;
	char str[512] = "";
	int total = 0;

	fp = fopen(file_path, "r");

	return fp;
}