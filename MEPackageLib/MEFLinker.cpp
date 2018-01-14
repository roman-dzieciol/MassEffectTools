#include "stdafx.h"
#include "MEFLinker.h"
#include <iostream>
#include "MEUFunction.h"
#include "MEUStruct.h"


MEFLinker::MEFLinker(MEPackage *Package)
	: Package(Package)
{
}


MEFLinker::~MEFLinker()
{
}


void MEFLinker::LoadScripts(MEArchive& A) {
	for (auto& exportObject : Package->ExportObjects) {
		try
		{
			auto func = dynamic_cast<MEUFunction*>(exportObject.get());
			if (func) {
				std::cout << "Loading script for: " << Package->GetObjectPath(MEObjectIndex::FromExportIndex(exportObject->_TableIndex)) << std::endl;
				LoadScript(A, func);
			}
		}
		catch (const std::exception& e)
		{
			std::cerr << MEFormat("Error reading script index:0x%x", exportObject->_TableIndex) << std::endl;
			std::cerr << "Exception: " << e.what() << std::endl;
		}
	}
}

void MEFLinker::LoadScript(MEArchive& A, MEUFunction* Function) {

	if (Function->ScriptOffset == 0) {
		return;
	}

	A.Seek(Function->ScriptOffset);
	UP_OFFSET_GUARD(object, A, Function->ScriptOffset, Function->ScriptOffset + Function->ScriptSize);
	UP_BYTE_MARKER(object, A, A.Tell(), BI_Object);

	Function->ScriptTokens = Script.ParseUntilEnd(A);
	Function->isScriptLoaded = true;
}


MEUFunction* MEFLinker::GetNativeFunc(MENativeFuncIndex Index) {
	auto result = NativeFunctions.find(Index);
	if (result != NativeFunctions.end()) {
		return result->second;
	}
	throw MEException("Unknown native function index: %d", (dword)Index);
	//return nullptr;
}

void MEFLinker::AddNativeFunc(MENativeFuncIndex Index, MEUFunction* Func) {
	auto result = NativeFunctions.find(Index);
	if (result != NativeFunctions.end()) {
		throw MEException("Native function already added: %d", Index);
	}
	NativeFunctions[Index] = Func;
}