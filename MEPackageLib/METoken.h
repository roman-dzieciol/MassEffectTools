#pragma once

class MEScript;
class MEArchive;

// EX_([A-Za-z0-9]+) = 0x([0-9]+), // (.*)

enum class MEExprToken : byte {
	EX_LocalVariable = 0x00, // "A local variable."
	EX_InstanceVariable = 0x01, // "An object variable."
	EX_DefaultVariable = 0x02, // "Default variable for a concrete object."
	EX_Return = 0x04, // "Return from function."
	EX_Switch = 0x05, // "Switch."
	EX_Jump = 0x06, // "Goto a local address in code."
	EX_JumpIfNot = 0x07, // "Goto if not expression."
	EX_Stop = 0x08, // "Stop executing state code."
	EX_Assert = 0x09, // "Assertion."
	EX_Case = 0x0A, // "Case."
	EX_Nothing = 0x0B, // "No operation."
	EX_LabelTable = 0x0C, // "Table of labels."
	EX_GotoLabel = 0x0D, // "Goto a label."
	EX_EatReturn = 0x0E, // "Ignore a dynamic string."
	EX_Let = 0x0F, // "Assign an arbitrary size value to a variable."
	EX_DynArrayElement = 0x10, // "Dynamic array element.!!"
	EX_New = 0x11, // "New object allocation."
	EX_ClassContext = 0x12, // "Class default metaobject context."
	EX_MetaCast = 0x13, // "Metaclass cast."
	EX_LetBool = 0x14, // "Let boolean variable."
	EX_EndParmValue = 0x15,	// EX_EndParmValue
	EX_EndFunctionParms = 0x16, // "End of function call parameters."
	EX_Self = 0x17, // "Self object."
	EX_Skip = 0x18, // "Skippable expression."
	EX_Context = 0x19, // "Call a function through an object context."
	EX_ArrayElement = 0x1A, // "Array element."
	EX_VirtualFunction = 0x1B, // "A function call with parameters."
	EX_FinalFunction = 0x1C, // "A prebound function call with parameters."
	EX_IntConst = 0x1D, // "Int constant."
	EX_FloatConst = 0x1E, // "Floating point constant."
	EX_StringConst = 0x1F, // "String constant."
	EX_ObjectConst = 0x20, // "An object constant."
	EX_NameConst = 0x21, // "A name constant."
	EX_RotationConst = 0x22, // "A rotation constant."
	EX_VectorConst = 0x23, // "A vector constant."
	EX_ByteConst = 0x24, // "A byte constant."
	EX_IntZero = 0x25, // "Zero."
	EX_IntOne = 0x26, // "One."
	EX_True = 0x27, // "Bool True."
	EX_False = 0x28, // "Bool False."
	EX_NativeParm = 0x29, // "Native function parameter offset."
	EX_NoObject = 0x2A, // "NoObject."
	EX_IntConstByte = 0x2C, // "Int constant that requires 1 byte."
	EX_BoolVariable = 0x2D, // "A bool variable which requires a bitmask."
	EX_DynamicCast = 0x2E, // "Safe dynamic class casting."
	EX_Iterator = 0x2F, // "Begin an iterator operation."
	EX_IteratorPop = 0x30, // "Pop an iterator level."
	EX_IteratorNext = 0x31, // "Go to next iteration."
	EX_StructCmpEq = 0x32, // "Struct binary compare-for-equal."
	EX_StructCmpNe = 0x33, // "Struct binary compare-for-unequal."
	EX_UnicodeStringConst = 0x34, // "Unicode string constant."
	EX_StructMember = 0x35, // ""
	EX_DynArrayLength = 0x36, // "A dynamic array length for setting/getting"
	EX_GlobalFunction = 0x37, // "Call non-state version of a function."
	EX_PrimitiveCast = 0x38, // "A casting operator for primitives which reads the type as the subsequent byte"
	EX_DynArrayInsert = 0x39, // "Inserts into a dynamic array"
	EX_3a = 0x3a,	// EX_3a
	EX_DynArrayRemove = 0x40, // "Removes from a dynamic array"
	EX_DelegateFunction = 0x42, // "Call to a delegate function"
	EX_DelegateProperty = 0x43, // "Delegate expression"
	EX_LetDelegate = 0x44, // "Assignment to a delegate"
	EX_TernaryIf = 0x45, // ""
	EX_46 = 0x46,	// something for enums / numbers ? 
	EX_47 = 0x47,	// archetype / replication related? 
	EX_OutParameter = 0x48, // ""
	EX_OptionalParamDefaults = 0x49, // ""
	EX__SkipOptionalParam = 0x4A,	// 0x4A
	EX_InterfaceToken = 0x51, // "0x51"
	EX_InterfaceStuff = 0x52, // "0x52"
	EX_End = 0x53, // "End of script"
	EX_Extended = 0x60, // Native func
	EX_First = 0x70, // Native func
};
extern std::string StringFromEnum(MEExprToken code);


class METoken
{
public:
	typedef std::unique_ptr<METoken> Ptr;
	METoken();
	~METoken();

	virtual MEExprToken GetCode() = 0;
	virtual std::string GetName();
	virtual std::string GetDescription() = 0;
	virtual void Parse(MEArchive& A, MEScript& S) = 0;
};