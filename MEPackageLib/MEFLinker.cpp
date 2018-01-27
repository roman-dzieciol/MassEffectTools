#include "stdafx.h"
#include "MEFLinker.h"
#include <iostream>
#include "MEUFunction.h"
#include "MEUStruct.h"
#include "MEScript.h"


MEFLinker::MEFLinker(MEPackage *Package, MENativeFunctionTable* FunctionTable)
	: Package(Package), FunctionTable(FunctionTable)
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
				auto const msg = MEFormat("Loading script for: %s", Package->GetObjectPath(MEObjectIndex::FromExportIndex(exportObject->_TableIndex)).c_str());
				std::cout << msg << std::endl;
				ME::Log("%s\n", msg.c_str());
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

	MEScriptContext Context;
	Context.ScriptOffset = Function->ScriptOffset;
	Context.ScriptSize = Function->ScriptSize;
	Function->ScriptTokens = Script.ParseUntilEnd(A, Context);
	Function->isScriptLoaded = true;
}
