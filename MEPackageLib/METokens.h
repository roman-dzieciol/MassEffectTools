#pragma once

#include "MEScript.h"
#include "METoken.h"
#include <iostream>

class MEUFunction;

// class ME_EX_$1: public METoken { \npublic:\n    static constexpr const MEExprToken Code = MEExprToken::EX_$1; // 0x$2\n    virtual std::string GetDescription() override { static const std::string desc = $3;\n\n    ME_EX_$1(){}\n\n    virtual void Parse(MEArchive& A, MEScript& S) override {//__debugbreak();\n\n    }\n}; return desc; }

class ME_EX_LocalVariable : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_LocalVariable; } // 0x00
	virtual std::string GetDescription() override { static const std::string desc = "A local variable."; return desc; }

	MEObjectIndex PropertyIndex;

	ME_EX_LocalVariable() {}

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {

		A << PropertyIndex;
	}
};

class ME_EX_InstanceVariable : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_InstanceVariable; } // 0x01
	virtual std::string GetDescription() override { static const std::string desc = "An object variable."; return desc; }

	MEObjectIndex Object;

	ME_EX_InstanceVariable() {}

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();
		A << Object;
	}
};

class ME_EX_DefaultVariable : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_DefaultVariable; } // 0x02
	virtual std::string GetDescription() override { static const std::string desc = "Default variable for a concrete object."; return desc; }

	MEObjectIndex Object;

	ME_EX_DefaultVariable() {}

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();
		A << Object;
	}
};

class ME_EX_Return : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_Return; } // 0x04
	virtual std::string GetDescription() override { static const std::string desc = "Return from function."; return desc; }

	std::unique_ptr<METoken> Expression;

	ME_EX_Return() {}

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
		Expression = S.ParseToken(A, Context);
	}
};

class ME_EX_Switch : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_Switch; } // 0x05
	virtual std::string GetDescription() override { static const std::string desc = "Switch."; return desc; }

	MEObjectIndex PropertySize;
	byte PropertyType;
	std::unique_ptr<METoken> Expression;

	ME_EX_Switch() {}

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();
		A << PropertySize;
		A << PropertyType;
		Expression = S.ParseToken(A, Context);
	}
};

class ME_EX_Jump : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_Jump; } // 0x06
	virtual std::string GetDescription() override { static const std::string desc = "Goto a local address in code."; return desc; }

	word Offset;

	ME_EX_Jump() {}

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {////__debugbreak();
		A << Offset;
		S.PrintOffsetInfo(MEFormat(" (Offset 0x%0.8x)", Offset), A, Context);
	}
};

class ME_EX_JumpIfNot : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_JumpIfNot; } // 0x07
	virtual std::string GetDescription() override { static const std::string desc = "Goto if not expression."; return desc; }

	word Offset;
	std::unique_ptr<METoken> Expression;

	ME_EX_JumpIfNot() {}

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override { //__debugbreak();
		A << Offset;
		S.PrintOffsetInfo(MEFormat(" (Offset 0x%0.8x)", Offset), A, Context);
		Expression = S.ParseToken(A, Context);
	}
};

class ME_EX_Stop : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_Stop; } // 0x08
	virtual std::string GetDescription() override { static const std::string desc = "Stop executing state code."; return desc; }

	ME_EX_Stop() {}

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();

	}
};

class ME_EX_Assert : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_Assert; } // 0x09
	virtual std::string GetDescription() override { static const std::string desc = "Assertion."; return desc; }

	word LineNumber;
	byte DebugMode;
	std::unique_ptr<METoken> Expression;

	ME_EX_Assert() {}

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();
		A << LineNumber;
		A << DebugMode;
		Expression = S.ParseToken(A, Context);
	}
};

class ME_EX_Case : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_Case; } // 0x0A
	virtual std::string GetDescription() override { static const std::string desc = "Case."; return desc; }
	static constexpr const word DefaultCase = 0xFFFF;

	word Offset;
	std::unique_ptr<METoken> Expression;

	ME_EX_Case() {}

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();
		A << Offset;
		if (Offset != DefaultCase) {
			Expression = S.ParseToken(A, Context);
		}
	}
};

class ME_EX_Nothing : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_Nothing; } // 0x0B
	virtual std::string GetDescription() override { static const std::string desc = "No operation."; return desc; }

	ME_EX_Nothing() {}

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override { //__debugbreak();

	}
};

class ME_EX_LabelTable : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_LabelTable; } // 0x0C
	virtual std::string GetDescription() override { static const std::string desc = "Table of labels."; return desc; }

	word Index;

	ME_EX_LabelTable() {}

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();
		throw MENotImplemented();
	}
};

class ME_EX_GotoLabel : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_GotoLabel; } // 0x0D
	virtual std::string GetDescription() override { static const std::string desc = "Goto a label."; return desc; }

	std::unique_ptr<METoken> Expression;

	ME_EX_GotoLabel() {}

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();
		Expression = S.ParseToken(A, Context);
	}
};

class ME_EX_EatReturnValue : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_EatReturnValue; } // 0x0E
	virtual std::string GetDescription() override { static const std::string desc = "Call function returning a string, then discard the result."; return desc; }

	MEObjectIndex PropertyIndex;

	ME_EX_EatReturnValue() {}

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
		//debugbreak();
		A << PropertyIndex;
	}
};

class ME_EX_Let : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_Let; } // 0x0F
	virtual std::string GetDescription() override { static const std::string desc = "Assign an arbitrary size value to a variable."; return desc; }

	std::unique_ptr<METoken> LHS;
	std::unique_ptr<METoken> RHS;

	ME_EX_Let() {}

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
		LHS = S.ParseToken(A, Context);
		RHS = S.ParseToken(A, Context);
	}
};

class ME_EX_DynArrayElement : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_DynArrayElement; } // 0x10
	virtual std::string GetDescription() override { static const std::string desc = "Dynamic array element.!!"; return desc; }

	std::unique_ptr<METoken> Key;
	std::unique_ptr<METoken> Value;

	ME_EX_DynArrayElement() {}

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override { //__debugbreak();
		Key = S.ParseToken(A, Context);
		Value = S.ParseToken(A, Context);

	}
};

class ME_EX_New : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_New; } // 0x11
	virtual std::string GetDescription() override { static const std::string desc = "New object allocation."; return desc; }

	std::unique_ptr<METoken> ParentExpression;
	std::unique_ptr<METoken> NameExpression;
	std::unique_ptr<METoken> FlagsExpression;
	std::unique_ptr<METoken> ClassExpression;

	ME_EX_New() {}

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();

		ParentExpression = S.ParseToken(A, Context);
		NameExpression = S.ParseToken(A, Context);
		FlagsExpression = S.ParseToken(A, Context);
		ClassExpression = S.ParseToken(A, Context);
	}
};

class ME_EX_ClassContext : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_ClassContext; } // 0x12
	virtual std::string GetDescription() override { static const std::string desc = "Class default metaobject context."; return desc; }

	ME_EX_ClassContext() {}

	std::unique_ptr<METoken> ObjectExpression;
	word Offset; // Code offset for NULL expressions
				 // UField index?
	byte PropertyType;
	std::unique_ptr<METoken> ContextExpression;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();

		ObjectExpression = S.ParseToken(A, Context);
		A << Offset;
		//
		A << PropertyType;
		ContextExpression = S.ParseToken(A, Context);
	}
};

class ME_EX_MetaCast : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_MetaCast; } // 0x13
	virtual std::string GetDescription() override { static const std::string desc = "Metaclass cast."; return desc; }

	MEObjectIndex ClassIndex;
	std::unique_ptr<METoken> Expression;

	ME_EX_MetaCast() {}

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();

		A << ClassIndex;
		Expression = S.ParseToken(A, Context);
	}
};

class ME_EX_LetBool : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_LetBool; } // 0x14
	virtual std::string GetDescription() override { static const std::string desc = "Let boolean variable."; return desc; }

	std::unique_ptr<METoken> LHS;
	std::unique_ptr<METoken> RHS;

	ME_EX_LetBool() {}

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override { //__debugbreak();
		LHS = S.ParseToken(A, Context);
		RHS = S.ParseToken(A, Context);
	}
};

class ME_EX_EndParmValue : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_EndParmValue; } // 0x15
	virtual std::string GetDescription() override { static const std::string desc = "EX_EndParmValue"; return desc; }

	ME_EX_EndParmValue() {}

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	}
};

class ME_EX_EndFunctionParms : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_EndFunctionParms; } // 0x16
	virtual std::string GetDescription() override { static const std::string desc = "End of function call parameters."; return desc; }

	ME_EX_EndFunctionParms() {}

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {

	}
};

class ME_EX_Self : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_Self; } // 0x17
	virtual std::string GetDescription() override { static const std::string desc = "Self object."; return desc; }

	ME_EX_Self() {}

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();

	}
};

class ME_EX_Skip : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_Skip; } // 0x18
	virtual std::string GetDescription() override { static const std::string desc = "Skippable expression."; return desc; }

	ME_EX_Skip() {}

	word SkipSize;
	std::unique_ptr<METoken> ExpressionToSkip;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override { //__debugbreak();
		A << SkipSize;
		ExpressionToSkip = S.ParseToken(A, Context);
	}
};

class ME_EX_Context : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_Context; } // 0x19
	virtual std::string GetDescription() override { static const std::string desc = "Call a function through an object context."; return desc; }

	ME_EX_Context() {}

	std::unique_ptr<METoken> ObjectExpression;
	word Offset; // Code offset for NULL expressions
				 // UField index?
	byte PropertyType;
	std::unique_ptr<METoken> ContextExpression;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();

		ObjectExpression = S.ParseToken(A, Context);
		A << Offset;
		//
		A << PropertyType;
		ContextExpression = S.ParseToken(A, Context);
	}
};

class ME_EX_ArrayElement : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_ArrayElement; } // 0x1A
	virtual std::string GetDescription() override { static const std::string desc = "Array element."; return desc; }

	ME_EX_ArrayElement() {}

	std::unique_ptr<METoken> Key;
	std::unique_ptr<METoken> Value;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();

		Key = S.ParseToken(A, Context);
		Value = S.ParseToken(A, Context);
	}
};

class ME_EX_VirtualFunction : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_VirtualFunction; } // 0x1B
	virtual std::string GetDescription() override { static const std::string desc = "A function call with parameters."; return desc; }

	ME_EX_VirtualFunction() {}

	MEFName FunctionName;
	std::vector<std::unique_ptr<METoken>> Args;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();

		A << FunctionName;
		Args = S.ParseFuncArgs(A, Context);
	}
};

class ME_EX_FinalFunction : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_FinalFunction; } // 0x1C
	virtual std::string GetDescription() override { static const std::string desc = "A prebound function call with parameters."; return desc; }

	ME_EX_FinalFunction() {}

	MEObjectIndex FunctionExportIndex;
	std::vector<std::unique_ptr<METoken>> Args;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override { //__debugbreak();

		A << FunctionExportIndex;
		Args = S.ParseFuncArgs(A, Context);
	}
};

class ME_EX_IntConst : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_IntConst; } // 0x1D
	virtual std::string GetDescription() override { static const std::string desc = "Int constant."; return desc; }

	ME_EX_IntConst() {}
	dword Value;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override { //__debugbreak();

		A << Value;
	}
};

class ME_EX_FloatConst : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_FloatConst; } // 0x1E
	virtual std::string GetDescription() override { static const std::string desc = "Floating point constant."; return desc; }

	ME_EX_FloatConst() {}
	float Value;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
		//__debugbreak();

		A << Value;
	}
};

class ME_EX_StringConst : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_StringConst; } // 0x1F
	virtual std::string GetDescription() override { static const std::string desc = "String constant."; return desc; }

	ME_EX_StringConst() {}
	MEASCIIZ Value;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override { //__debugbreak();

		A << Value;
	}
};

class ME_EX_ObjectConst : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_ObjectConst; } // 0x20
	virtual std::string GetDescription() override { static const std::string desc = "An object constant."; return desc; }

	ME_EX_ObjectConst() {}
	MEObjectIndex Value;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
		//__debugbreak();

		A << Value;
	}
};

class ME_EX_NameConst : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_NameConst; } // 0x21
	virtual std::string GetDescription() override { static const std::string desc = "A name constant."; return desc; }

	ME_EX_NameConst() {}
	dword Value;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
		//__debugbreak();

		A << Value;
	}
};

class ME_EX_RotationConst : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_RotationConst; } // 0x22
	virtual std::string GetDescription() override { static const std::string desc = "A rotation constant."; return desc; }

	ME_EX_RotationConst() {}
	dword Value1;
	dword Value2;
	dword Value3;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
		//__debugbreak();

		A << Value1;
		A << Value2;
		A << Value3;
	}
};

class ME_EX_VectorConst : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_VectorConst; } // 0x23
	virtual std::string GetDescription() override { static const std::string desc = "A vector constant."; return desc; }

	ME_EX_VectorConst() {}
	dword Value1;
	dword Value2;
	dword Value3;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
		//__debugbreak();

		A << Value1;
		A << Value2;
		A << Value3;
	}
};

class ME_EX_ByteConst : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_ByteConst; } // 0x24
	virtual std::string GetDescription() override { static const std::string desc = "A byte constant."; return desc; }

	ME_EX_ByteConst() {}
	byte Value;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
		//__debugbreak();

		A << Value;
	}
};

class ME_EX_IntZero : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_IntZero; } // 0x25
	virtual std::string GetDescription() override { static const std::string desc = "Zero."; return desc; }

	ME_EX_IntZero() {}

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {////__debugbreak();

	}
};

class ME_EX_IntOne : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_IntOne; } // 0x26
	virtual std::string GetDescription() override { static const std::string desc = "One."; return desc; }

	ME_EX_IntOne() {}

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override { //__debugbreak();

	}
};

class ME_EX_True : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_True; } // 0x27
	virtual std::string GetDescription() override { static const std::string desc = "Bool True."; return desc; }

	ME_EX_True() {}

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {////__debugbreak();

	}
};

class ME_EX_False : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_False; } // 0x28
	virtual std::string GetDescription() override { static const std::string desc = "Bool False."; return desc; }

	ME_EX_False() {}

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {////__debugbreak();

	}
};

class ME_EX_NativeParm : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_NativeParm; } // 0x29
	virtual std::string GetDescription() override { static const std::string desc = "Native function parameter offset."; return desc; }

	ME_EX_NativeParm() {}
	MEObjectIndex PropertyIndex;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override { //__debugbreak();

		A << PropertyIndex;
	}
};

class ME_EX_NoObject : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_NoObject; } // 0x2A
	virtual std::string GetDescription() override { static const std::string desc = "NoObject."; return desc; }

	ME_EX_NoObject() {}

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();

	}
};

class ME_EX_IntConstByte : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_IntConstByte; } // 0x2C
	virtual std::string GetDescription() override { static const std::string desc = "Int constant that requires 1 byte."; return desc; }

	ME_EX_IntConstByte() {}
	byte Value;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();

		A << Value;
	}
};

class ME_EX_BoolVariable : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_BoolVariable; } // 0x2D
	virtual std::string GetDescription() override { static const std::string desc = "A bool variable which requires a bitmask."; return desc; }

	ME_EX_BoolVariable() {}
	std::unique_ptr<METoken> Token;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override { //__debugbreak();

		Token = S.ParseToken(A, Context);
	}
};

class ME_EX_DynamicCast : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_DynamicCast; } // 0x2E
	virtual std::string GetDescription() override { static const std::string desc = "Safe dynamic class casting."; return desc; }

	ME_EX_DynamicCast() {}
	MEObjectIndex Object;
	std::unique_ptr<METoken> Token;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();
		A << Object;
		Token = S.ParseToken(A, Context);
	}
};

class ME_EX_Iterator : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_Iterator; } // 0x2F
	virtual std::string GetDescription() override { static const std::string desc = "Begin an iterator operation."; return desc; }

	ME_EX_Iterator() {}
	std::unique_ptr<METoken> Expression;
	word Offset;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();
		Expression = S.ParseToken(A, Context);
		A << Offset;
	}
};

class ME_EX_IteratorPop : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_IteratorPop; } // 0x30
	virtual std::string GetDescription() override { static const std::string desc = "Pop an iterator level."; return desc; }

	ME_EX_IteratorPop() {}

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();

	}
};

class ME_EX_IteratorNext : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_IteratorNext; } // 0x31
	virtual std::string GetDescription() override { static const std::string desc = "Go to next iteration."; return desc; }

	ME_EX_IteratorNext() {}

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();

	}
};

class ME_EX_StructCmpEq : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_StructCmpEq; } // 0x32
	virtual std::string GetDescription() override { static const std::string desc = "Struct binary compare-for-equal."; return desc; }

	ME_EX_StructCmpEq() {}
	MEObjectIndex StructIndex;
	std::unique_ptr<METoken> LHS;
	std::unique_ptr<METoken> RHS;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();
		A << StructIndex;
		LHS = S.ParseToken(A, Context);
		RHS = S.ParseToken(A, Context);
	}
};

class ME_EX_StructCmpNe : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_StructCmpNe; } // 0x33
	virtual std::string GetDescription() override { static const std::string desc = "Struct binary compare-for-unequal."; return desc; }

	ME_EX_StructCmpNe() {}
	MEObjectIndex StructIndex;
	std::unique_ptr<METoken> LHS;
	std::unique_ptr<METoken> RHS;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();
		A << StructIndex;
		LHS = S.ParseToken(A, Context);
		RHS = S.ParseToken(A, Context);
	}
};

class ME_EX_UnicodeStringConst : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_UnicodeStringConst; } // 0x34
	virtual std::string GetDescription() override { static const std::string desc = "Unicode string constant."; return desc; }

	ME_EX_UnicodeStringConst() {}
	MEUNICODEZ Value;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();
		A << Value;
	}
};

class ME_EX_StructMember : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_StructMember; } // 0x35
	virtual std::string GetDescription() override { static const std::string desc = ""; return desc; }

	ME_EX_StructMember() {}
	MEObjectIndex MemberIndex;
	MEObjectIndex TypeIndex;
	byte bCreatesLocal;
	byte bModifies;
	std::unique_ptr<METoken> MemberExpression;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
		//__debugbreak();
		A << MemberIndex;
		A << TypeIndex;
		A << bCreatesLocal;
		A << bModifies;
		MemberExpression = S.ParseToken(A, Context);
	}
};

class ME_EX_DynArrayLength : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_DynArrayLength; } // 0x36
	virtual std::string GetDescription() override { static const std::string desc = "A dynamic array length for setting/getting"; return desc; }

	ME_EX_DynArrayLength() {}
	std::unique_ptr<METoken> Expression;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override { //__debugbreak();
		Expression = S.ParseToken(A, Context);
	}
};

class ME_EX_GlobalFunction : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_GlobalFunction; } // 0x37
	virtual std::string GetDescription() override { static const std::string desc = "Call non-state version of a function."; return desc; }

	ME_EX_GlobalFunction() {}

	MEFName FunctionName;
	std::vector<std::unique_ptr<METoken>> Args;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();

		A << FunctionName;
		Args = S.ParseFuncArgs(A, Context);
	}
};

class ME_EX_PrimitiveCast : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_PrimitiveCast; } // 0x38
	virtual std::string GetDescription() override { static const std::string desc = "A casting operator for primitives which reads the type as the subsequent byte"; return desc; }

	ME_EX_PrimitiveCast() {}
	byte CastType;
	std::unique_ptr<METoken> Expression;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override { //__debugbreak();
		A << CastType;
		Expression = S.ParseToken(A, Context);
	}
};

class ME_EX_DynArrayInsert : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_DynArrayInsert; } // 0x39
	virtual std::string GetDescription() override { static const std::string desc = "Inserts into a dynamic array"; return desc; }

	ME_EX_DynArrayInsert() {}
	std::unique_ptr<METoken> Expression;
	std::unique_ptr<METoken> Index;
	std::unique_ptr<METoken> Count;
	std::unique_ptr<METoken> End;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();
		Expression = S.ParseToken(A, Context);
		Index = S.ParseToken(A, Context);
		End = S.ParseToken(A, Context);
		S.VerifyToken(End.get(), MEExprToken::EX_EndFunctionParms);
	}
};

class ME_EX_ReturnNothing : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_ReturnNothing; } // 0x3a
	virtual std::string GetDescription() override { static const std::string desc = ""; return desc; }

	ME_EX_ReturnNothing() {}
	MEObjectIndex PropertyIndex;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override { //__debugbreak();
		A << PropertyIndex;
	}
};

class ME_EX_EqualEqual_DelDel : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_EqualEqual_DelDel; } // 0x3b
	virtual std::string GetDescription() override { static const std::string desc = "Used for ReturnValue"; return desc; }

	ME_EX_EqualEqual_DelDel() {}
	std::vector<std::unique_ptr<METoken>> Args;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();

		Args = S.ParseFuncArgs(A, Context);
	}
};

class ME_EX_NotEqual_DelDel : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_NotEqual_DelDel; } // 0x3c
	virtual std::string GetDescription() override { static const std::string desc = ""; return desc; }

	ME_EX_NotEqual_DelDel() {}
	std::vector<std::unique_ptr<METoken>> Args;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();

		Args = S.ParseFuncArgs(A, Context);
	}
};

class ME_EX_EqualEqual_DelFunc : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_EqualEqual_DelFunc; } // 0x3d
	virtual std::string GetDescription() override { static const std::string desc = ""; return desc; }

	ME_EX_EqualEqual_DelFunc() {}
	std::vector<std::unique_ptr<METoken>> Args;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();

		Args = S.ParseFuncArgs(A, Context);
	}
};

class ME_EX_NotEqual_DelFunc : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_NotEqual_DelFunc; } // 0x3e
	virtual std::string GetDescription() override { static const std::string desc = ""; return desc; }

	ME_EX_NotEqual_DelFunc() {}
	std::vector<std::unique_ptr<METoken>> Args;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();

		Args = S.ParseFuncArgs(A, Context);
	}
};

class ME_EX_EmptyDelegate : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_EmptyDelegate; } // 0x3f
	virtual std::string GetDescription() override { static const std::string desc = ""; return desc; }

	ME_EX_EmptyDelegate() {}

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override { //__debugbreak();

	}
};

class ME_EX_DynArrayRemove : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_DynArrayRemove; } // 0x40
	virtual std::string GetDescription() override { static const std::string desc = "Removes from a dynamic array"; return desc; }

	ME_EX_DynArrayRemove() {}
	std::unique_ptr<METoken> Expression;
	std::unique_ptr<METoken> Index;
	std::unique_ptr<METoken> Count;
	std::unique_ptr<METoken> End;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();
		Expression = S.ParseToken(A, Context);
		Index = S.ParseToken(A, Context);
		End = S.ParseToken(A, Context);
		S.VerifyToken(End.get(), MEExprToken::EX_EndFunctionParms);
	}
};

class ME_EX_DebugInfo : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_DebugInfo; } // 0x41
	virtual std::string GetDescription() override { static const std::string desc = ""; return desc; }

	ME_EX_DebugInfo() {}
	dword Version;
	dword LineNumber;
	dword CharacterPos;
	byte OpCode;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override { //__debugbreak();
		
		A << Version;
		A << LineNumber;
		A << CharacterPos;
		A << OpCode;
	}
};

class ME_EX_DelegateFunction : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_DelegateFunction; } // 0x42
	virtual std::string GetDescription() override { static const std::string desc = "Call to a delegate function"; return desc; }

	ME_EX_DelegateFunction() {}
	byte LocalProperty;
	MEObjectIndex DelegateProperty;
	MEObjectIndex DelegateFunctionName;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();
		A << LocalProperty;
		A << DelegateProperty;
		A << DelegateFunctionName;
	}
};

class ME_EX_DelegateProperty : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_DelegateProperty; } // 0x43
	virtual std::string GetDescription() override { static const std::string desc = "Delegate expression"; return desc; }

	ME_EX_DelegateProperty() {}
	MEObjectIndex FunctionName;
	MEObjectIndex DelegateProperty;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();
		A << FunctionName;
		A << DelegateProperty;
	}
};

class ME_EX_LetDelegate : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_LetDelegate; } // 0x44
	virtual std::string GetDescription() override { static const std::string desc = "Assignment to a delegate"; return desc; }

	ME_EX_LetDelegate() {}
	std::unique_ptr<METoken> LHS;
	std::unique_ptr<METoken> RHS;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();
		LHS = S.ParseToken(A, Context);
		RHS = S.ParseToken(A, Context);
	}
};

class ME_EX_Conditional : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_Conditional; } // 0x45
	virtual std::string GetDescription() override { static const std::string desc = ""; return desc; }

	ME_EX_Conditional() {}
	std::unique_ptr<METoken> BoolExpression;
	word Offset1;
	std::unique_ptr<METoken> ResultExpression1;
	word Offset2;
	std::unique_ptr<METoken> ResultExpression2;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();
		BoolExpression = S.ParseToken(A, Context);
		A << Offset1;
		ResultExpression1 = S.ParseToken(A, Context);
		A << Offset2;
		ResultExpression2 = S.ParseToken(A, Context);
	}
};

class ME_EX_DynArrayFind : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_DynArrayFind; } // 0x46
	virtual std::string GetDescription() override { static const std::string desc = "something for enums / numbers ? "; return desc; }

	ME_EX_DynArrayFind() {}
	std::unique_ptr<METoken> ArrayPropertyExpression;
	word Offset;
	std::unique_ptr<METoken> SearchItemExpression;
	std::unique_ptr<METoken> End;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();
		ArrayPropertyExpression = S.ParseToken(A, Context);
		A << Offset;
		SearchItemExpression = S.ParseToken(A, Context);
		End = S.ParseToken(A, Context);
		S.VerifyToken(End.get(), MEExprToken::EX_EndFunctionParms);
	}
};

class ME_EX_DynArrayFindStruct : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_DynArrayFindStruct; } // 0x47
	virtual std::string GetDescription() override { static const std::string desc = "archetype / replication related? "; return desc; }

	ME_EX_DynArrayFindStruct() {}
	std::unique_ptr<METoken> ArrayPropertyExpression;
	word Offset;
	std::unique_ptr<METoken> PropertyNameExpression;
	std::unique_ptr<METoken> SearchItemExpression;
	std::unique_ptr<METoken> End;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();
		ArrayPropertyExpression = S.ParseToken(A, Context);
		A << Offset;
		PropertyNameExpression = S.ParseToken(A, Context);
		SearchItemExpression = S.ParseToken(A, Context);
		End = S.ParseToken(A, Context);
		S.VerifyToken(End.get(), MEExprToken::EX_EndFunctionParms);
	}
};

class ME_EX_LocalOutVariable : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_LocalOutVariable; } // 0x48
	virtual std::string GetDescription() override { static const std::string desc = ""; return desc; }

	ME_EX_LocalOutVariable() {}
	MEObjectIndex PropertyIndex;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override { //__debugbreak();
		A << PropertyIndex;
	}
};

class ME_EX_DefaultParmValue : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_DefaultParmValue; } // 0x49
	virtual std::string GetDescription() override { static const std::string desc = ""; return desc; }

	ME_EX_DefaultParmValue() {}
	word Offset;
	std::unique_ptr<METoken> Expression;
	std::unique_ptr<METoken> End;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {////__debugbreak();
		A << Offset;
		Expression = S.ParseToken(A, Context); 
		End = S.ParseToken(A, Context);
		S.VerifyToken(End.get(), MEExprToken::EX_EndParmValue);
	}
};

class ME_EX_EmptyParmValue : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_EmptyParmValue; } // 0x4A
	virtual std::string GetDescription() override { static const std::string desc = "EX_EmptyParmValue"; return desc; }

	ME_EX_EmptyParmValue() {}

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override { //__debugbreak();

	}
};

class ME_EX_InstanceDelegate : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_InstanceDelegate; } // 0x4B
	virtual std::string GetDescription() override { static const std::string desc = "EX_InstanceDelegate"; return desc; }

	ME_EX_InstanceDelegate() {}
	MENameTableIndex FunctionName;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override { //__debugbreak();
		A << FunctionName;
	}
};

class ME_EX_InterfaceContext : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_InterfaceContext; } // 0x51
	virtual std::string GetDescription() override { static const std::string desc = "0x51"; return desc; }

	ME_EX_InterfaceContext() {}
	std::unique_ptr<METoken> Expression;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();
		Expression = S.ParseToken(A, Context);
	}
};

class ME_EX_InterfaceCast : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_InterfaceCast; } // 0x52
	virtual std::string GetDescription() override { static const std::string desc = "0x52"; return desc; }

	ME_EX_InterfaceCast() {}
	MEObjectIndex InterfaceClassIndex;
	std::unique_ptr<METoken> Expression;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();
		A << InterfaceClassIndex;
		Expression = S.ParseToken(A, Context);
	}
};

class ME_EX_EndOfScript : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_EndOfScript; } // 0x53
	virtual std::string GetDescription() override { static const std::string desc = "End of script"; return desc; }

	ME_EX_EndOfScript() {}

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();

	}
};

class ME_EX_DynArrayAdd : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_DynArrayAdd; } // 0x54
	virtual std::string GetDescription() override { static const std::string desc = "End of script"; return desc; }

	ME_EX_DynArrayAdd() {}
	std::unique_ptr<METoken> Expression;
	std::unique_ptr<METoken> CountExpression;
	std::unique_ptr<METoken> End;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {////__debugbreak();

		Expression = S.ParseToken(A, Context);
		CountExpression = S.ParseToken(A, Context);
		End = S.ParseToken(A, Context);
		S.VerifyToken(End.get(), MEExprToken::EX_EndFunctionParms);
	}
};

class ME_EX_DynArrayAddItem : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_DynArrayAddItem; } // 0x55
	virtual std::string GetDescription() override { static const std::string desc = "End of script"; return desc; }

	ME_EX_DynArrayAddItem() {}
	std::unique_ptr<METoken> ArrayPropertyExpression;
	dword Offset;
	std::unique_ptr<METoken> ItemExpression;
	std::unique_ptr<METoken> End;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {////__debugbreak();

		ArrayPropertyExpression = S.ParseToken(A, Context);
		A << Offset;
		ItemExpression = S.ParseToken(A, Context);
		End = S.ParseToken(A, Context);
		S.VerifyToken(End.get(), MEExprToken::EX_EndFunctionParms);
	}
};

class ME_EX_DynArrayRemoveItem : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_DynArrayRemoveItem; } // 0x56
	virtual std::string GetDescription() override { static const std::string desc = "End of script"; return desc; }

	ME_EX_DynArrayRemoveItem() {}
	std::unique_ptr<METoken> ArrayPropertyExpression;
	dword Offset;
	std::unique_ptr<METoken> ItemExpression;
	std::unique_ptr<METoken> End;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {////__debugbreak();

		ArrayPropertyExpression = S.ParseToken(A, Context);
		A << Offset;
		ItemExpression = S.ParseToken(A, Context);
		End = S.ParseToken(A, Context);
		S.VerifyToken(End.get(), MEExprToken::EX_EndFunctionParms);
	}
};

class ME_EX_DynArrayInsertItem : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_DynArrayInsertItem; } // 0x57
	virtual std::string GetDescription() override { static const std::string desc = "End of script"; return desc; }

	ME_EX_DynArrayInsertItem() {}
	std::unique_ptr<METoken> Expression;
	dword Offset;
	std::unique_ptr<METoken> Index;
	std::unique_ptr<METoken> Count;
	std::unique_ptr<METoken> End;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();
		Expression = S.ParseToken(A, Context);
		A << Offset;
		Index = S.ParseToken(A, Context);
		End = S.ParseToken(A, Context);
		S.VerifyToken(End.get(), MEExprToken::EX_EndFunctionParms);
	}
};

class ME_EX_DynArrayIterator : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_DynArrayIterator; } // 0x58
	virtual std::string GetDescription() override { static const std::string desc = "End of script"; return desc; }

	ME_EX_DynArrayIterator() {}
	std::unique_ptr<METoken> ArrayExpression;
	std::unique_ptr<METoken> ArrayItemExpression;
	byte hasIndex;
	std::unique_ptr<METoken> Index;
	dword Offset;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();
		ArrayExpression = S.ParseToken(A, Context);
		ArrayItemExpression = S.ParseToken(A, Context);
		A << hasIndex;
		Index = S.ParseToken(A, Context);
		A << Offset;
	}
};

class ME_EX_DynArraySort : public METoken {
public:
	virtual MEExprToken GetCode() override { return MEExprToken::EX_DynArraySort; } // 0x59
	virtual std::string GetDescription() override { static const std::string desc = "End of script"; return desc; }

	ME_EX_DynArraySort() {}
	std::unique_ptr<METoken> ArrayPropertyExpression;
	dword Offset;
	std::unique_ptr<METoken> SortExpression;
	std::unique_ptr<METoken> End;

	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override {
	//__debugbreak();
		ArrayPropertyExpression = S.ParseToken(A, Context);
		A << Offset;
		SortExpression = S.ParseToken(A, Context);
		End = S.ParseToken(A, Context);
		S.VerifyToken(End.get(), MEExprToken::EX_EndFunctionParms);
	}
};


class ME_EX_HighNative : public METoken {
public:
	MEExprToken Index;
	std::vector<std::unique_ptr<METoken>> Tokens;

	ME_EX_HighNative(MEExprToken Index) : Index(Index) {}

	virtual MEExprToken GetCode() override;
	virtual std::string GetName() override;
	virtual std::string GetDescription() override;


	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override;
};


class MENativeFuncToken : public METoken {
public:
	MEUFunction* Function;
	std::vector<std::unique_ptr<METoken>> Tokens;

	MENativeFuncToken(MEUFunction* Function) : Function(Function) {}

	virtual MEExprToken GetCode() override;
	virtual std::string GetName() override;
	virtual std::string GetDescription() override;


	virtual void Parse(MEArchive& A, MEScript& S, MEScriptContext& Context) override;
};