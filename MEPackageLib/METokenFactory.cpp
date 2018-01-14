#include "stdafx.h"
#include "METokenFactory.h"
#include "METokens.h"


METokenFactory::METokenFactory()
{
}


METokenFactory::~METokenFactory()
{
}

std::unique_ptr<METoken> METokenFactory::ConstructByCode(MEExprToken Code) {
	auto result = ConstructorMap.find(Code);
	if (result != ConstructorMap.end()) {
		return result->second();
	}
	else {
		//std::cerr << "ConstructByClassName: Unknown class " << ClassName << std::endl;
	}
	return {};
}

void METokenFactory::RegisterToken(MEExprToken Code, std::function<std::unique_ptr<METoken>()> Constructor) {
	ConstructorMap[Code] = Constructor;
}


void METokenFactory::RegisterAll()
{
	RegisterToken(MEExprToken::EX_LocalVariable, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_LocalVariable>(); });
	RegisterToken(MEExprToken::EX_InstanceVariable, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_InstanceVariable>(); });
	RegisterToken(MEExprToken::EX_DefaultVariable, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_DefaultVariable>(); });
	RegisterToken(MEExprToken::EX_Return, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_Return>(); });
	RegisterToken(MEExprToken::EX_Switch, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_Switch>(); });
	RegisterToken(MEExprToken::EX_Jump, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_Jump>(); });
	RegisterToken(MEExprToken::EX_JumpIfNot, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_JumpIfNot>(); });
	RegisterToken(MEExprToken::EX_Stop, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_Stop>(); });
	RegisterToken(MEExprToken::EX_Assert, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_Assert>(); });
	RegisterToken(MEExprToken::EX_Case, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_Case>(); });
	RegisterToken(MEExprToken::EX_Nothing, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_Nothing>(); });
	RegisterToken(MEExprToken::EX_LabelTable, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_LabelTable>(); });
	RegisterToken(MEExprToken::EX_GotoLabel, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_GotoLabel>(); });
	RegisterToken(MEExprToken::EX_EatReturn, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_EatReturn>(); });
	RegisterToken(MEExprToken::EX_Let, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_Let>(); });
	RegisterToken(MEExprToken::EX_DynArrayElement, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_DynArrayElement>(); });
	RegisterToken(MEExprToken::EX_New, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_New>(); });
	RegisterToken(MEExprToken::EX_ClassContext, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_ClassContext>(); });
	RegisterToken(MEExprToken::EX_MetaCast, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_MetaCast>(); });
	RegisterToken(MEExprToken::EX_LetBool, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_LetBool>(); });
	RegisterToken(MEExprToken::EX_EndParmValue, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_EndParmValue>(); });
	RegisterToken(MEExprToken::EX_EndFunctionParms, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_EndFunctionParms>(); });
	RegisterToken(MEExprToken::EX_Self, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_Self>(); });
	RegisterToken(MEExprToken::EX_Skip, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_Skip>(); });
	RegisterToken(MEExprToken::EX_Context, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_Context>(); });
	RegisterToken(MEExprToken::EX_ArrayElement, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_ArrayElement>(); });
	RegisterToken(MEExprToken::EX_VirtualFunction, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_VirtualFunction>(); });
	RegisterToken(MEExprToken::EX_FinalFunction, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_FinalFunction>(); });
	RegisterToken(MEExprToken::EX_IntConst, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_IntConst>(); });
	RegisterToken(MEExprToken::EX_FloatConst, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_FloatConst>(); });
	RegisterToken(MEExprToken::EX_StringConst, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_StringConst>(); });
	RegisterToken(MEExprToken::EX_ObjectConst, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_ObjectConst>(); });
	RegisterToken(MEExprToken::EX_NameConst, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_NameConst>(); });
	RegisterToken(MEExprToken::EX_RotationConst, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_RotationConst>(); });
	RegisterToken(MEExprToken::EX_VectorConst, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_VectorConst>(); });
	RegisterToken(MEExprToken::EX_ByteConst, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_ByteConst>(); });
	RegisterToken(MEExprToken::EX_IntZero, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_IntZero>(); });
	RegisterToken(MEExprToken::EX_IntOne, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_IntOne>(); });
	RegisterToken(MEExprToken::EX_True, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_True>(); });
	RegisterToken(MEExprToken::EX_False, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_False>(); });
	RegisterToken(MEExprToken::EX_NativeParm, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_NativeParm>(); });
	RegisterToken(MEExprToken::EX_NoObject, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_NoObject>(); });
	RegisterToken(MEExprToken::EX_IntConstByte, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_IntConstByte>(); });
	RegisterToken(MEExprToken::EX_BoolVariable, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_BoolVariable>(); });
	RegisterToken(MEExprToken::EX_DynamicCast, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_DynamicCast>(); });
	RegisterToken(MEExprToken::EX_Iterator, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_Iterator>(); });
	RegisterToken(MEExprToken::EX_IteratorPop, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_IteratorPop>(); });
	RegisterToken(MEExprToken::EX_IteratorNext, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_IteratorNext>(); });
	RegisterToken(MEExprToken::EX_StructCmpEq, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_StructCmpEq>(); });
	RegisterToken(MEExprToken::EX_StructCmpNe, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_StructCmpNe>(); });
	RegisterToken(MEExprToken::EX_UnicodeStringConst, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_UnicodeStringConst>(); });
	RegisterToken(MEExprToken::EX_StructMember, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_StructMember>(); });
	RegisterToken(MEExprToken::EX_DynArrayLength, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_DynArrayLength>(); });
	RegisterToken(MEExprToken::EX_GlobalFunction, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_GlobalFunction>(); });
	RegisterToken(MEExprToken::EX_PrimitiveCast, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_PrimitiveCast>(); });
	RegisterToken(MEExprToken::EX_DynArrayInsert, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_DynArrayInsert>(); });
	RegisterToken(MEExprToken::EX_3a, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_3a>(); });
	RegisterToken(MEExprToken::EX_DynArrayRemove, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_DynArrayRemove>(); });
	RegisterToken(MEExprToken::EX_DelegateFunction, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_DelegateFunction>(); });
	RegisterToken(MEExprToken::EX_DelegateProperty, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_DelegateProperty>(); });
	RegisterToken(MEExprToken::EX_LetDelegate, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_LetDelegate>(); });
	RegisterToken(MEExprToken::EX_TernaryIf, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_TernaryIf>(); });
	RegisterToken(MEExprToken::EX_46, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_46>(); });
	RegisterToken(MEExprToken::EX_47, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_47>(); });
	RegisterToken(MEExprToken::EX_OutParameter, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_OutParameter>(); });
	RegisterToken(MEExprToken::EX_OptionalParamDefaults, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_OptionalParamDefaults>(); });
	RegisterToken(MEExprToken::EX__SkipOptionalParam, []()->std::unique_ptr<METoken> { return std::make_unique<EX__SkipOptionalParam>(); });
	RegisterToken(MEExprToken::EX_InterfaceToken, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_InterfaceToken>(); });
	RegisterToken(MEExprToken::EX_InterfaceStuff, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_InterfaceStuff>(); });
	RegisterToken(MEExprToken::EX_End, []()->std::unique_ptr<METoken> { return std::make_unique<ME_EX_End>(); });
}