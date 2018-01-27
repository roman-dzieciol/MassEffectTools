#include "stdafx.h"
#include "MEScript.h"
#include "METokenFactory.h"
#include "MEFLinker.h"
#include "METokens.h"
#include "MEUFunction.h"
#include "MENativeFunctionTable.h"
#include <iostream>

struct Indenter {
	dword& Indent;
	Indenter(dword& Indent): Indent(Indent) {
		++Indent;
	}
	~Indenter() {
		--Indent;
	}

	std::string Text() const {
		return std::string(Indent, ' ');
	}
};

MEScript::MEScript()
{
	factory.RegisterAll();
}


MEScript::~MEScript()
{
}


std::unique_ptr<METoken> MEScript::ParseCode(byte code, MEArchive& A, MEScriptContext& Context)
{
	auto indenter = Indenter(Context.Depth);
	PrintOffsetInfo(MEFormat("0x%X %s"
		, (dword)code
		, StringFromEnum((MEExprToken)code).c_str()
	), A, Context);
	auto token = factory.ConstructByCode((MEExprToken)code);
	if (token) {
		token->Parse(A, *this, Context);
		return token;
	}
	else {
		throw MEException("Unexpected token %x at %x", (int)code, A.Tell());
	}
}

std::unique_ptr<METoken> MEScript::ParseFunc(MENativeFuncIndex funcCode, MEArchive& A, MEScriptContext& Context)
{
	auto indenter = Indenter(Context.Depth);
	auto ft = A.GetLinker()->FunctionTable;
	auto func = ft->GetNativeFunc(funcCode);
	PrintOffsetInfo(MEFormat("0x%X %s"
		, (dword)funcCode
		, func->GetObjectName().c_str()
	), A, Context);
	std::unique_ptr<METoken> nativeFuncToken = std::make_unique<MENativeFuncToken>(func);
	nativeFuncToken->Parse(A, *this, Context);
	return nativeFuncToken;
}

std::vector<std::unique_ptr<METoken>> MEScript::ParseFuncArgs(MEArchive& A, MEScriptContext& Context)
{
	auto indenter = Indenter(Context.Depth);
	std::vector<std::unique_ptr<METoken>> tokens;
	while (true)
	{
		auto token = ParseToken(A, Context);
		auto code = token->GetCode();
		tokens.push_back(std::move(token));
		if (code == MEExprToken::EX_EndFunctionParms) {
			break;
		}
	}
	return std::move(tokens);
}


std::unique_ptr<METoken> MEScript::ParseToken(MEArchive& A, MEScriptContext& Context)
{
	byte code = 0;
	A << code;
	return ParseToken(code, A, Context);

}

std::unique_ptr<METoken> MEScript::ParseToken(byte code, MEArchive& A, MEScriptContext& Context)
{
	if (code >= (dword)MEExprToken::EX_FirstNative)
	{
		return ParseFunc(code, A, Context);
	}
	else if (code >= (dword)MEExprToken::EX_ExtendedNative)
	{
		byte funcCode2 = 0;
		A << funcCode2;
		return ParseCode(code, A, Context);
	}

	//if (code >= (byte)MEExprToken::EX_FirstNative) {
	//	dword funcCode = code;
	//	if ((funcCode & 0xF0) == (byte)MEExprToken::EX_ExtendedNative) {
	//		byte funcCode2 = 0;
	//		A << funcCode2;
	//		funcCode = ((funcCode - (dword)funcCode2) << 8) + (dword)funcCode2;
	//	}
	//	return ParseFunc(funcCode, A, Context);
	//}
	else {
		return ParseCode(code, A, Context);
	}
}

void MEScript::PrintOffsetInfo(std::string Info, MEArchive& A, MEScriptContext& Context)
{
	ME::Log("%s[%0.4x][%0.2x] %s%s\n"
		, A.GetOffsetText().c_str()
		, A.Tell() - Context.ScriptOffset
		, Context.Depth
		, std::string(Context.Depth, ' ').c_str()
		, Info.c_str()
	);
}

void MEScript::VerifyToken(METoken* Token, MEExprToken Value) {
	if (Token->GetCode() != Value) {
		throw MEException("Unexpected token %d, expected: %d", (dword)Token->GetCode(), (dword)Value);
	}
}

std::vector<std::unique_ptr<METoken>> MEScript::ParseUntilEnd(MEArchive& A, MEScriptContext& Context)
{
	std::vector<std::unique_ptr<METoken>> result;
	byte code = 0;
	A << code;
	while (code != (byte)MEExprToken::EX_EndOfScript) {
		auto token = ParseToken(code, A, Context);
		if (token) {
			result.push_back(std::move(token));
		}
		A << code;
	}

	return result;
}

#if 0

	switch (token)
	{





		case MEExprToken::EX_LabelTable: // 0x0C "Table of labels."
		{
			while (true)
			{
				RB_LOAD_DATA(dword, nidx);

				if (wxString(wxT("None")).IsSameAs(Pkg.GetNameString(nidx)))
					break;

				RB_LOAD_DATA(dword, offset);
				PrintOutput(wxT("%s: //%u "), Pkg.GetNameString(nidx), offset);
			}
			RB_ADD_TOKEN;
			break;
		}


		case MEExprToken::EX_FinalFunction: // 0x1C "A prebound function call with parameters."
		{
			RB_LOAD_DATA(dword, value);
			output = wxString::Format(wxT("%s"), PF_SAFESTR(Pkg.GetObjectName(value)));

			RB_ADD_TOKEN;

			dword thisfunc = FuncIdx;
			if (value != FuncIdx && t->Parent && t->Parent->Id != 0x19)
			{
				output = wxString::Format(wxT("Super(%s)."), PF_SAFESTR(Pkg.GetObjectName(Pkg.GetSuperClass(value)))) + output;
			}

			ParseAndOutputFunction(output);
			break;
		}


		case MEExprToken::EX_IntConst: // 0x1D "Int constant."
		{
			RB_LOAD_DATA(dword, value);

			RB_ADD_TOKEN;
			output = wxString::Format(wxT("%d"), value);
			PrintOutput(output);
			break;
		}


		case MEExprToken::EX_FloatConst: // 0x1E "Floating point constant."
		{
			RB_LOAD_DATA(float, value);
			output = wxString::Format(wxT("%f"), value);
			RB_ADD_TOKEN;
			PrintOutput(output);
			break;
		}


		case MEExprToken::EX_StringConst: // 0x1F "String constant."
		{
			RB_LOAD_DATA(rbASCIIZ, value);
			output = wxString::Format(wxT("\"%s\""), PF_SAFESTR(value));
			RB_ADD_TOKEN;
			PrintOutput(output);
			break;
		}


		case MEExprToken::EX_ObjectConst: // 0x20 "An object constant."
		{
			RB_LOAD_DATA(dword, value);
			output = wxString::Format(wxT("%s'%s'"), PF_SAFESTR(Pkg.GetObjectName(value)), PF_SAFESTR(Pkg.GetObjectPath(value)));
			RB_ADD_TOKEN;
			PrintOutput(output);
			break;
		}


		case MEExprToken::EX_NameConst: // 0x21 "A name constant."
		{
			RB_LOAD_DATA(dword, value);
			//RB_LOAD_DATA(dword,value2);
			output = wxString::Format(wxT("'%s'"), PF_SAFESTR(Pkg.GetNameString(value)));

			RB_ADD_TOKEN;
			PrintOutput(output);
			break;
		}


		case MEExprToken::EX_RotationConst: // 0x22 "A rotation constant."
		{
			RB_LOAD_DATA(dword, value);
			RB_LOAD_DATA(dword, value2);
			RB_LOAD_DATA(dword, value3);
			output = wxString::Format(wxT("rot(%d,%d,%d)"), value, value2, value3);

			RB_ADD_TOKEN;
			PrintOutput(output);
			break;
		}


		case MEExprToken::EX_VectorConst: // 0x23 "A vector constant."
		{
			RB_LOAD_DATA(float, value);
			RB_LOAD_DATA(float, value2);
			RB_LOAD_DATA(float, value3);
			output = wxString::Format(wxT("vect(%f,%f,%f)"), value, value2, value3);

			RB_ADD_TOKEN;
			PrintOutput(output);
			break;
		}


		case MEExprToken::EX_ByteConst: // 0x24 "A byte constant."
		{
			RB_LOAD_DATA(byte, value2);
			output = wxString::Format(wxT("%d"), dword(value2));

			RB_ADD_TOKEN;
			PrintOutput(output);
			break;
		}


		case MEExprToken::EX_IntZero: // 0x25 "Zero."
		{	output = wxString::Format(wxT("0"));
		RB_ADD_TOKEN;
		PrintOutput(output);
		break;
		}


		case MEExprToken::EX_IntOne: // 0x26 "One."
		{	output = wxString::Format(wxT("1"));
		RB_ADD_TOKEN;
		PrintOutput(output);
		break;
		}


		case MEExprToken::EX_True: // 0x27 "Bool True."
		{	output = wxString::Format(wxT("True"));
		RB_ADD_TOKEN;
		PrintOutput(output);
		break;
		}


		case MEExprToken::EX_False: // 0x28 "Bool False."
		{	output = wxString::Format(wxT("False"));
		RB_ADD_TOKEN;
		PrintOutput(output);
		break;
		}


		case MEExprToken::EX_NativeParm: // 0x29 "Native function parameter offset."
		{
			RB_LOAD_DATA(dword, idx);

			output = Pkg.GetObjectName(idx);
			RB_ADD_TOKEN;
			break;
		}


		case MEExprToken::EX_NoObject: // 0x2A "NoObject."
		{	output = wxString::Format(wxT("None"));
		RB_ADD_TOKEN;
		PrintOutput(output);
		break;
		}


		case MEExprToken::EX_IntConstByte: // 0x2C "Int constant that requires 1 byte."
		{
			RB_LOAD_DATA(byte, value);
			output = wxString::Format(wxT("%d"), dword(value));

			RB_ADD_TOKEN;
			PrintOutput(output);
			break;
		}


		case MEExprToken::EX_BoolVariable: // 0x2D "A bool variable which requires a bitmask."
		{	RB_ADD_TOKEN;
		RB_LOAD_TOKEN;
		break;
		}


		case MEExprToken::EX_DynamicCast: // 0x2E "Safe dynamic class casting."
		{
			RB_LOAD_DATA(dword, idx);
			output = wxString::Format(wxT("class<%s>("), PF_SAFESTR(Pkg.GetObjectName(idx)));
			PrintOutput(output);

			RB_ADD_TOKEN;
			RB_LOAD_TOKEN;
			PrintOutput(wxT(")"));
			break;
		}


		case MEExprToken::EX_Iterator: // 0x2F "Begin an iterator operation."
		{	t->SetFlag(TF_SkipPostOutput);

		output = wxT("ForEach ");
		PrintOutput(output);

		RB_ADD_TOKEN;
		RB_LOAD_TOKEN;
		RB_LOAD_DATA(word, offset);

		PopStack();
		bStack = false;

		PrintOutput(wxT("\n"));
		OutputLeftBracket();
		PushBracket(0xFFFF);
		PushIndent();

		for (dword x = 0; x != 0xFF; ++x)
		{
			if (LoadToken() == 0x31)
			{
				break;
			}
		}

		PopIndent();
		PopBracket();
		OutputRightBracket();
		break;
		}


		case MEExprToken::EX_IteratorPop: // 0x30 "Pop an iterator level."
		{	RB_ADD_TOKEN;
		break;
		}


		case MEExprToken::EX_IteratorNext: // 0x31 "Go to next iteration."
		{	RB_ADD_TOKEN;
		break;
		}


		case MEExprToken::EX_StructCmpEq: // 0x32 "Struct binary compare-for-equal."
		{
			RB_LOAD_DATA(dword, idx);

			RB_ADD_TOKEN;
			RB_LOAD_TOKEN;
			PrintOutput(wxT(" == "));
			RB_LOAD_TOKEN;
			break;
			break;
		}


		case MEExprToken::EX_StructCmpNe: // 0x33 "Struct binary compare-for-unequal."
		{
			RB_LOAD_DATA(dword, idx);

			RB_ADD_TOKEN;
			RB_LOAD_TOKEN;
			PrintOutput(wxT(" != "));
			RB_LOAD_TOKEN;
			break;
		}


		case MEExprToken::EX_UnicodeStringConst: // 0x34 "Unicode string constant."
		{
			RB_LOAD_DATA(rbUNICODEZ, value);

			RB_ADD_TOKEN;
			break;
		}

		case MEExprToken::EX_StructMember: // 0x35 ""
		{
			RB_LOAD_DATA(dword, value);
			output = wxString::Format(wxT(".%s"), PF_SAFESTR(Pkg.GetObjectName(value)));

			RB_ADD_TOKEN;
			RB_LOAD_TOKEN;
			PrintOutput(output);
			break;
		}

		case MEExprToken::EX_DynArrayLength: // 0x36 "A dynamic array length for setting/getting"
		{	RB_ADD_TOKEN;
		RB_LOAD_TOKEN;
		PrintOutput(wxT(".Length"));
		break;
		}

		case MEExprToken::EX_GlobalFunction: // 0x37 "Call non-state version of a function."
		{
			//RB_LOAD_DATA(dword,value2);
			RB_LOAD_DATA(dword, value);
			output = wxString::Format(wxT("%s"), PF_SAFESTR(Pkg.GetNameString(value)));

			RB_ADD_TOKEN;
			/*dword thisfunc = FuncIdx;
			if( value != FuncIdx && t->Parent && t->Parent->Id != 0x19 )
			{
			output = wxString::Format( wxT("Super(%s)."), PF_SAFESTR(Pkg.GetObjectName(Pkg.GetSuperClass(value))) ) + output;
			}*/

			ParseAndOutputFunction(output);
			break;
		}


		case MEExprToken::EX_PrimitiveCast: // 0x38 "A casting operator for primitives which reads the type as the subsequent byte"
		{
			RB_LOAD_DATA(byte, value);
			output = wxString::Format(wxT("%s("), PF_SAFESTR(GetCastTokenString(value)));
			PrintOutput(output);

			RB_ADD_TOKEN;
			RB_LOAD_TOKEN;
			PrintOutput(wxT(")"));
			break;
		}


		case MEExprToken::EX_DynArrayInsert: // 0x39 "Inserts into a dynamic array"
		{	RB_ADD_TOKEN;
		RB_LOAD_TOKEN;
		PrintOutput(wxT(".Insert("));
		RB_LOAD_TOKEN;
		PrintOutput(wxT(", "));
		RB_LOAD_TOKEN;
		PrintOutput(wxT(")"));
		break;
		}

		case 0x3a:	// EX_ReturnNothing
		{
			RB_TOKEN_NAME("EX_ReturnNothing");
			RB_TOKEN_DESC("");

			RB_LOAD_DATA(dword, value);

			output = wxString::Format(wxT("EX_ReturnNothing %d %s"), value, PF_SAFESTR(Pkg.GetObjectName(value)));
			PrintOutput(output);
			RB_ADD_TOKEN;
			break;
		}

		case MEExprToken::EX_DynArrayRemove: // 0x40 "Removes from a dynamic array"
		{	RB_ADD_TOKEN;
		RB_LOAD_TOKEN;
		PrintOutput(wxT(".Remove("));
		RB_LOAD_TOKEN;
		PrintOutput(wxT(", "));
		RB_LOAD_TOKEN;
		PrintOutput(wxT(")"));
		break;
		}

		case MEExprToken::EX_DelegateFunction: // 0x42 "Call to a delegate function"
		{	RB_ADD_TOKEN;
		RB_LOAD_TOKEN;
		RB_LOAD_DATA(dword, fname);
		RB_LOAD_DATA(dword, unk);

		output = wxT("EX_DelegateFunction");
		ParseAndOutputFunction(output);
		break;
		}


		case MEExprToken::EX_DelegateProperty: // 0x43 "Delegate expression"
		{	RB_LOAD_DATA(dword, fname);
		//RB_LOAD_DATA(dword,unk);
		output = wxString::Format(wxT("delegate= [%d] %s"), fname, PF_SAFESTR(Pkg.GetNameString(fname)));
		PrintOutput(wxT(")"));
		RB_ADD_TOKEN;
		break;
		}


		case MEExprToken::EX_LetDelegate: // 0x44 "Assignment to a delegate"
		{	RB_ADD_TOKEN;
		RB_LOAD_TOKEN;
		PrintOutput(wxT(" = "));
		RB_LOAD_TOKEN;
		break;
		}

		case MEExprToken::EX_Conditional: // 0x45 ""
		{	output = name;
		RB_ADD_TOKEN;

		RB_LOAD_TOKEN;
		RB_LOAD_DATA(byte, end1);
		RB_LOAD_DATA(byte, end11);
		PrintOutput(wxT(" ? "));

		RB_LOAD_TOKEN;
		RB_LOAD_DATA(byte, end2);
		RB_LOAD_DATA(byte, end21);
		PrintOutput(wxT(" : "));

		RB_LOAD_TOKEN;
		break;
		}


		case 0x46:	// something for enums / numbers ? 
		{
			RB_TOKEN_NAME("EX_0x46");
			RB_TOKEN_DESC("");
			output = name;
			PrintOutput(output);
			RB_ADD_TOKEN;
			RB_LOAD_TOKEN;
			RB_LOAD_TOKEN;
			break;
		}


		case 0x47:	// archetype / replication related? 
		{
			RB_TOKEN_NAME("EX_0x47");
			RB_TOKEN_DESC("");
			output = name;
			PrintOutput(output);
			RB_ADD_TOKEN;
			RB_LOAD_TOKEN; // archetype
			RB_LOAD_TOKEN; // const name
			break;
		}

		case MEExprToken::EX_LocalOutVariable: // 0x48 ""
		{	RB_LOAD_DATA(dword, value);
		output = wxString::Format(wxT("%s"), PF_SAFESTR(Pkg.GetObjectName(value)));
		RB_ADD_TOKEN;
		PrintOutput(output);
		break;
		}

		case MEExprToken::EX_DefaultParmValue: // 0x49 ""
		{	RB_LOAD_DATA(word, value);
		RB_ADD_TOKEN;
		RB_LOAD_TOKEN;
		break;
		}


		case 0x50:	// 0x50
		{
			RB_TOKEN_NAME("0x50"); // EX_SkipOptionalParam ??
			RB_TOKEN_DESC("0x50");
			t->SetFlag(TF_SkipPostOutput);
			RB_ADD_TOKEN;
			break;
		}

		case MEExprToken::EX_InterfaceContext: // 0x51 "0x51"
		{	RB_ADD_TOKEN;
		RB_LOAD_TOKEN;
		break;
		}

		case MEExprToken::EX_InterfaceCast: // 0x52 "0x52"
		{	RB_LOAD_DATA(dword, value);
		output = wxString::Format(wxT("%s"), PF_SAFESTR(Pkg.GetNameString(value)));
		RB_ADD_TOKEN;
		PrintOutput(output);
		break;
		}


		case MEExprToken::EX_EndOfScript: // 0x53 "End of script"
		{	t->SetFlag(TF_SkipPostOutput);
		RB_ADD_TOKEN;
		break;
		}
	}
}

#endif