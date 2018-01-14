#include "stdafx.h"
#include "METoken.h"


std::string StringFromEnum(MEExprToken code) {
	switch (code) {
	case MEExprToken::EX_LocalVariable: return "EX_LocalVariable"; // 0x00 A local variable.
	case MEExprToken::EX_InstanceVariable: return "EX_InstanceVariable"; // 0x01 An object variable.
	case MEExprToken::EX_DefaultVariable: return "EX_DefaultVariable"; // 0x02 Default variable for a concrete object.

	case MEExprToken::EX_Return: return "EX_Return"; // 0x04 Return from function.
	case MEExprToken::EX_Switch: return "EX_Switch"; // 0x05 Switch.
	case MEExprToken::EX_Jump: return "EX_Jump"; // 0x06 Goto a local address in code.
	case MEExprToken::EX_JumpIfNot: return "EX_JumpIfNot"; // 0x07 Goto if not expression.
	case MEExprToken::EX_Stop: return "EX_Stop"; // 0x08 Stop executing state code.
	case MEExprToken::EX_Assert: return "EX_Assert"; // 0x09 Assertion.
	case MEExprToken::EX_Case: return "EX_Case"; // 0x0A Case.
	case MEExprToken::EX_Nothing: return "EX_Nothing"; // 0x0B No operation.
	case MEExprToken::EX_LabelTable: return "EX_LabelTable"; // 0x0C Table of labels.
	case MEExprToken::EX_GotoLabel: return "EX_GotoLabel"; // 0x0D Goto a label.
	case MEExprToken::EX_EatReturnValue: return "EX_EatReturnValue"; // 0x0E destroy an unused return value
	case MEExprToken::EX_Let: return "EX_Let"; // 0x0F Assign an arbitrary size value to a variable.
	case MEExprToken::EX_DynArrayElement: return "EX_DynArrayElement"; // 0x10 Dynamic array element.!!
	case MEExprToken::EX_New: return "EX_New"; // 0x11 New object allocation.
	case MEExprToken::EX_ClassContext: return "EX_ClassContext"; // 0x12 Class default metaobject context.
	case MEExprToken::EX_MetaCast: return "EX_MetaCast"; // 0x13 Metaclass cast.
	case MEExprToken::EX_LetBool: return "EX_LetBool"; // 0x14 Let boolean variable.
	case MEExprToken::EX_EndParmValue: return "EX_EndParmValue"; // 0x15 end of default value for optional function parameter
	case MEExprToken::EX_EndFunctionParms: return "EX_EndFunctionParms"; // 0x16 End of function call parameters.
	case MEExprToken::EX_Self: return "EX_Self"; // 0x17 Self object.
	case MEExprToken::EX_Skip: return "EX_Skip"; // 0x18 Skippable expression.
	case MEExprToken::EX_Context: return "EX_Context"; // 0x19 Call a function through an object context.
	case MEExprToken::EX_ArrayElement: return "EX_ArrayElement"; // 0x1A Array element.
	case MEExprToken::EX_VirtualFunction: return "EX_VirtualFunction"; // 0x1B A function call with parameters.
	case MEExprToken::EX_FinalFunction: return "EX_FinalFunction"; // 0x1C A prebound function call with parameters.
	case MEExprToken::EX_IntConst: return "EX_IntConst"; // 0x1D Int constant.
	case MEExprToken::EX_FloatConst: return "EX_FloatConst"; // 0x1E Floating point constant.
	case MEExprToken::EX_StringConst: return "EX_StringConst"; // 0x1F String constant.
	case MEExprToken::EX_ObjectConst: return "EX_ObjectConst"; // 0x20 An object constant.
	case MEExprToken::EX_NameConst: return "EX_NameConst"; // 0x21 A name constant.
	case MEExprToken::EX_RotationConst: return "EX_RotationConst"; // 0x22 A rotation constant.
	case MEExprToken::EX_VectorConst: return "EX_VectorConst"; // 0x23 A vector constant.
	case MEExprToken::EX_ByteConst: return "EX_ByteConst"; // 0x24 A byte constant.
	case MEExprToken::EX_IntZero: return "EX_IntZero"; // 0x25 Zero.
	case MEExprToken::EX_IntOne: return "EX_IntOne"; // 0x26 One.
	case MEExprToken::EX_True: return "EX_True"; // 0x27 Bool True.
	case MEExprToken::EX_False: return "EX_False"; // 0x28 Bool False.
	case MEExprToken::EX_NativeParm: return "EX_NativeParm"; // 0x29 Native function parameter offset.
	case MEExprToken::EX_NoObject: return "EX_NoObject"; // 0x2A NoObject.

	case MEExprToken::EX_IntConstByte: return "EX_IntConstByte"; // 0x2C Int constant that requires 1 byte.
	case MEExprToken::EX_BoolVariable: return "EX_BoolVariable"; // 0x2D A bool variable which requires a bitmask.
	case MEExprToken::EX_DynamicCast: return "EX_DynamicCast"; // 0x2E Safe dynamic class casting.
	case MEExprToken::EX_Iterator: return "EX_Iterator"; // 0x2F Begin an iterator operation.
	case MEExprToken::EX_IteratorPop: return "EX_IteratorPop"; // 0x30 Pop an iterator level.
	case MEExprToken::EX_IteratorNext: return "EX_IteratorNext"; // 0x31 Go to next iteration.
	case MEExprToken::EX_StructCmpEq: return "EX_StructCmpEq"; // 0x32 Struct binary compare-for-equal.
	case MEExprToken::EX_StructCmpNe: return "EX_StructCmpNe"; // 0x33 Struct binary compare-for-unequal.
	case MEExprToken::EX_UnicodeStringConst: return "EX_UnicodeStringConst"; // 0x34 Unicode string constant.
	case MEExprToken::EX_StructMember: return "EX_StructMember"; // 0x35 Struct member.
	case MEExprToken::EX_DynArrayLength: return "EX_DynArrayLength"; // 0x36 A dynamic array length for setting/getting
	case MEExprToken::EX_GlobalFunction: return "EX_GlobalFunction"; // 0x37 Call non-state version of a function.
	case MEExprToken::EX_PrimitiveCast: return "EX_PrimitiveCast"; // 0x38 A casting operator for primitives which reads the type as the subsequent byte
	case MEExprToken::EX_DynArrayInsert: return "EX_DynArrayInsert"; // 0x39 Inserts into a dynamic array
	case MEExprToken::EX_ReturnNothing: return "EX_ReturnNothing"; // 0x3A failsafe for functions that return a value - returns the zero value for a property and logs that control reached the end of a non-void function
	case MEExprToken::EX_EqualEqual_DelDel: return "EX_EqualEqual_DelDel"; // 0x3B delegate comparison for equality
	case MEExprToken::EX_NotEqual_DelDel: return "EX_NotEqual_DelDel"; // 0x3C delegate comparison for inequality
	case MEExprToken::EX_EqualEqual_DelFunc: return "EX_EqualEqual_DelFunc"; // 0x3D delegate comparison for equality against a function
	case MEExprToken::EX_NotEqual_DelFunc: return "EX_NotEqual_DelFunc"; // 0x3E delegate comparison for inequality against a function
	case MEExprToken::EX_EmptyDelegate: return "EX_EmptyDelegate"; // 0x3F delegate 'None'
	case MEExprToken::EX_DynArrayRemove: return "EX_DynArrayRemove"; // 0x40 Removes from a dynamic array
	case MEExprToken::EX_DebugInfo: return "EX_DebugInfo"; // 0x41 DEBUGGER Debug information
	case MEExprToken::EX_DelegateFunction: return "EX_DelegateFunction"; // 0x42 Call to a delegate function
	case MEExprToken::EX_DelegateProperty: return "EX_DelegateProperty"; // 0x43 Delegate expression
	case MEExprToken::EX_LetDelegate: return "EX_LetDelegate"; // 0x44 Assignment to a delegate
	case MEExprToken::EX_Conditional: return "EX_Conditional"; // 0x45 tertiary operator support
	case MEExprToken::EX_DynArrayFind: return "EX_DynArrayFind"; // 0x46 dynarray search for item index
	case MEExprToken::EX_DynArrayFindStruct: return "EX_DynArrayFindStruct"; // 0x47 dynarray<struct> search for item index
	case MEExprToken::EX_LocalOutVariable: return "EX_LocalOutVariable"; // 0x48 local out (pass by reference) function parameter
	case MEExprToken::EX_DefaultParmValue: return "EX_DefaultParmValue"; // 0x49 default value of optional function parameter
	case MEExprToken::EX_EmptyParmValue: return "EX_EmptyParmValue"; // 0x4A unspecified value for optional function parameter
	case MEExprToken::EX_InstanceDelegate: return "EX_InstanceDelegate"; // 0x4B const reference to a delegate or normal function object

	case MEExprToken::EX_InterfaceContext: return "EX_InterfaceContext"; // 0x51 Call a function through a native interface variable
	case MEExprToken::EX_InterfaceCast: return "EX_InterfaceCast"; // 0x52 Converting an object reference to native interface variable
	case MEExprToken::EX_EndOfScript: return "EX_EndOfScript"; // 0x53 Last byte in script code
	case MEExprToken::EX_DynArrayAdd: return "EX_DynArrayAdd"; // 0x54 Add to a dynamic array
	case MEExprToken::EX_DynArrayAddItem: return "EX_DynArrayAddItem"; // 0x55 Add an item to a dynamic array
	case MEExprToken::EX_DynArrayRemoveItem: return "EX_DynArrayRemoveItem"; // 0x56 Remove an item from a dynamic array
	case MEExprToken::EX_DynArrayInsertItem: return "EX_DynArrayInsertItem"; // 0x57 Insert an item into a dynamic array
	case MEExprToken::EX_DynArrayIterator: return "EX_DynArrayIterator"; // 0x58 Iterate through a dynamic array
	case MEExprToken::EX_DynArraySort: return "EX_DynArraySort"; // 0x59 Sort a list in place

	case MEExprToken::EX_ExtendedNative: return "EX_ExtendedNative"; // 0x60
	case MEExprToken::EX_FirstNative: return "EX_FirstNative"; // 0x70

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
