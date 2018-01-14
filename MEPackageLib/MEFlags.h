#pragma once

template<typename T, typename SerialT>
class MEFlags
{
public:
	std::underlying_type_t<T> Value;

	static_assert(sizeof(SerialT) <= sizeof(T));

	std::string StringFromFlags() {
		std::stringstream result;
		for (size_t i = 0; i < sizeof(std::underlying_type_t<T>) * 8; i++)
		{
			std::underlying_type_t<T> testFlag = 1;
			testFlag <<= i;
			if (is(testFlag)) {
				result << StringFromEnum(T(testFlag));
				result << ",";
			}
		}
		return result.str();
	}

	bool is(T Flag) {
		return is((std::underlying_type_t<T>)Flag);
	}

	bool is(std::underlying_type_t<T> FlagValue) {
		return (Value & FlagValue) == FlagValue;
	}
};


template<typename T, typename SerialT>
inline MEArchive& operator << (MEArchive& A, MEFlags<T, SerialT>& D) {
	SerialT value;
	A << value;
	D.Value = value;
	return A;
}

//
// Flags for loading objects.
//
enum class ELoadFlags : dword
{
	LOAD_None = 0x00000000,   // No flags.
	LOAD_SeekFree = 0x00000001,   // Loads the package via the seek free loading path/ reader
	LOAD_NoWarn = 0x00000002,   // Don't display warning if load fails.
	LOAD_Throw = 0x00000008,   // Throw exceptions upon failure.
	LOAD_Verify = 0x00000010,   // Only verify existance; don't actually load.
	LOAD_AllowDll = 0x00000020,   // Allow plain DLLs.
	LOAD_DisallowFiles = 0x00000040,   // Don't load from file.
	LOAD_NoVerify = 0x00000080,   // Don't verify imports yet.
	LOAD_Quiet = 0x00002000,   // No log warnings.
	LOAD_FindIfFail = 0x00004000,   // Tries FindObject if a linker cannot be obtained (e.g. package is currently being compiled)
	LOAD_MemoryReader = 0x00008000,   // Loads the file into memory and serializes from there.
	
	//@script patcher
	LOAD_RemappedPackage = 0x00010000,   // Indicates that is a native script package which has been renamed - GScriptPackageSuffix should be appended to the package name
	
	LOAD_NoRedirects = 0x00020000,   // Never follow redirects when loading objects; redirected loads will fail
};




extern std::string StringFromEnum(ELoadFlags flag);

//
// Package flags.
//
enum class EPackageFlags : dword
{
	PKG_AllowDownload = 0x00000001,   // Allow downloading package.
	PKG_ClientOptional = 0x00000002,   // Purely optional for clients.
	PKG_ServerSideOnly = 0x00000004,   // Only needed on the server side.
	PKG_Cooked = 0x00000008,   // Whether this package has been cooked for the target platform.
	PKG_Unsecure = 0x00000010,   // Not trusted.
	PKG_SavedWithNewerVersion = 0x00000020,   // Package was saved with newer version.
	PKG_Need = 0x00008000,   // Client needs to download this package.
	PKG_Compiling = 0x00010000,   // package is currently being compiled
	PKG_ContainsMap = 0x00020000,   // Set if the package contains a ULevel/ UWorld object
	PKG_Trash = 0x00040000,   // Set if the package was loaded from the trashcan
	PKG_DisallowLazyLoading = 0x00080000,   // Set if the archive serializing this package cannot use lazy loading
	PKG_PlayInEditor = 0x00100000,   // Set if the package was created for the purpose of PIE
	PKG_ContainsScript = 0x00200000,   // Package is allowed to contain UClasses and unrealscript
	PKG_ContainsDebugInfo = 0x00400000,   // Package contains debug info (for UDebugger)
	PKG_RequireImportsAlreadyLoaded = 0x00800000,   // Package requires all its imports to already have been loaded
	PKG_SelfContainedLighting = 0x01000000,   // All lighting in this package should be self contained
	PKG_StoreCompressed = 0x02000000,   // Package is being stored compressed, requires archive support for compression
	PKG_StoreFullyCompressed = 0x04000000,   // Package is serialized normally, and then fully compressed after (must be decompressed before LoadPackage is called)
	PKG_ContainsInlinedShaders = 0x08000000,   // Package was cooked allowing materials to inline their FMaterials (and hence shaders)
	PKG_ContainsFaceFXData = 0x10000000,   // Package contains FaceFX assets and/or animsets
	PKG_NoExportAllowed = 0x20000000,   // Package was NOT created by a modder.  Internal data not for export
	PKG_StrippedSource = 0x40000000,   // Source has been removed to compress the package size
};

extern std::string StringFromEnum(EPackageFlags flag);

//
// Flags describing a class.
//
enum class EClassFlags : dword
{
	CLASS_None = 0x00000000,
	CLASS_Abstract = 0x00000001,
	CLASS_Compiled = 0x00000002,
	CLASS_Config = 0x00000004,
	CLASS_Transient = 0x00000008,
	CLASS_Parsed = 0x00000010,
	CLASS_Localized = 0x00000020,
	CLASS_SafeReplace = 0x00000040,
	CLASS_Native = 0x00000080,
	CLASS_NoExport = 0x00000100,
	CLASS_Placeable = 0x00000200,
	CLASS_PerObjectConfig = 0x00000400,
	CLASS_NativeReplication = 0x00000800,
	CLASS_EditInlineNew = 0x00001000,
	CLASS_CollapseCategories = 0x00002000,
	CLASS_Interface = 0x00004000,
	CLASS_HasInstancedProps = 0x00200000,
	CLASS_NeedsDefProps = 0x00400000,
	CLASS_HasComponents = 0x00800000,
	CLASS_Hidden = 0x01000000,
	CLASS_Deprecated = 0x02000000,
	CLASS_HideDropDown = 0x04000000,
	CLASS_Exported = 0x08000000,
	CLASS_Intrinsic = 0x10000000,
	CLASS_NativeOnly = 0x20000000,
	CLASS_PerObjectLocalized = 0x40000000,
	CLASS_HasCrossLevelRefs = 0x80000000,
};

extern std::string StringFromEnum(EClassFlags flag);


enum class EClassCastFlags : dword
{
	CASTCLASS_None = 0x00000000,
	CASTCLASS_UField = 0x00000001,
	CASTCLASS_UConst = 0x00000002,
	CASTCLASS_UEnum = 0x00000004,
	CASTCLASS_UStruct = 0x00000008,
	CASTCLASS_UScriptStruct = 0x00000010,
	CASTCLASS_UClass = 0x00000020,
	CASTCLASS_UByteProperty = 0x00000040,
	CASTCLASS_UIntProperty = 0x00000080,
	CASTCLASS_UFloatProperty = 0x00000100,
	CASTCLASS_UComponentProperty = 0x00000200,
	CASTCLASS_UClassProperty = 0x00000400,
	CASTCLASS_UInterfaceProperty = 0x00001000,
	CASTCLASS_UNameProperty = 0x00002000,
	CASTCLASS_UStrProperty = 0x00004000,

	// these match the values of the old class flags to make conversion easier
	CASTCLASS_UProperty = 0x00008000,
	CASTCLASS_UObjectProperty = 0x00010000,
	CASTCLASS_UBoolProperty = 0x00020000,
	CASTCLASS_UState = 0x00040000,
	CASTCLASS_UFunction = 0x00080000,
	CASTCLASS_UStructProperty = 0x00100000,

	CASTCLASS_UArrayProperty = 0x00200000,
	CASTCLASS_UMapProperty = 0x00400000,
	CASTCLASS_UDelegateProperty = 0x00800000,
	CASTCLASS_UComponent = 0x01000000,


};
extern std::string StringFromEnum(EClassCastFlags flag);

// ^\s+#define (.*?)\s+DECLARE_UINT64\((.*?)\)\s+// (.*)$
// 

//
// Flags associated with each property in a class, overriding the
// property's default behavior.
//
enum class EPropertyFlags : qword
{
CPF_Edit = 0x0000000000000001ULL, // Property is user-settable in the editor.
CPF_Const = 0x0000000000000002ULL, // Actor's property always matches class's default actor property.
CPF_Input = 0x0000000000000004ULL, // Variable is writable by the input system.
CPF_ExportObject = 0x0000000000000008ULL, // Object can be exported with actor.
CPF_OptionalParm = 0x0000000000000010ULL, // Optional parameter (if CPF_Param is set).
CPF_Net = 0x0000000000000020ULL, // Property is relevant to network replication.
CPF_EditFixedSize = 0x0000000000000040ULL, // Indicates that elements of an array can be modified, but its size cannot be changed.
CPF_Parm = 0x0000000000000080ULL, // Function/When call parameter.
CPF_OutParm = 0x0000000000000100ULL, // Value is copied out after function call.
CPF_SkipParm = 0x0000000000000200ULL, // Property is a short-circuitable evaluation function parm.
CPF_ReturnParm = 0x0000000000000400ULL, // Return value.
CPF_CoerceParm = 0x0000000000000800ULL, // Coerce args into this function parameter.
CPF_Native = 0x0000000000001000ULL, // Property is native: C++ code is responsible for serializing it.
CPF_Transient = 0x0000000000002000ULL, // Property is transient: shouldn't be saved, zero-filled at load time.
CPF_Config = 0x0000000000004000ULL, // Property should be loaded/saved as permanent profile.
CPF_Localized = 0x0000000000008000ULL, // Property should be loaded as localizable text.

CPF_EditConst = 0x0000000000020000ULL, // Property is uneditable in the editor.
CPF_GlobalConfig = 0x0000000000040000ULL, // Load config from base class, not subclass.
CPF_Component = 0x0000000000080000ULL, // Property containts component references.
CPF_AlwaysInit = 0x0000000000100000ULL, // Property should never be exported as NoInit  (@todo - this doesn't need to be a property flag...only used during make)
CPF_DuplicateTransient = 0x0000000000200000ULL, // Property should always be reset to the default value during any type of duplication (copy/paste, binary duplication, etc.)
CPF_NeedCtorLink = 0x0000000000400000ULL, // Fields need construction/destruction.
CPF_NoExport = 0x0000000000800000ULL, // Property should not be exported to the native class header file.
CPF_NoImport = 0x0000000001000000ULL, // Property should not be imported when creating an object from text (copy/paste)
CPF_NoClear = 0x0000000002000000ULL, // Hide clear (and browse) button.
CPF_EditInline = 0x0000000004000000ULL, // Edit this object reference inline.

CPF_EditInlineUse = 0x0000000010000000ULL, // EditInline with Use button.
CPF_Deprecated = 0x0000000020000000ULL, // Property is deprecated.  Read it from an archive, but don't save it.
CPF_DataBinding = 0x0000000040000000ULL, // Indicates that this property should be exposed to data stores
CPF_SerializeText = 0x0000000080000000ULL, // Native property should be serialized as text (ImportText, ExportText)

CPF_RepNotify = 0x0000000100000000ULL, // Notify actors when a property is replicated
CPF_Interp = 0x0000000200000000ULL, // interpolatable property for use with matinee
CPF_NonTransactional = 0x0000000400000000ULL, // Property isn't transacted

CPF_EditorOnly = 0x0000000800000000ULL, // Property should only be loaded in the editor
CPF_NotForConsole = 0x0000001000000000ULL, // Property should not be loaded on console (or be a console cooker commandlet)
CPF_RepRetry = 0x0000002000000000ULL, // retry replication of this property if it fails to be fully sent (e.g. object references not yet available to serialize over the network)
CPF_PrivateWrite = 0x0000004000000000ULL, // property is const outside of the class it was declared in
CPF_ProtectedWrite = 0x0000008000000000ULL, // property is const outside of the class it was declared in and subclasses

CPF_ArchetypeProperty = 0x0000010000000000ULL, // property should be ignored by archives which have ArIgnoreArchetypeRef set

CPF_EditHide = 0x0000020000000000ULL, // property should never be shown in a properties window.
CPF_EditTextBox = 0x0000040000000000ULL, // property can be edited using a text dialog box.

CPF_CrossLevelPassive = 0x0000100000000000ULL, // property can point across levels, and will be serialized properly, but assumes it's target exists in-game (non-editor)
CPF_CrossLevelActive = 0x0000200000000000ULL, // property can point across levels, and will be serialized properly, and will be updated when the target is streamed in/out
};

extern std::string StringFromEnum(EPropertyFlags flag);

//
// Flags describing an object instance.
//
enum class EObjectFlags : qword {
	RF_InSingularFunc = 0x0000000000000002ULL, // In a singular function.
	RF_StateChanged = 0x0000000000000004ULL, // Object did a state change.
	RF_DebugPostLoad = 0x0000000000000008ULL, // For debugging PostLoad calls.
	RF_DebugSerialize = 0x0000000000000010ULL, // For debugging Serialize calls.
	RF_DebugFinishDestroyed = 0x0000000000000020ULL, // For debugging FinishDestroy calls.
	RF_EdSelected = 0x0000000000000040ULL, // Object is selected in one of the editors browser windows.
	RF_ZombieComponent = 0x0000000000000080ULL, // This component's template was deleted, so should not be used.
	RF_Protected = 0x0000000000000100ULL, // Property is protected (may only be accessed from its owner class or subclasses)
	RF_ClassDefaultObject = 0x0000000000000200ULL, // this object is its class's default object
	RF_ArchetypeObject = 0x0000000000000400ULL, // this object is a template for another object - treat like a class default object
	RF_ForceTagExp = 0x0000000000000800ULL, // Forces this object to be put into the export table when saving a package regardless of outer
	RF_TokenStreamAssembled = 0x0000000000001000ULL, // Set if reference token stream has already been assembled
	RF_MisalignedObject = 0x0000000000002000ULL, // Object's size no longer matches the size of its C++ class (only used during make, for native classes whose properties have changed)
	RF_RootSet = 0x0000000000004000ULL, // Object will not be garbage collected, even if unreferenced.
	RF_BeginDestroyed = 0x0000000000008000ULL, // BeginDestroy has been called on the object.
	RF_FinishDestroyed = 0x0000000000010000ULL, // FinishDestroy has been called on the object.
	RF_DebugBeginDestroyed = 0x0000000000020000ULL, // Whether object is rooted as being part of the root set (garbage collection)
	RF_MarkedByCooker = 0x0000000000040000ULL, // Marked by content cooker.
	RF_LocalizedResource = 0x0000000000080000ULL, // Whether resource object is localized.
	RF_InitializedProps = 0x0000000000100000ULL, // whether InitProperties has been called on this object
	RF_PendingFieldPatches = 0x0000000000200000ULL, // whether InitProperties has been called on this object
	RF_IsCrossLevelReferenced = 0x0000000000400000ULL, // This object has been pointed to by a cross-level reference, and therefore requires additional cleanup upon deletion

	RF_Saved = 0x0000000080000000ULL, // Object has been saved via SavePackage. Temporary.
	RF_Transactional = 0x0000000100000000ULL, // Object is transactional.
	RF_Unreachable = 0x0000000200000000ULL, // Object is not reachable on the object graph.
	RF_Public = 0x0000000400000000ULL, // Object is visible outside its package.
	RF_TagImp = 0x0000000800000000ULL, // Temporary import tag in load/save.
	RF_TagExp = 0x0000001000000000ULL, // Temporary export tag in load/save.
	RF_Obsolete = 0x0000002000000000ULL, // Object marked as obsolete and should be replaced.
	RF_TagGarbage = 0x0000004000000000ULL, // Check during garbage collection.
	RF_DisregardForGC = 0x0000008000000000ULL, // Object is being disregard for GC as its static and itself and all references are always loaded.
	RF_PerObjectLocalized = 0x0000010000000000ULL, // Object is localized by instance name, not by class.
	RF_NeedLoad = 0x0000020000000000ULL, // During load, indicates object needs loading.
	RF_AsyncLoading = 0x0000040000000000ULL, // Object is being asynchronously loaded.
	RF_NeedPostLoadSubobjects = 0x0000080000000000ULL, // During load, indicates that the object still needs to instance subobjects and fixup serialized component references
	RF_Suppress = 0x0000100000000000ULL, // @warning: Mirrored in UnName.h. Suppressed log name.
	RF_InEndState = 0x0000200000000000ULL, // Within an EndState call.
	RF_Transient = 0x0000400000000000ULL, // Don't save object.
	RF_Cooked = 0x0000800000000000ULL, // Whether the object has already been cooked
	RF_LoadForClient = 0x0001000000000000ULL, // In-file load for client.
	RF_LoadForServer = 0x0002000000000000ULL, // In-file load for client.
	RF_LoadForEdit = 0x0004000000000000ULL, // In-file load for client.
	RF_Standalone = 0x0008000000000000ULL, // Keep object around for editing even if unreferenced.
	RF_NotForClient = 0x0010000000000000ULL, // Don't load this object for the game client.
	RF_NotForServer = 0x0020000000000000ULL, // Don't load this object for the game server.
	RF_NotForEdit = 0x0040000000000000ULL, // Don't load this object for the editor.
	RF_NeedPostLoad = 0x0100000000000000ULL, // Object needs to be postloaded.
	RF_HasStack = 0x0200000000000000ULL, // Has execution stack.
	RF_Native = 0x0400000000000000ULL, // Native (UClass only).
	RF_Marked = 0x0800000000000000ULL, // Marked (for debugging).
	RF_ErrorShutdown = 0x1000000000000000ULL, // ShutdownAfterError called.
	RF_PendingKill = 0x2000000000000000ULL, // Objects that are pending destruction (invalid for gameplay but valid objects)

};

extern std::string StringFromEnum(EObjectFlags flag);

enum class EFunctionFlags : dword {

	// Function flags.
	FUNC_Final = 0x00000001,   // Function is final (prebindable, non-overridable function).
	FUNC_Defined = 0x00000002,   // Function has been defined (not just declared).
	FUNC_Iterator = 0x00000004,   // Function is an iterator.
	FUNC_Latent = 0x00000008,   // Function is a latent state function.
	FUNC_PreOperator = 0x00000010,   // Unary operator is a prefix operator.
	FUNC_Singular = 0x00000020,   // Function cannot be reentered.
	FUNC_Net = 0x00000040,   // Function is network-replicated.
	FUNC_NetReliable = 0x00000080,   // Function should be sent reliably on the network.
	FUNC_Simulated = 0x00000100,   // Function executed on the client side.
	FUNC_Exec = 0x00000200,   // Executable from command line.
	FUNC_Native = 0x00000400,   // Native function.
	FUNC_Event = 0x00000800,   // Event function.
	FUNC_Operator = 0x00001000,   // Operator function.
	FUNC_Static = 0x00002000,   // Static function.
	FUNC_HasOptionalParms = 0x00004000,   // Function has optional parameters
	FUNC_Const = 0x00008000,   // Function doesn't modify this object.

	FUNC_Public = 0x00020000,   // Function is accessible in all classes (if overridden, parameters much remain unchanged).
	FUNC_Private = 0x00040000,   // Function is accessible only in the class it is defined in (cannot be overriden, but function name may be reused in subclasses.  IOW: if overridden, parameters don't need to match, and Super.Func() cannot be accessed since it's private.)
	FUNC_Protected = 0x00080000,   // Function is accessible only in the class it is defined in and subclasses (if overridden, parameters much remain unchanged).
	FUNC_Delegate = 0x00100000,   // Function is actually a delegate.
	FUNC_NetServer = 0x00200000,   // Function is executed on servers (set by replication code if passes check)
	FUNC_HasOutParms = 0x00400000,   // function has out (pass by reference) parameters
	FUNC_HasDefaults = 0x00800000,   // function has structs that contain defaults
	FUNC_NetClient = 0x01000000,   // function is executed on clients
	FUNC_DLLImport = 0x02000000,   // function is imported from a DLL
	FUNC_K2Call = 0x04000000,   // function can be called from K2
	FUNC_K2Override = 0x08000000,   // function can be overriden/implemented from K2
	FUNC_K2Pure = 0x10000000,   // function can be called from K2, and is also pure (produces no side effects). If you set this, you should set K2call as well.

	FUNC_FuncInherit = FUNC_Exec | FUNC_Event,
	FUNC_FuncOverrideMatch = FUNC_Exec | FUNC_Final | FUNC_Latent | FUNC_PreOperator | FUNC_Iterator | FUNC_Static | FUNC_Public | FUNC_Protected | FUNC_Const,
	FUNC_NetFuncFlags = FUNC_Net | FUNC_NetReliable | FUNC_NetServer | FUNC_NetClient,

	FUNC_AllFlags = 0xFFFFFFFF,
};

extern std::string StringFromEnum(EFunctionFlags flag);

enum class ECastToken : byte {
	CST_InterfaceToObject = 0x36,
	CST_InterfaceToString = 0x37,
	CST_InterfaceToBool = 0x38,
	CST_RotatorToVector = 0x39,
	CST_ByteToInt = 0x3A,
	CST_ByteToBool = 0x3B,
	CST_ByteToFloat = 0x3C,
	CST_IntToByte = 0x3D,
	CST_IntToBool = 0x3E,
	CST_IntToFloat = 0x3F,
	CST_BoolToByte = 0x40,
	CST_BoolToInt = 0x41,
	CST_BoolToFloat = 0x42,
	CST_FloatToByte = 0x43,
	CST_FloatToInt = 0x44,
	CST_FloatToBool = 0x45,
	CST_ObjectToInterface = 0x46,
	CST_ObjectToBool = 0x47,
	CST_NameToBool = 0x48,
	CST_StringToByte = 0x49,
	CST_StringToInt = 0x4A,
	CST_StringToBool = 0x4B,
	CST_StringToFloat = 0x4C,
	CST_StringToVector = 0x4D,
	CST_StringToRotator = 0x4E,
	CST_VectorToBool = 0x4F,
	CST_VectorToRotator = 0x50,
	CST_RotatorToBool = 0x51,
	CST_ByteToString = 0x52,
	CST_IntToString = 0x53,
	CST_BoolToString = 0x54,
	CST_FloatToString = 0x55,
	CST_ObjectToString = 0x56,
	CST_NameToString = 0x57,
	CST_VectorToString = 0x58,
	CST_RotatorToString = 0x59,
	CST_DelegateToString = 0x5A,
	CST_StringToDelegate = 0x5B,
	CST_StringToName = 0x60,
	CST_Max = 0xFF, 
};