#include "stdafx.h"
#include "MENativeFunctionTable.h"


MENativeFunctionTable::MENativeFunctionTable()
{
}


MENativeFunctionTable::~MENativeFunctionTable()
{
}


MEUFunction* MENativeFunctionTable::GetNativeFunc(MENativeFuncIndex Index) {
	auto result = NativeFunctions.find(Index);
	if (result != NativeFunctions.end()) {
		return result->second;
	}
	throw MEException("Unknown native function index: %d", (dword)Index);
	//return nullptr;
}

void MENativeFunctionTable::AddNativeFunc(MENativeFuncIndex Index, MEUFunction* Func) {
	auto result = NativeFunctions.find(Index);
	if (result != NativeFunctions.end()) {
		throw MEException("Native function already added: %d", Index);
	}
	NativeFunctions[Index] = Func;
}