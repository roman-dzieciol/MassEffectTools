#pragma once

class MEScript;
class MEArchive;
class MEScriptContext;

// EX_([A-Za-z0-9]+) = 0x([0-9]+), // (.*)

enum class MEExprToken : word {
	// Variable references.
	EX_LocalVariable = 0x00, // A local variable.
	EX_InstanceVariable = 0x01, // An object variable.
	EX_DefaultVariable = 0x02, // Default variable for a concrete object.
	
	// Tokens.
	EX_Return = 0x04, // Return from function.
	EX_Switch = 0x05, // Switch.
	EX_Jump = 0x06, // Goto a local address in code.
	EX_JumpIfNot = 0x07, // Goto if not expression.
	EX_Stop = 0x08, // Stop executing state code.
	EX_Assert = 0x09, // Assertion.
	EX_Case = 0x0A, // Case.
	EX_Nothing = 0x0B, // No operation.
	EX_LabelTable = 0x0C, // Table of labels.
	EX_GotoLabel = 0x0D, // Goto a label.
	EX_EatReturnValue = 0x0E, // destroy an unused return value
	EX_Let = 0x0F, // Assign an arbitrary size value to a variable.
	EX_DynArrayElement = 0x10, // Dynamic array element.!!
	EX_New = 0x11, // New object allocation.
	EX_ClassContext = 0x12, // Class default metaobject context.
	EX_MetaCast = 0x13, // Metaclass cast.
	EX_LetBool = 0x14, // Let boolean variable.
	EX_EndParmValue = 0x15, // end of default value for optional function parameter
	EX_EndFunctionParms = 0x16, // End of function call parameters.
	EX_Self = 0x17, // Self object.
	EX_Skip = 0x18, // Skippable expression.
	EX_Context = 0x19, // Call a function through an object context.
	EX_ArrayElement = 0x1A, // Array element.
	EX_VirtualFunction = 0x1B, // A function call with parameters.
	EX_FinalFunction = 0x1C, // A prebound function call with parameters.
	EX_IntConst = 0x1D, // Int constant.
	EX_FloatConst = 0x1E, // Floating point constant.
	EX_StringConst = 0x1F, // String constant.
	EX_ObjectConst = 0x20, // An object constant.
	EX_NameConst = 0x21, // A name constant.
	EX_RotationConst = 0x22, // A rotation constant.
	EX_VectorConst = 0x23, // A vector constant.
	EX_ByteConst = 0x24, // A byte constant.
	EX_IntZero = 0x25, // Zero.
	EX_IntOne = 0x26, // One.
	EX_True = 0x27, // Bool True.
	EX_False = 0x28, // Bool False.
	EX_NativeParm = 0x29, // Native function parameter offset.
	EX_NoObject = 0x2A, // NoObject.
	
	EX_IntConstByte = 0x2C, // Int constant that requires 1 byte.
	EX_BoolVariable = 0x2D, // A bool variable which requires a bitmask.
	EX_DynamicCast = 0x2E, // Safe dynamic class casting.
	EX_Iterator = 0x2F, // Begin an iterator operation.
	EX_IteratorPop = 0x30, // Pop an iterator level.
	EX_IteratorNext = 0x31, // Go to next iteration.
	EX_StructCmpEq = 0x32, // Struct binary compare-for-equal.
	EX_StructCmpNe = 0x33, // Struct binary compare-for-unequal.
	EX_UnicodeStringConst = 0x34, // Unicode string constant.
	EX_StructMember = 0x35, // Struct member.
	EX_DynArrayLength = 0x36, // A dynamic array length for setting/getting
	EX_GlobalFunction = 0x37, // Call non-state version of a function.
	EX_PrimitiveCast = 0x38, // A casting operator for primitives which reads the type as the subsequent byte
	EX_DynArrayInsert = 0x39, // Inserts into a dynamic array
	EX_ReturnNothing = 0x3A, // failsafe for functions that return a value - returns the zero value for a property and logs that control reached the end of a non-void function
	EX_EqualEqual_DelDel = 0x3B, // delegate comparison for equality
	EX_NotEqual_DelDel = 0x3C, // delegate comparison for inequality
	EX_EqualEqual_DelFunc = 0x3D, // delegate comparison for equality against a function
	EX_NotEqual_DelFunc = 0x3E, // delegate comparison for inequality against a function
	EX_EmptyDelegate = 0x3F, // delegate 'None'
	EX_DynArrayRemove = 0x40, // Removes from a dynamic array
	EX_DebugInfo = 0x41, //DEBUGGER Debug information
	EX_DelegateFunction = 0x42, // Call to a delegate function
	EX_DelegateProperty = 0x43, // Delegate expression
	EX_LetDelegate = 0x44, // Assignment to a delegate
	EX_Conditional = 0x45, // tertiary operator support
	EX_DynArrayFind = 0x46, // dynarray search for item index
	EX_DynArrayFindStruct = 0x47, // dynarray<struct> search for item index
	EX_LocalOutVariable = 0x48, // local out (pass by reference) function parameter
	EX_DefaultParmValue = 0x49, // default value of optional function parameter
	EX_EmptyParmValue = 0x4A, // unspecified value for optional function parameter
	EX_InstanceDelegate = 0x4B, // const reference to a delegate or normal function object
	
	EX_InterfaceContext = 0x51, // Call a function through a native interface variable
	EX_InterfaceCast = 0x52, // Converting an object reference to native interface variable
	EX_EndOfScript = 0x53, // Last byte in script code
	EX_DynArrayAdd = 0x54, // Add to a dynamic array
	EX_DynArrayAddItem = 0x55, // Add an item to a dynamic array
	EX_DynArrayRemoveItem = 0x56, // Remove an item from a dynamic array
	EX_DynArrayInsertItem = 0x57, // Insert an item into a dynamic array
	EX_DynArrayIterator = 0x58, // Iterate through a dynamic array
	EX_DynArraySort = 0x59, // Sort a list in place
	
	// Natives.
	EX_ExtendedNative = 0x60,
	EX_FirstNative = 0x70,
	EX_Max = 0x1000,

	EX_HighNative_60 = 0x60, // Native func
	EX_HighNative_61 = 0x61, // Native func
	EX_HighNative_62 = 0x62, // Native func
	EX_HighNative_63 = 0x63, // Native func
	EX_HighNative_64 = 0x64, // Native func
	EX_HighNative_65 = 0x65, // Native func
	EX_HighNative_66 = 0x66, // Native func
	EX_HighNative_67 = 0x67, // Native func
	EX_HighNative_68 = 0x68, // Native func
	EX_HighNative_69 = 0x69, // Native func
	EX_HighNative_6a = 0x6a, // Native func
	EX_HighNative_6b = 0x6b, // Native func
	EX_HighNative_6c = 0x6c, // Native func
	EX_HighNative_6d = 0x6d, // Native func
	EX_HighNative_6e = 0x6e, // Native func
	EX_HighNative_6f = 0x6f, // Native func
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
	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) = 0;
};