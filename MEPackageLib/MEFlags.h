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
			if ((Value & testFlag) == testFlag) {
				result << StringFromEnum(T(testFlag));
				result << ",";
			}
		}
		return result.str();
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
	LOAD_None = 0x0000,	// No flags.
	LOAD_NoFail = 0x0001,	// Critical error if load fails.
	LOAD_Async = 0x00000001,	// Loads the package using async loading path/ reader
	LOAD_NoWarn = 0x0002,	// Don't display warning if load fails.
	LOAD_EditorOnly = 0x00000004, // Load for editor-only purposes and by editor-only code
	LOAD_Throw = 0x0008,	// Throw exceptions upon failure.
	LOAD_ResolvingDeferredExports = 0x00000008,	// Denotes that we should not defer export loading (as we're resolving them)
	LOAD_Verify = 0x0010,	// Only verify existance; don't actually load.
	LOAD_AllowDll = 0x0020,	// Allow plain DLLs.
	LOAD_DisallowFiles = 0x0040,	// Don't load from file.
	LOAD_NoVerify = 0x0080,   // Don't verify imports yet.
	LOAD_IsVerifying = 0x00000100,		// Is verifying imports
	LOAD_Forgiving = 0x1000,   // Forgive missing imports (set them to NULL).
	LOAD_DisableDependencyPreloading = 0x00001000,	// Bypass dependency preloading system
	LOAD_Quiet = 0x2000,   // No log warnings.
	LOAD_NoRemap = 0x4000,   // No remapping of packages.
	LOAD_FindIfFail = 0x00004000,	// Tries FindObject if a linker cannot be obtained (e.g. package is currently being compiled)
	LOAD_MemoryReader = 0x00008000,	// Loads the file into memory and serializes from there.
	LOAD_NoRedirects = 0x00010000,	// Never follow redirects when loading objects; redirected loads will fail
	LOAD_ForDiff = 0x00020000,	// Loading for diffing.
	LOAD_PackageForPIE = 0x00080000,   // This package is being loaded for PIE, it must be flagged as such immediately
	LOAD_DeferDependencyLoads = 0x00100000,   // Do not load external (blueprint) dependencies (instead, track them for deferred loading)
	LOAD_ForFileDiff = 0x00200000,	// Load the package (not for diffing in the editor), instead verify at the two packages serialized output are the same, if they are not then debug break so that you can get the callstack and object information
	LOAD_DisableCompileOnLoad = 0x00400000,	// Prevent this load call from running compile on load for the loaded blueprint (intentionally not recursive, dependencies will still compile on load)
	LOAD_Propagate = 0,
};




extern std::string StringFromEnum(ELoadFlags flag);

//
// Package flags.
//
enum class EPackageFlags : dword
{
	PKG_AllowDownload = 0x0001,	// Allow downloading package.
	PKG_NewlyCreated = 0x00000001,	// Newly created package, not saved yet. In editor only.
	PKG_ClientOptional = 0x0002,	// Purely optional for clients.
	PKG_ServerSideOnly = 0x0004,   // Only needed on the server side.
	PKG_BrokenLinks = 0x0008,   // Loaded from linker with broken import links.
	PKG_Unsecure = 0x0010,   // Not trusted.
	PKG_CompiledIn = 0x00000010,   // This package is from "compiled in" classes.

	PKG_ForDiffing = 0x00000020,	// This package was loaded just for the purposes of diffing
	PKG_EditorOnly = 0x00000040, // This is editor-only package (for example: editor module script package)
	PKG_Developer = 0x00000080,	// Developer module
	PKG_ContainsMapData = 0x00004000,   // Contains map data (UObjects only referenced by a single ULevel) but is stored in a different package

	PKG_Need = 0x8000,	// Client needs to download this package.
	PKG_Compiling = 0x00010000,	// package is currently being compiled
	PKG_ContainsMap = 0x00020000,	// Set if the package contains a ULevel/ UWorld object
	PKG_RequiresLocalizationGather = 0x00040000,	// Set if the package contains any data to be gathered by localization
	PKG_DisallowLazyLoading = 0x00080000,	// Set if the archive serializing this package cannot use lazy loading
	PKG_PlayInEditor = 0x00100000,	// Set if the package was created for the purpose of PIE
	PKG_ContainsScript = 0x00200000,	// Package is allowed to contain UClass objects
	PKG_ReloadingForCooker = 0x40000000,   // this package is reloading in the cooker, try to avoid getting data we will never need. We won't save this package.
	PKG_FilterEditorOnly = 0x80000000,	// Package has editor-only data filtered
};

extern std::string StringFromEnum(EPackageFlags flag);

//
// Flags describing a class.
//
enum class EClassFlags : dword
{
	/** @name Base flags */
	//@{
	CLASS_None = 0x00000000u,
	/** Class is abstract and can't be instantiated directly. */
	CLASS_Abstract = 0x00000001u,
	/* Script has been compiled successfully. */
	CLASS_Compiled = 0x00002,
	/** Save object configuration only to Default INIs, never to local INIs. Must be combined with CLASS_Config */
	CLASS_DefaultConfig = 0x00000002u,
	/** Load object configuration at construction time. */
	CLASS_Config = 0x00000004u,
	/** This object type can't be saved; null it out at save time. */
	CLASS_Transient = 0x00000008u,
	/** Successfully parsed. */
	CLASS_Parsed = 0x00000010u,
	/** Class contains localized text. */
	CLASS_Localized = 0x00020,
	/*  Objects of this class can be safely replaced with default or NULL. */
	CLASS_SafeReplace = 0x00040,

	/** All the properties on the class are shown in the advanced section (which is hidden by default) unless SimpleDisplay is specified on the property */
	CLASS_AdvancedDisplay = 0x00000040u,

	/* Objects of this class are static during gameplay. */
	CLASS_RuntimeStatic = 0x00080,

	/** Class is a native class - native interfaces will have CLASS_Native set, but not RF_MarkAsNative */
	CLASS_Native = 0x00000080u,
	/** Don't export to C++ header. */
	CLASS_NoExport = 0x00000100u,

	/*  Don't allow users to create in the editor. */
	CLASS_NoUserCreate = 0x00200,

	/** Do not allow users to create in the editor. */
	CLASS_NotPlaceable = 0x00000200u,
	/** Handle object configuration on a per-object basis, rather than per-class. */
	CLASS_PerObjectConfig = 0x00000400u,

	/**  Replication handled in C++. */
	CLASS_NativeReplication = 0x00800,

	/** Class can be constructed from editinline New button. */
	CLASS_EditInlineNew = 0x00001000u,
	/** Display properties in the editor without using categories. */
	CLASS_CollapseCategories = 0x00002000u,
	/** Class is an interface **/
	CLASS_Interface = 0x00004000u,
	/**  Do not export a constructor for this class, assuming it is in the cpptext **/
	CLASS_CustomConstructor = 0x00008000u,
	/** all properties and functions in this class are const and should be exported as const */
	CLASS_Const = 0x00010000u,

	/** Indicates that the class was created from blueprint source material */
	CLASS_CompiledFromBlueprint = 0x00040000u,

	/** Indicates that only the bare minimum bits of this class should be DLL exported/imported */
	CLASS_MinimalAPI = 0x00080000u,

	/** Indicates this class must be DLL exported/imported (along with all of it's members) */
	CLASS_RequiredAPI = 0x00100000u,

	/** Indicates that references to this class default to instanced. Used to be subclasses of UComponent, but now can be any UObject */
	CLASS_DefaultToInstanced = 0x00200000u,

	/** Indicates that the parent token stream has been merged with ours. */
	CLASS_TokenStreamAssembled = 0x00400000u,
	/** Class has component properties. */
	CLASS_HasInstancedReference = 0x00800000u,
	/** Don't show this class in the editor class browser or edit inline new menus. */
	CLASS_Hidden = 0x01000000u,
	/** Don't save objects of this class when serializing */
	CLASS_Deprecated = 0x02000000u,
	/** Class not shown in editor drop down for class selection */
	CLASS_HideDropDown = 0x04000000u,
	/** Class settings are saved to <AppData>/..../Blah.ini (as opposed to CLASS_DefaultConfig) */
	CLASS_GlobalUserConfig = 0x08000000u,
	/** Class was declared directly in C++ and has no boilerplate generated by UnrealHeaderTool */
	CLASS_Intrinsic = 0x10000000u,
	/** Class has already been constructed (maybe in a previous DLL version before hot-reload). */
	CLASS_Constructed = 0x20000000u,
	/** Indicates that object configuration will not check against ini base/defaults when serialized */
	CLASS_ConfigDoNotCheckDefaults = 0x40000000u,
	/** Class has been consigned to oblivion as part of a blueprint recompile, and a newer version currently exists. */
	CLASS_NewerVersionExists = 0x80000000u,

	CLASS_Inherit = CLASS_Transient | CLASS_Config | CLASS_Localized | CLASS_SafeReplace | CLASS_RuntimeStatic | CLASS_PerObjectConfig, // Flags to inherit from base class.
	CLASS_RecompilerClear = CLASS_Inherit | CLASS_Abstract | CLASS_NoExport | CLASS_NativeReplication,
};

extern std::string StringFromEnum(EClassFlags flag);

//
// Flags associated with each property in a class, overriding the
// property's default behavior.
//
enum class EPropertyFlags : qword
{
	// Regular flags.

	CPF_Edit = 0x0000000000000001ULL,		// Property is user-settable in the editor.
	CPF_ConstParm = 0x0000000000000002ULL,		// This is a constant function parameter
	CPF_Input = 0x0000000000000004ULL, // Variable is writable by the input system.
	CPF_BlueprintVisible = 0x0000000000000004ULL,		// This property can be read by blueprint code
	CPF_ExportObject = 0x0000000000000008ULL,		// Object can be exported with actor.
	CPF_OptionalParm = 0x0000000000000010ULL, // Optional parameter (if CPF_Param is set).
	CPF_BlueprintReadOnly = 0x0000000000000010ULL,		// This property cannot be modified by blueprint code
	CPF_Net = 0x0000000000000020ULL,		// Property is relevant to network replication.
	CPF_ConstRef = 0x0000000000000040ULL, // Reference to a constant object.
	CPF_EditFixedSize = 0x0000000000000040ULL,		// Indicates that elements of an array can be modified, but its size cannot be changed.
	CPF_Parm = 0x0000000000000080ULL,		// Function/When call parameter.
	CPF_OutParm = 0x0000000000000100ULL,		// Value is copied out after function call.
	CPF_SkipParm = 0x0000000000000200ULL, // Property is a short-circuitable evaluation function parm.
	CPF_ZeroConstructor = 0x0000000000000200ULL,		// memset is fine for construction
	CPF_ReturnParm = 0x0000000000000400ULL,		// Return value.
	CPF_CoerceParm = 0x0000000000000800ULL, // Coerce args into this function parameter.
	CPF_DisableEditOnTemplate = 0x0000000000000800ULL,		// Disable editing of this property on an archetype/sub-blueprint
	CPF_Native = 0x0000000000001000ULL, // Property is native: C++ code is responsible for serializing it.
	CPF_Transient = 0x0000000000002000ULL,		// Property is transient: shouldn't be saved or loaded, except for Blueprint CDOs.
	CPF_Config = 0x0000000000004000ULL,		// Property should be loaded/saved as permanent profile.
	CPF_Localized = 0x0000000000008000ULL, // Property should be loaded as localizable text.
	CPF_Travel = 0x0000000000010000ULL, // Property travels across levels/servers.
	CPF_DisableEditOnInstance = 0x0000000000010000ULL,		// Disable editing on an instance of this class
	CPF_EditConst = 0x0000000000020000ULL,		// Property is uneditable in the editor.
	CPF_GlobalConfig = 0x0000000000040000ULL,		// Load config from base class, not subclass.
	CPF_InstancedReference = 0x0000000000080000ULL,		// Property is a component references.
	CPF_OnDemand = 0x0000000000100000ULL, // Object or dynamic array loaded on demand only.
	CPF_New = 0x0000000000200000ULL, // Automatically create inner object.
	CPF_DuplicateTransient = 0x0000000000200000ULL,		// Property should always be reset to the default value during any type of duplication (copy/paste, binary duplication, etc.)
	CPF_NeedCtorLink = 0x0000000000400000ULL, // Fields need construction/destruction.

	CPF_SubobjectReference = 0x0000000000400000ULL,		// Property contains subobject references (TSubobjectPtr)
	CPF_SaveGame = 0x0000000001000000ULL,		// Property should be serialized for save games
	CPF_NoClear = 0x0000000002000000ULL,		// Hide clear (and browse) button.
	CPF_ReferenceParm = 0x0000000008000000ULL,		// Value is passed by reference; CPF_OutParam and CPF_Param should also be set.
	CPF_BlueprintAssignable = 0x0000000010000000ULL,		// MC Delegates only.  Property should be exposed for assigning in blueprint code
	CPF_Deprecated = 0x0000000020000000ULL,		// Property is deprecated.  Read it from an archive, but don't save it.
	CPF_IsPlainOldData = 0x0000000040000000ULL,		// If this is set, then the property can be memcopied instead of CopyCompleteValue / CopySingleValue
	CPF_RepSkip = 0x0000000080000000ULL,		// Not replicated. For non replicated properties in replicated structs 
	CPF_RepNotify = 0x0000000100000000ULL,		// Notify actors when a property is replicated
	CPF_Interp = 0x0000000200000000ULL,		// interpolatable property for use with matinee
	CPF_NonTransactional = 0x0000000400000000ULL,		// Property isn't transacted
	CPF_EditorOnly = 0x0000000800000000ULL,		// Property should only be loaded in the editor
	CPF_NoDestructor = 0x0000001000000000ULL,		// No destructor
	CPF_AutoWeak = 0x0000004000000000ULL,		// Only used for weak pointers, means the export type is autoweak
	CPF_ContainsInstancedReference = 0x0000008000000000ULL,		// Property contains component references.
	CPF_AssetRegistrySearchable = 0x0000010000000000ULL,		// asset instances will add properties with this flag to the asset registry automatically
	CPF_SimpleDisplay = 0x0000020000000000ULL,		// The property is visible by default in the editor details view
	CPF_AdvancedDisplay = 0x0000040000000000ULL,		// The property is advanced and not visible by default in the editor details view
	CPF_Protected = 0x0000080000000000ULL,		// property is protected from the perspective of script
	CPF_BlueprintCallable = 0x0000100000000000ULL,		// MC Delegates only.  Property should be exposed for calling in blueprint code
	CPF_BlueprintAuthorityOnly = 0x0000200000000000ULL,		// MC Delegates only.  This delegate accepts (only in blueprint) only events with BlueprintAuthorityOnly.
	CPF_TextExportTransient = 0x0000400000000000ULL,		// Property shouldn't be exported to text format (e.g. copy/paste)
	CPF_NonPIEDuplicateTransient = 0x0000800000000000ULL,		// Property should only be copied in PIE
	CPF_ExposeOnSpawn = 0x0001000000000000ULL,		// Property is exposed on spawn
	CPF_PersistentInstance = 0x0002000000000000ULL,		// A object referenced by the property is duplicated like a component. (Each actor should have an own instance.)
	CPF_UObjectWrapper = 0x0004000000000000ULL,		// Property was parsed as a wrapper class like TSubclassOf<T>, FScriptInterface etc., rather than a USomething*
	CPF_HasGetValueTypeHash = 0x0008000000000000ULL,		// This property can generate a meaningful hash value.
	CPF_NativeAccessSpecifierPublic = 0x0010000000000000ULL,		// Public native access specifier
	CPF_NativeAccessSpecifierProtected = 0x0020000000000000ULL,		// Protected native access specifier
	CPF_NativeAccessSpecifierPrivate = 0x0040000000000000ULL,		// Private native access specifier
	CPF_SkipSerialization = 0x0080000000000000ULL,		// Property shouldn't be serialized, can still be exported to text


#define CPF_NativeAccessSpecifiers	(CPF_NativeAccessSpecifierPublic | CPF_NativeAccessSpecifierProtected | CPF_NativeAccessSpecifierPrivate)

#define CPF_ParmFlags				(CPF_Parm | CPF_OutParm | CPF_ReturnParm | CPF_ReferenceParm | CPF_ConstParm)
#define CPF_PropagateToArrayInner	(CPF_ExportObject | CPF_PersistentInstance | CPF_InstancedReference | CPF_ContainsInstancedReference | CPF_Config | CPF_EditConst | CPF_Deprecated | CPF_EditorOnly | CPF_AutoWeak | CPF_UObjectWrapper )
#define CPF_PropagateToMapValue		(CPF_ExportObject | CPF_PersistentInstance | CPF_InstancedReference | CPF_ContainsInstancedReference | CPF_Config | CPF_EditConst | CPF_Deprecated | CPF_EditorOnly | CPF_AutoWeak | CPF_UObjectWrapper | CPF_Edit )
#define CPF_PropagateToMapKey		(CPF_ExportObject | CPF_PersistentInstance | CPF_InstancedReference | CPF_ContainsInstancedReference | CPF_Config | CPF_EditConst | CPF_Deprecated | CPF_EditorOnly | CPF_AutoWeak | CPF_UObjectWrapper | CPF_Edit )
#define CPF_PropagateToSetElement	(CPF_ExportObject | CPF_PersistentInstance | CPF_InstancedReference | CPF_ContainsInstancedReference | CPF_Config | CPF_EditConst | CPF_Deprecated | CPF_EditorOnly | CPF_AutoWeak | CPF_UObjectWrapper | CPF_Edit )

														/** the flags that should never be set on interface properties */
#define CPF_InterfaceClearMask		(CPF_ExportObject|CPF_InstancedReference|CPF_ContainsInstancedReference)

														/** all the properties that can be stripped for final release console builds */
#define CPF_DevelopmentAssets		(CPF_EditorOnly)

														/** all the properties that should never be loaded or saved */
#define CPF_ComputedFlags			(CPF_IsPlainOldData | CPF_NoDestructor | CPF_ZeroConstructor | CPF_HasGetValueTypeHash)

#define CPF_AllFlags				0xFFFFFFFFFFFFFFFFULL

};

extern std::string StringFromEnum(EPropertyFlags flag);

//
// Flags describing an object instance.
//
enum class EObjectFlags : qword
{
	RF_NoFlags = 0x00000000,	///< No flags, used to avoid a cast
	RF_Transactional = 0x00000001,   // Object is transactional.
	RF_PublicUE4 = 0x00000001,	///< Object is visible outside its package.
	RF_Unreachable = 0x00000002,	// Object is not reachable on the object graph.
	RF_StandaloneUE4 = 0x00000002,	///< Keep object around for editing even if unreferenced.
	RF_Public = 0x00000004,	// Object is visible outside its package.
	RF_MarkAsNativeUE4 = 0x00000004,	///< Object (UField) will be marked as native on construction (DO NOT USE THIS FLAG in HasAnyFlags() etc)
	RF_TagImp = 0x00000008,	// Temporary import tag in load/save.
	RF_TransactionalUE4 = 0x00000008,	///< Object is transactional.
	RF_TagExp = 0x00000010,	// Temporary export tag in load/save.
	RF_ClassDefaultObjectUE4 = 0x00000010,	///< This object is its class's default object
	RF_SourceModified = 0x00000020,   // Modified relative to source files.
	RF_ArchetypeObjectUE4 = 0x00000020,	///< This object is a template for another object - treat like a class default object
	RF_TagGarbage = 0x00000040,	// Check during garbage collection.
	RF_TransientUE4 = 0x00000040,	///< Don't save object.
	RF_MarkAsRootSetUE4 = 0x00000080,	///< Object will be marked as root set on construction and not be garbage collected, even if unreferenced (DO NOT USE THIS FLAG in HasAnyFlags() etc)
	RF_TagGarbageTempUE4 = 0x00000100,	///< This is a temp user flag for various utilities that need to use the garbage collector. The garbage collector itself does not interpret it.
	RF_NeedLoad = 0x00000200,   // During load, indicates object needs loading.
	RF_NeedInitializationUE4 = 0x00000200,	///< This object has not completed its initialization process. Cleared when ~FObjectInitializer completes
	RF_HighlightedName = 0x00000400,	// A hardcoded name which should be syntax-highlighted.
	RF_EliminateObject = 0x00000400,   // NULL out references to this during garbage collecion.
	RF_NeedLoadUE4 = 0x00000400,	///< During load, indicates object needs loading.
	RF_InSingularFunc = 0x00000800,	// In a singular function.
	RF_RemappedName = 0x00000800,   // Name is remapped.
	RF_KeepForCookerUE4 = 0x00000800,	///< Keep this object during garbage collection because it's still being used by the cooker
	RF_Suppress = 0x00001000,	//warning: Mirrored in UnName.h. Suppressed log name.
	RF_StateChanged = 0x00001000,   // Object did a state change.
	RF_NeedPostLoadUE4 = 0x00001000,	///< Object needs to be postloaded.
	RF_InEndState = 0x00002000,   // Within an EndState call.
	RF_NeedPostLoadSubobjectsUE4 = 0x00002000,	///< During load, indicates that the object still needs to instance subobjects and fixup serialized component references
	RF_Transient = 0x00004000,	// Don't save object.
	RF_NewerVersionExistsUE4 = 0x00004000,	///< Object has been consigned to oblivion due to its owner package being reloaded, and a newer version currently exists
	RF_Preloading = 0x00008000,   // Data is being preloaded from file.
	RF_BeginDestroyedUE4 = 0x00008000,	///< BeginDestroy has been called on the object.
	RF_LoadForClient = 0x00010000,	// In-file load for client.
	RF_FinishDestroyedUE4 = 0x00010000,	///< FinishDestroy has been called on the object.
	RF_LoadForServer = 0x00020000,	// In-file load for client.
	RF_BeingRegeneratedUE4 = 0x00020000,	///< Flagged on UObjects that are used to create UClasses (e.g. Blueprints) while they are regenerating their UClass on load (See FLinkerLoad::CreateExport())
	RF_LoadForEdit = 0x00040000,	// In-file load for client.
	RF_DefaultSubObjectUE4 = 0x00040000,	///< Flagged on subobjects that are defaults
	RF_Standalone = 0x00080000,   // Keep object around for editing even if unreferenced.
	RF_NotForClient = 0x00100000,	// Don't load this object for the game client.
	RF_NotForServer = 0x00200000,	// Don't load this object for the game server.
	RF_NotForEdit = 0x00400000,	// Don't load this object for the editor.
	RF_Destroyed = 0x00800000,	// Object Destroy has already been called.
	RF_WasLoadedUE4 = 0x00080000,	///< Flagged on UObjects that were loaded
	RF_NeedPostLoad = 0x01000000,   // Object needs to be postloaded.
	RF_TextExportTransientUE4 = 0x00100000,	///< Do not export object to text form (e.g. copy/paste). Generally used for sub-objects that can be regenerated from data in their parent object.
	RF_HasStack = 0x02000000,	// Has execution stack.
	RF_LoadCompletedUE4 = 0x00200000,	///< Object has been completely serialized by linkerload at least once. DO NOT USE THIS FLAG, It should be replaced with RF_WasLoaded.
	RF_Native = 0x04000000,   // Native (UClass only).
	RF_InheritableComponentTemplateUE4 = 0x00400000, ///< Archetype of the object can be in its super class
	RF_Marked = 0x08000000,   // Marked (for debugging).
	RF_DuplicateTransientUE4 = 0x00800000, ///< Object should not be included in any type of duplication (copy/paste, binary duplication, etc.)
	RF_ErrorShutdown = 0x10000000,	// ShutdownAfterError called.
	RF_StrongRefOnFrameUE4 = 0x01000000,	///< References to this object from persistent function frame are handled as strong ones.
	RF_DebugPostLoad = 0x20000000,   // For debugging Serialize calls.
	RF_NonPIEDuplicateTransientUE4 = 0x02000000,  ///< Object should not be included for duplication unless it's being duplicated for a PIE session
	RF_DebugSerialize = 0x40000000,   // For debugging Serialize calls.
	RF_DynamicUE4 = 0x04000000, // Field Only. Dynamic field - doesn't get constructed during static initialization, can be constructed multiple times
	RF_DebugDestroy = 0x80000000,   // For debugging Destroy calls.
	RF_WillBeLoadedUE4 = 0x08000000, // This object was constructed during load and will be loaded shortly

	RF_ContextFlags = RF_NotForClient | RF_NotForServer | RF_NotForEdit, // All context flags.
	RF_LoadContextFlags = RF_LoadForClient | RF_LoadForServer | RF_LoadForEdit, // Flags affecting loading.
	RF_Load = RF_ContextFlags | RF_LoadContextFlags | RF_Public | RF_Standalone | RF_Native | RF_SourceModified | RF_Transactional | RF_HasStack, // Flags to load from Unrealfiles.
	RF_Keep = RF_Native | RF_Marked, // Flags to persist across loads.
	RF_ScriptMask = RF_Transactional | RF_Public | RF_Transient | RF_NotForClient | RF_NotForServer | RF_NotForEdit // Script-accessible flags.
};

extern std::string StringFromEnum(EObjectFlags flag);

enum class EFunctionFlags: dword {

	// Function flags.
	FUNC_None = 0x00000000,

	FUNC_Final = 0x00000001,	// Function is final (prebindable, non-overridable function).
	FUNC_RequiredAPI = 0x00000002,	// Indicates this function is DLL exported/imported.
	FUNC_BlueprintAuthorityOnly = 0x00000004,   // Function will only run if the object has network authority
	FUNC_BlueprintCosmetic = 0x00000008,   // Function is cosmetic in nature and should not be invoked on dedicated servers
	FUNC_Net = 0x00000040,   // Function is network-replicated.
	FUNC_NetReliable = 0x00000080,   // Function should be sent reliably on the network.
	FUNC_NetRequest = 0x00000100,	// Function is sent to a net service
	FUNC_Exec = 0x00000200,	// Executable from command line.
	FUNC_Native = 0x00000400,	// Native function.
	FUNC_Event = 0x00000800,   // Event function.
	FUNC_NetResponse = 0x00001000,   // Function response from a net service
	FUNC_Static = 0x00002000,   // Static function.
	FUNC_NetMulticast = 0x00004000,	// Function is networked multicast Server -> All Clients
	FUNC_MulticastDelegate = 0x00010000,	// Function is a multi-cast delegate signature (also requires FUNC_Delegate to be set!)
	FUNC_Public = 0x00020000,	// Function is accessible in all classes (if overridden, parameters must remain unchanged).
	FUNC_Private = 0x00040000,	// Function is accessible only in the class it is defined in (cannot be overridden, but function name may be reused in subclasses.  IOW: if overridden, parameters don't need to match, and Super.Func() cannot be accessed since it's private.)
	FUNC_Protected = 0x00080000,	// Function is accessible only in the class it is defined in and subclasses (if overridden, parameters much remain unchanged).
	FUNC_Delegate = 0x00100000,	// Function is delegate signature (either single-cast or multi-cast, depending on whether FUNC_MulticastDelegate is set.)
	FUNC_NetServer = 0x00200000,	// Function is executed on servers (set by replication code if passes check)
	FUNC_HasOutParms = 0x00400000,	// function has out (pass by reference) parameters
	FUNC_HasDefaults = 0x00800000,	// function has structs that contain defaults
	FUNC_NetClient = 0x01000000,	// function is executed on clients
	FUNC_DLLImport = 0x02000000,	// function is imported from a DLL
	FUNC_BlueprintCallable = 0x04000000,	// function can be called from blueprint code
	FUNC_BlueprintEvent = 0x08000000,	// function can be overridden/implemented from a blueprint
	FUNC_BlueprintPure = 0x10000000,	// function can be called from blueprint code, and is also pure (produces no side effects). If you set this, you should set FUNC_BlueprintCallable as well.
	FUNC_EditorOnly = 0x20000000,	// function can only be called from an editor scrippt.
	FUNC_Const = 0x40000000,	// function can be called from blueprint code, and only reads state (never writes state)
	FUNC_NetValidate = 0x80000000,	// function must supply a _Validate implementation
};

extern std::string StringFromEnum(EFunctionFlags flag);