#include "stdafx.h"
#include "METoken.h"


std::string StringFromEnum(MEExprToken code) {
	switch (code) {
	case MEExprToken::EX_LocalVariable: return "EX_LocalVariable";
	case MEExprToken::EX_InstanceVariable: return "EX_InstanceVariable";
	case MEExprToken::EX_DefaultVariable: return "EX_DefaultVariable";
	case MEExprToken::EX_Return: return "EX_Return";
	case MEExprToken::EX_Switch: return "EX_Switch";
	case MEExprToken::EX_Jump: return "EX_Jump";
	case MEExprToken::EX_JumpIfNot: return "EX_JumpIfNot";
	case MEExprToken::EX_Stop: return "EX_Stop";
	case MEExprToken::EX_Assert: return "EX_Assert";
	case MEExprToken::EX_Case: return "EX_Case";
	case MEExprToken::EX_Nothing: return "EX_Nothing";
	case MEExprToken::EX_LabelTable: return "EX_LabelTable";
	case MEExprToken::EX_GotoLabel: return "EX_GotoLabel";
	case MEExprToken::EX_EatReturn: return "EX_EatReturn";
	case MEExprToken::EX_Let: return "EX_Let";
	case MEExprToken::EX_DynArrayElement: return "EX_DynArrayElement";
	case MEExprToken::EX_New: return "EX_New";
	case MEExprToken::EX_ClassContext: return "EX_ClassContext";
	case MEExprToken::EX_MetaCast: return "EX_MetaCast";
	case MEExprToken::EX_LetBool: return "EX_LetBool";
	case MEExprToken::EX_EndParmValue: return "EX_EndParmValue";
	case MEExprToken::EX_EndFunctionParms: return "EX_EndFunctionParms";
	case MEExprToken::EX_Self: return "EX_Self";
	case MEExprToken::EX_Skip: return "EX_Skip";
	case MEExprToken::EX_Context: return "EX_Context";
	case MEExprToken::EX_ArrayElement: return "EX_ArrayElement";
	case MEExprToken::EX_VirtualFunction: return "EX_VirtualFunction";
	case MEExprToken::EX_FinalFunction: return "EX_FinalFunction";
	case MEExprToken::EX_IntConst: return "EX_IntConst";
	case MEExprToken::EX_FloatConst: return "EX_FloatConst";
	case MEExprToken::EX_StringConst: return "EX_StringConst";
	case MEExprToken::EX_ObjectConst: return "EX_ObjectConst";
	case MEExprToken::EX_NameConst: return "EX_NameConst";
	case MEExprToken::EX_RotationConst: return "EX_RotationConst";
	case MEExprToken::EX_VectorConst: return "EX_VectorConst";
	case MEExprToken::EX_ByteConst: return "EX_ByteConst";
	case MEExprToken::EX_IntZero: return "EX_IntZero";
	case MEExprToken::EX_IntOne: return "EX_IntOne";
	case MEExprToken::EX_True: return "EX_True";
	case MEExprToken::EX_False: return "EX_False";
	case MEExprToken::EX_NativeParm: return "EX_NativeParm";
	case MEExprToken::EX_NoObject: return "EX_NoObject";
	case MEExprToken::EX_IntConstByte: return "EX_IntConstByte";
	case MEExprToken::EX_BoolVariable: return "EX_BoolVariable";
	case MEExprToken::EX_DynamicCast: return "EX_DynamicCast";
	case MEExprToken::EX_Iterator: return "EX_Iterator";
	case MEExprToken::EX_IteratorPop: return "EX_IteratorPop";
	case MEExprToken::EX_IteratorNext: return "EX_IteratorNext";
	case MEExprToken::EX_StructCmpEq: return "EX_StructCmpEq";
	case MEExprToken::EX_StructCmpNe: return "EX_StructCmpNe";
	case MEExprToken::EX_UnicodeStringConst: return "EX_UnicodeStringConst";
	case MEExprToken::EX_StructMember: return "EX_StructMember";
	case MEExprToken::EX_DynArrayLength: return "EX_DynArrayLength";
	case MEExprToken::EX_GlobalFunction: return "EX_GlobalFunction";
	case MEExprToken::EX_PrimitiveCast: return "EX_PrimitiveCast";
	case MEExprToken::EX_DynArrayInsert: return "EX_DynArrayInsert";
	case MEExprToken::EX_3a: return "EX_3a";
	case MEExprToken::EX_DynArrayRemove: return "EX_DynArrayRemove";
	case MEExprToken::EX_DelegateFunction: return "EX_DelegateFunction";
	case MEExprToken::EX_DelegateProperty: return "EX_DelegateProperty";
	case MEExprToken::EX_LetDelegate: return "EX_LetDelegate";
	case MEExprToken::EX_TernaryIf: return "EX_TernaryIf";
	case MEExprToken::EX_46: return "EX_46";
	case MEExprToken::EX_47: return "EX_47";
	case MEExprToken::EX_OutParameter: return "EX_OutParameter";
	case MEExprToken::EX_OptionalParamDefaults: return "EX_OptionalParamDefaults";
	case MEExprToken::EX__SkipOptionalParam: return "EX__SkipOptionalParam";
	case MEExprToken::EX_InterfaceToken: return "EX_InterfaceToken";
	case MEExprToken::EX_InterfaceStuff: return "EX_InterfaceStuff";
	case MEExprToken::EX_End: return "EX_End";
	case MEExprToken::EX_Extended: return "EX_Extended";
	case MEExprToken::EX_First: return "EX_First";
	default: return MEFormat("0x%X", (dword)code);
	}
}


METoken::METoken()
{
}


METoken::~METoken()
{
}

std::string METoken::GetName()
{
	return StringFromEnum(GetCode());
}
