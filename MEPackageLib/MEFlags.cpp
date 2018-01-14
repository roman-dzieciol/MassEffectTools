#include "stdafx.h"
#include "MEFlags.h"
#include <inttypes.h>

//
// ^\s+([A-Z]+_)([a-zA-Z]+)\s.*
// case EPackageFlags::$1$2: return "$2";
//


std::string StringFromEnum(ELoadFlags flag) {
	switch (flag) {
	case ELoadFlags::LOAD_None: return "None";
	case ELoadFlags::LOAD_SeekFree: return "SeekFree";
	case ELoadFlags::LOAD_NoWarn: return "NoWarn";
	case ELoadFlags::LOAD_Throw: return "Throw";
	case ELoadFlags::LOAD_Verify: return "Verify";
	case ELoadFlags::LOAD_AllowDll: return "AllowDll";
	case ELoadFlags::LOAD_DisallowFiles: return "DisallowFiles";
	case ELoadFlags::LOAD_NoVerify: return "NoVerify";
	case ELoadFlags::LOAD_Quiet: return "Quiet";
	case ELoadFlags::LOAD_FindIfFail: return "FindIfFail";
	case ELoadFlags::LOAD_MemoryReader: return "MemoryReader";
	case ELoadFlags::LOAD_RemappedPackage: return "RemappedPackage";
	case ELoadFlags::LOAD_NoRedirects: return "NoRedirects";
	}
	return MEFormat("0x%x", (dword)flag);
}

std::string StringFromEnum(EPackageFlags flag) {
	switch (flag) {
	case EPackageFlags::PKG_AllowDownload: return "AllowDownload";
	case EPackageFlags::PKG_ClientOptional: return "ClientOptional";
	case EPackageFlags::PKG_ServerSideOnly: return "ServerSideOnly";
	case EPackageFlags::PKG_Cooked: return "Cooked";
	case EPackageFlags::PKG_Unsecure: return "Unsecure";
	case EPackageFlags::PKG_SavedWithNewerVersion: return "SavedWithNewerVersion";
	case EPackageFlags::PKG_Need: return "Need";
	case EPackageFlags::PKG_Compiling: return "Compiling";
	case EPackageFlags::PKG_ContainsMap: return "ContainsMap";
	case EPackageFlags::PKG_Trash: return "Trash";
	case EPackageFlags::PKG_DisallowLazyLoading: return "DisallowLazyLoading";
	case EPackageFlags::PKG_PlayInEditor: return "PlayInEditor";
	case EPackageFlags::PKG_ContainsScript: return "ContainsScript";
	case EPackageFlags::PKG_ContainsDebugInfo: return "ContainsDebugInfo";
	case EPackageFlags::PKG_RequireImportsAlreadyLoaded: return "RequireImportsAlreadyLoaded";
	case EPackageFlags::PKG_SelfContainedLighting: return "SelfContainedLighting";
	case EPackageFlags::PKG_StoreCompressed: return "StoreCompressed";
	case EPackageFlags::PKG_StoreFullyCompressed: return "StoreFullyCompressed";
	case EPackageFlags::PKG_ContainsInlinedShaders: return "ContainsInlinedShaders";
	case EPackageFlags::PKG_ContainsFaceFXData: return "ContainsFaceFXData";
	case EPackageFlags::PKG_NoExportAllowed: return "NoExportAllowed";
	case EPackageFlags::PKG_StrippedSource: return "StrippedSource";
	}
	return MEFormat("0x%x", (dword)flag);
}

std::string StringFromEnum(EClassFlags flag) {
	switch (flag) {
	case EClassFlags::CLASS_None: return "None";
	case EClassFlags::CLASS_Abstract: return "Abstract";
	case EClassFlags::CLASS_Compiled: return "Compiled";
	case EClassFlags::CLASS_Config: return "Config";
	case EClassFlags::CLASS_Transient: return "Transient";
	case EClassFlags::CLASS_Parsed: return "Parsed";
	case EClassFlags::CLASS_Localized: return "Localized";
	case EClassFlags::CLASS_SafeReplace: return "SafeReplace";
	case EClassFlags::CLASS_Native: return "Native";
	case EClassFlags::CLASS_NoExport: return "NoExport";
	case EClassFlags::CLASS_Placeable: return "Placeable";
	case EClassFlags::CLASS_PerObjectConfig: return "PerObjectConfig";
	case EClassFlags::CLASS_NativeReplication: return "NativeReplication";
	case EClassFlags::CLASS_EditInlineNew: return "EditInlineNew";
	case EClassFlags::CLASS_CollapseCategories: return "CollapseCategories";
	case EClassFlags::CLASS_Interface: return "Interface";
	case EClassFlags::CLASS_HasInstancedProps: return "HasInstancedProps";
	case EClassFlags::CLASS_NeedsDefProps: return "NeedsDefProps";
	case EClassFlags::CLASS_HasComponents: return "HasComponents";
	case EClassFlags::CLASS_Hidden: return "Hidden";
	case EClassFlags::CLASS_Deprecated: return "Deprecated";
	case EClassFlags::CLASS_HideDropDown: return "HideDropDown";
	case EClassFlags::CLASS_Exported: return "Exported";
	case EClassFlags::CLASS_Intrinsic: return "Intrinsic";
	case EClassFlags::CLASS_NativeOnly: return "NativeOnly";
	case EClassFlags::CLASS_PerObjectLocalized: return "PerObjectLocalized";
	case EClassFlags::CLASS_HasCrossLevelRefs: return "HasCrossLevelRefs";
	}
	return MEFormat("0x%x", (dword)flag);
}


std::string StringFromEnum(EClassCastFlags flag) {
	switch (flag) {
	case EClassCastFlags::CASTCLASS_None: return "None";
	case EClassCastFlags::CASTCLASS_UField: return "UField";
	case EClassCastFlags::CASTCLASS_UConst: return "UConst";
	case EClassCastFlags::CASTCLASS_UEnum: return "UEnum";
	case EClassCastFlags::CASTCLASS_UStruct: return "UStruct";
	case EClassCastFlags::CASTCLASS_UScriptStruct: return "UScriptStruct";
	case EClassCastFlags::CASTCLASS_UClass: return "UClass";
	case EClassCastFlags::CASTCLASS_UByteProperty: return "UByteProperty";
	case EClassCastFlags::CASTCLASS_UIntProperty: return "UIntProperty";
	case EClassCastFlags::CASTCLASS_UFloatProperty: return "UFloatProperty";
	case EClassCastFlags::CASTCLASS_UComponentProperty: return "UComponentProperty";
	case EClassCastFlags::CASTCLASS_UClassProperty: return "UClassProperty";
	case EClassCastFlags::CASTCLASS_UInterfaceProperty: return "UInterfaceProperty";
	case EClassCastFlags::CASTCLASS_UNameProperty: return "UNameProperty";
	case EClassCastFlags::CASTCLASS_UStrProperty: return "UStrProperty";

	case EClassCastFlags::CASTCLASS_UProperty: return "UProperty";
	case EClassCastFlags::CASTCLASS_UObjectProperty: return "UObjectProperty";
	case EClassCastFlags::CASTCLASS_UBoolProperty: return "UBoolProperty";
	case EClassCastFlags::CASTCLASS_UState: return "UState";
	case EClassCastFlags::CASTCLASS_UFunction: return "UFunction";
	case EClassCastFlags::CASTCLASS_UStructProperty: return "UStructProperty";
	case EClassCastFlags::CASTCLASS_UArrayProperty: return "UArrayProperty";
	case EClassCastFlags::CASTCLASS_UMapProperty: return "UMapProperty";
	case EClassCastFlags::CASTCLASS_UDelegateProperty: return "UDelegateProperty";
	case EClassCastFlags::CASTCLASS_UComponent: return "UComponent";
	}
	return MEFormat("0x%x", (dword)flag);
}


std::string StringFromEnum(EPropertyFlags flag) {
	switch (flag) {
	case EPropertyFlags::CPF_Edit: return "Edit";
	case EPropertyFlags::CPF_Const: return "Const";
	case EPropertyFlags::CPF_Input: return "Input";
	case EPropertyFlags::CPF_ExportObject: return "ExportObject";
	case EPropertyFlags::CPF_OptionalParm: return "OptionalParm";
	case EPropertyFlags::CPF_Net: return "Net";
	case EPropertyFlags::CPF_EditFixedSize: return "EditFixedSize";
	case EPropertyFlags::CPF_Parm: return "Parm";
	case EPropertyFlags::CPF_OutParm: return "OutParm";
	case EPropertyFlags::CPF_SkipParm: return "SkipParm";
	case EPropertyFlags::CPF_ReturnParm: return "ReturnParm";
	case EPropertyFlags::CPF_CoerceParm: return "CoerceParm";
	case EPropertyFlags::CPF_Native: return "Native";
	case EPropertyFlags::CPF_Transient: return "Transient";
	case EPropertyFlags::CPF_Config: return "Config";
	case EPropertyFlags::CPF_Localized: return "Localized";
	case EPropertyFlags::CPF_EditConst: return "EditConst";
	case EPropertyFlags::CPF_GlobalConfig: return "GlobalConfig";
	case EPropertyFlags::CPF_Component: return "Component";
	case EPropertyFlags::CPF_AlwaysInit: return "AlwaysInit";
	case EPropertyFlags::CPF_DuplicateTransient: return "DuplicateTransient";
	case EPropertyFlags::CPF_NeedCtorLink: return "NeedCtorLink";
	case EPropertyFlags::CPF_NoExport: return "NoExport";
	case EPropertyFlags::CPF_NoImport: return "NoImport";
	case EPropertyFlags::CPF_NoClear: return "NoClear";
	case EPropertyFlags::CPF_EditInline: return "EditInline";
	case EPropertyFlags::CPF_EditInlineUse: return "EditInlineUse";
	case EPropertyFlags::CPF_Deprecated: return "Deprecated";
	case EPropertyFlags::CPF_DataBinding: return "DataBinding";
	case EPropertyFlags::CPF_SerializeText: return "SerializeText";
	case EPropertyFlags::CPF_RepNotify: return "RepNotify";
	case EPropertyFlags::CPF_Interp: return "Interp";
	case EPropertyFlags::CPF_NonTransactional: return "NonTransactional";
	case EPropertyFlags::CPF_EditorOnly: return "EditorOnly";
	case EPropertyFlags::CPF_NotForConsole: return "NotForConsole";
	case EPropertyFlags::CPF_RepRetry: return "RepRetry";
	case EPropertyFlags::CPF_PrivateWrite: return "PrivateWrite";
	case EPropertyFlags::CPF_ProtectedWrite: return "ProtectedWrite";

	case EPropertyFlags::CPF_ArchetypeProperty: return "ArchetypeProperty";
	case EPropertyFlags::CPF_EditHide: return "EditHide";
	case EPropertyFlags::CPF_EditTextBox: return "EditTextBox";
	case EPropertyFlags::CPF_CrossLevelPassive: return "CrossLevelPassive";
	case EPropertyFlags::CPF_CrossLevelActive: return "CrossLevelActive";
	}
	return MEFormat("0x%" PRIx64, (qword)flag);
}

std::string StringFromEnum(EObjectFlags flag) {
	switch (flag) {
	case EObjectFlags::RF_InSingularFunc: return "InSingularFunc";
	case EObjectFlags::RF_StateChanged: return "StateChanged";
	case EObjectFlags::RF_DebugPostLoad: return "DebugPostLoad";
	case EObjectFlags::RF_DebugSerialize: return "DebugSerialize";
	case EObjectFlags::RF_DebugFinishDestroyed: return "DebugFinishDestroyed";
	case EObjectFlags::RF_EdSelected: return "EdSelected";
	case EObjectFlags::RF_ZombieComponent: return "ZombieComponent";
	case EObjectFlags::RF_Protected: return "Protected";
	case EObjectFlags::RF_ClassDefaultObject: return "ClassDefaultObject";
	case EObjectFlags::RF_ArchetypeObject: return "ArchetypeObject";
	case EObjectFlags::RF_ForceTagExp: return "ForceTagExp";
	case EObjectFlags::RF_TokenStreamAssembled: return "TokenStreamAssembled";
	case EObjectFlags::RF_MisalignedObject: return "MisalignedObject";
	case EObjectFlags::RF_RootSet: return "RootSet";
	case EObjectFlags::RF_BeginDestroyed: return "BeginDestroyed";
	case EObjectFlags::RF_FinishDestroyed: return "FinishDestroyed";
	case EObjectFlags::RF_DebugBeginDestroyed: return "DebugBeginDestroyed";
	case EObjectFlags::RF_MarkedByCooker: return "MarkedByCooker";
	case EObjectFlags::RF_LocalizedResource: return "LocalizedResource";
	case EObjectFlags::RF_InitializedProps: return "InitializedProps";
	case EObjectFlags::RF_PendingFieldPatches: return "PendingFieldPatches";
	case EObjectFlags::RF_IsCrossLevelReferenced: return "IsCrossLevelReferenced";
	case EObjectFlags::RF_Saved: return "Saved";
	case EObjectFlags::RF_Transactional: return "Transactional";
	case EObjectFlags::RF_Unreachable: return "Unreachable";
	case EObjectFlags::RF_Public: return "Public";
	case EObjectFlags::RF_TagImp: return "TagImp";
	case EObjectFlags::RF_TagExp: return "TagExp";
	case EObjectFlags::RF_Obsolete: return "Obsolete";
	case EObjectFlags::RF_TagGarbage: return "TagGarbage";
	case EObjectFlags::RF_DisregardForGC: return "DisregardForGC";
	case EObjectFlags::RF_PerObjectLocalized: return "PerObjectLocalized";
	case EObjectFlags::RF_NeedLoad: return "NeedLoad";
	case EObjectFlags::RF_AsyncLoading: return "AsyncLoading";
	case EObjectFlags::RF_NeedPostLoadSubobjects: return "NeedPostLoadSubobjects";
	case EObjectFlags::RF_Suppress: return "Suppress";
	case EObjectFlags::RF_InEndState: return "InEndState";
	case EObjectFlags::RF_Transient: return "Transient";
	case EObjectFlags::RF_Cooked: return "Cooked";
	case EObjectFlags::RF_LoadForClient: return "LoadForClient";
	case EObjectFlags::RF_LoadForServer: return "LoadForServer";
	case EObjectFlags::RF_LoadForEdit: return "LoadForEdit";
	case EObjectFlags::RF_Standalone: return "Standalone";
	case EObjectFlags::RF_NotForClient: return "NotForClient";
	case EObjectFlags::RF_NotForServer: return "NotForServer";
	case EObjectFlags::RF_NotForEdit: return "NotForEdit";
	case EObjectFlags::RF_NeedPostLoad: return "NeedPostLoad";
	case EObjectFlags::RF_HasStack: return "HasStack";
	case EObjectFlags::RF_Native: return "Native";
	case EObjectFlags::RF_Marked: return "Marked";
	case EObjectFlags::RF_ErrorShutdown: return "ErrorShutdown";
	case EObjectFlags::RF_PendingKill: return "PendingKill";
	}
	return MEFormat("0x%" PRIx64, (qword)flag);
}

std::string StringFromEnum(EFunctionFlags flag) {
	switch (flag) {
	case EFunctionFlags::FUNC_Final: return "Final";
	case EFunctionFlags::FUNC_Defined: return "Defined";
	case EFunctionFlags::FUNC_Iterator: return "Iterator";
	case EFunctionFlags::FUNC_Latent: return "Latent";
	case EFunctionFlags::FUNC_PreOperator: return "PreOperator";
	case EFunctionFlags::FUNC_Singular: return "Singular";
	case EFunctionFlags::FUNC_Net: return "Net";
	case EFunctionFlags::FUNC_NetReliable: return "NetReliable";
	case EFunctionFlags::FUNC_Simulated: return "Simulated";
	case EFunctionFlags::FUNC_Exec: return "Exec";
	case EFunctionFlags::FUNC_Native: return "Native";
	case EFunctionFlags::FUNC_Event: return "Event";
	case EFunctionFlags::FUNC_Operator: return "Operator";
	case EFunctionFlags::FUNC_Static: return "Static";
	case EFunctionFlags::FUNC_HasOptionalParms: return "HasOptionalParms";
	case EFunctionFlags::FUNC_Const: return "Const";
	case EFunctionFlags::FUNC_Public: return "Public";
	case EFunctionFlags::FUNC_Private: return "Private";
	case EFunctionFlags::FUNC_Protected: return "Protected";
	case EFunctionFlags::FUNC_Delegate: return "Delegate";
	case EFunctionFlags::FUNC_NetServer: return "NetServer";
	case EFunctionFlags::FUNC_HasOutParms: return "HasOutParms";
	case EFunctionFlags::FUNC_HasDefaults: return "HasDefaults";
	case EFunctionFlags::FUNC_NetClient: return "NetClient";
	case EFunctionFlags::FUNC_DLLImport: return "DLLImport";
	case EFunctionFlags::FUNC_K2Call: return "K2Call";
	case EFunctionFlags::FUNC_K2Override: return "K2Override";
	case EFunctionFlags::FUNC_K2Pure: return "K2Pure";
	}
	return MEFormat("0x%x", (dword)flag);
}

std::string StringFromEnum(ECastToken flag) {
	switch (flag) {
	case ECastToken::CST_InterfaceToObject: return "CST_InterfaceToObject";
	case ECastToken::CST_InterfaceToString: return "CST_InterfaceToString";
	case ECastToken::CST_InterfaceToBool: return "CST_InterfaceToBool";
	case ECastToken::CST_RotatorToVector: return "CST_RotatorToVector";
	case ECastToken::CST_ByteToInt: return "CST_ByteToInt";
	case ECastToken::CST_ByteToBool: return "CST_ByteToBool";
	case ECastToken::CST_ByteToFloat: return "CST_ByteToFloat";
	case ECastToken::CST_IntToByte: return "CST_IntToByte";
	case ECastToken::CST_IntToBool: return "CST_IntToBool";
	case ECastToken::CST_IntToFloat: return "CST_IntToFloat";
	case ECastToken::CST_BoolToByte: return "CST_BoolToByte";
	case ECastToken::CST_BoolToInt: return "CST_BoolToInt";
	case ECastToken::CST_BoolToFloat: return "CST_BoolToFloat";
	case ECastToken::CST_FloatToByte: return "CST_FloatToByte";
	case ECastToken::CST_FloatToInt: return "CST_FloatToInt";
	case ECastToken::CST_FloatToBool: return "CST_FloatToBool";
	case ECastToken::CST_ObjectToInterface: return "CST_ObjectToInterface";
	case ECastToken::CST_ObjectToBool: return "CST_ObjectToBool";
	case ECastToken::CST_NameToBool: return "CST_NameToBool";
	case ECastToken::CST_StringToByte: return "CST_StringToByte";
	case ECastToken::CST_StringToInt: return "CST_StringToInt";
	case ECastToken::CST_StringToBool: return "CST_StringToBool";
	case ECastToken::CST_StringToFloat: return "CST_StringToFloat";
	case ECastToken::CST_StringToVector: return "CST_StringToVector";
	case ECastToken::CST_StringToRotator: return "CST_StringToRotator";
	case ECastToken::CST_VectorToBool: return "CST_VectorToBool";
	case ECastToken::CST_VectorToRotator: return "CST_VectorToRotator";
	case ECastToken::CST_RotatorToBool: return "CST_RotatorToBool";
	case ECastToken::CST_ByteToString: return "CST_ByteToString";
	case ECastToken::CST_IntToString: return "CST_IntToString";
	case ECastToken::CST_BoolToString: return "CST_BoolToString";
	case ECastToken::CST_FloatToString: return "CST_FloatToString";
	case ECastToken::CST_ObjectToString: return "CST_ObjectToString";
	case ECastToken::CST_NameToString: return "CST_NameToString";
	case ECastToken::CST_VectorToString: return "CST_VectorToString";
	case ECastToken::CST_RotatorToString: return "CST_RotatorToString";
	case ECastToken::CST_DelegateToString: return "CST_DelegateToString";
	case ECastToken::CST_StringToDelegate: return "CST_StringToDelegate";
	case ECastToken::CST_StringToName: return "CST_StringToName";
	case ECastToken::CST_Max: return "CST_Max";
	}
	return MEFormat("0x%x", (dword)flag);
}

