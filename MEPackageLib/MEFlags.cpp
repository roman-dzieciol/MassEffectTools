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
	case ELoadFlags::LOAD_NoFail: return "NoFail/Async";
		//case ELoadFlags::LOAD_Async: return "Async";
	case ELoadFlags::LOAD_NoWarn: return "NoWarn";
	case ELoadFlags::LOAD_EditorOnly: return "EditorOnly";
	case ELoadFlags::LOAD_Throw: return "Throw/ResolvingDeferredExports";
		//case ELoadFlags::LOAD_ResolvingDeferredExports: return "ResolvingDeferredExports";
	case ELoadFlags::LOAD_Verify: return "Verify";
	case ELoadFlags::LOAD_AllowDll: return "AllowDll";
	case ELoadFlags::LOAD_DisallowFiles: return "DisallowFiles";
	case ELoadFlags::LOAD_NoVerify: return "NoVerify";
	case ELoadFlags::LOAD_IsVerifying: return "IsVerifying";
	case ELoadFlags::LOAD_Forgiving: return "Forgiving/DisableDependencyPreloading";
		//case ELoadFlags::LOAD_DisableDependencyPreloading: return "DisableDependencyPreloading";
	case ELoadFlags::LOAD_Quiet: return "Quiet";
	case ELoadFlags::LOAD_NoRemap: return "NoRemap/FindIfFail";
		//case ELoadFlags::LOAD_FindIfFail: return "FindIfFail";
	case ELoadFlags::LOAD_MemoryReader: return "MemoryReader";
	case ELoadFlags::LOAD_NoRedirects: return "NoRedirects";
	case ELoadFlags::LOAD_ForDiff: return "ForDiff";
	case ELoadFlags::LOAD_PackageForPIE: return "PackageForPIE";
	case ELoadFlags::LOAD_DeferDependencyLoads: return "DeferDependencyLoads";
	case ELoadFlags::LOAD_ForFileDiff: return "ForFileDiff";
	case ELoadFlags::LOAD_DisableCompileOnLoad: return "DisableCompileOnLoad";
		//case ELoadFlags::LOAD_Propagate: return "Propagate";
	}
	return MEFormat("0x%x", (dword)flag);
}

std::string StringFromEnum(EPackageFlags flag) {
	switch (flag) {
	case EPackageFlags::PKG_AllowDownload: return "AllowDownload/NewlyCreated";
		//case EPackageFlags::PKG_NewlyCreated: return "NewlyCreated";
	case EPackageFlags::PKG_ClientOptional: return "ClientOptional";
	case EPackageFlags::PKG_ServerSideOnly: return "ServerSideOnly";
	case EPackageFlags::PKG_BrokenLinks: return "BrokenLinks";
	case EPackageFlags::PKG_Unsecure: return "Unsecure/CompiledIn";
		//case EPackageFlags::PKG_CompiledIn: return "CompiledIn";
	case EPackageFlags::PKG_ForDiffing: return "ForDiffing";
	case EPackageFlags::PKG_EditorOnly: return "EditorOnly";
	case EPackageFlags::PKG_Developer: return "Developer";
	case EPackageFlags::PKG_ContainsMapData: return "ContainsMapData";
	case EPackageFlags::PKG_Need: return "Need";
	case EPackageFlags::PKG_Compiling: return "Compiling";
	case EPackageFlags::PKG_ContainsMap: return "ContainsMap";
	case EPackageFlags::PKG_RequiresLocalizationGather: return "RequiresLocalizationGather";
	case EPackageFlags::PKG_DisallowLazyLoading: return "DisallowLazyLoading";
	case EPackageFlags::PKG_PlayInEditor: return "PlayInEditor";
	case EPackageFlags::PKG_ContainsScript: return "ContainsScript";
	case EPackageFlags::PKG_ReloadingForCooker: return "ReloadingForCooker";
	case EPackageFlags::PKG_FilterEditorOnly: return "FilterEditorOnly";
	}
	return MEFormat("0x%x", (dword)flag);
}

std::string StringFromEnum(EClassFlags flag) {
	switch (flag) {

		/** @name Base flags */
		//@{
	case EClassFlags::CLASS_None: return "None";
		/** Class is abstract and can't be instantiated directly. */
	case EClassFlags::CLASS_Abstract: return "Abstract";
		/* Script has been compiled successfully. */
	case EClassFlags::CLASS_Compiled: return "Compiled/DefaultConfig";
		/** Save object configuration only to Default INIs, never to local INIs. Must be combined with CLASS_Config */
		//case EClassFlags::CLASS_DefaultConfig: return "DefaultConfig";
		/** Load object configuration at construction time. */
	case EClassFlags::CLASS_Config: return "Config";
		/** This object type can't be saved; null it out at save time. */
	case EClassFlags::CLASS_Transient: return "Transient";
		/** Successfully parsed. */
	case EClassFlags::CLASS_Parsed: return "Parsed";
		/** Class contains localized text. */
	case EClassFlags::CLASS_Localized: return "Localized";
		/*  Objects of this class can be safely replaced with default or NULL. */
	case EClassFlags::CLASS_SafeReplace: return "SafeReplace/AdvancedDisplay";

		/** All the properties on the class are shown in the advanced section (which is hidden by default) unless SimpleDisplay is specified on the property */
		//case EClassFlags::CLASS_AdvancedDisplay: return "AdvancedDisplay";

		/* Objects of this class are static during gameplay. */
	case EClassFlags::CLASS_RuntimeStatic: return "RuntimeStatic/Native";

		/** Class is a native class - native interfaces will have CLASS_Native set, but not RF_MarkAsNative */
		//case EClassFlags::CLASS_Native: return "Native";
		/** Don't export to C++ header. */
	case EClassFlags::CLASS_NoExport: return "NoExport";

		/*  Don't allow users to create in the editor. */
	case EClassFlags::CLASS_NoUserCreate: return "NoUserCreate/NotPlaceable";

		/** Do not allow users to create in the editor. */
		//case EClassFlags::CLASS_NotPlaceable: return "NotPlaceable";
		/** Handle object configuration on a per-object basis, rather than per-class. */
	case EClassFlags::CLASS_PerObjectConfig: return "PerObjectConfig";

		/**  Replication handled in C++. */
	case EClassFlags::CLASS_NativeReplication: return "NativeReplication";

		/** Class can be constructed from editinline New button. */
	case EClassFlags::CLASS_EditInlineNew: return "EditInlineNew";
		/** Display properties in the editor without using categories. */
	case EClassFlags::CLASS_CollapseCategories: return "CollapseCategories";
		/** Class is an interface **/
	case EClassFlags::CLASS_Interface: return "Interface";
		/**  Do not export a constructor for this class, assuming it is in the cpptext **/
	case EClassFlags::CLASS_CustomConstructor: return "CustomConstructor";
		/** all properties and functions in this class are const and should be exported as const */
	case EClassFlags::CLASS_Const: return "Const";

		/** Indicates that the class was created from blueprint source material */
	case EClassFlags::CLASS_CompiledFromBlueprint: return "CompiledFromBlueprint";

		/** Indicates that only the bare minimum bits of this class should be DLL exported/imported */
	case EClassFlags::CLASS_MinimalAPI: return "MinimalAPI";

		/** Indicates this class must be DLL exported/imported (along with all of it's members) */
	case EClassFlags::CLASS_RequiredAPI: return "RequiredAPI";

		/** Indicates that references to this class default to instanced. Used to be subclasses of UComponent, but now can be any UObject */
	case EClassFlags::CLASS_DefaultToInstanced: return "DefaultToInstanced";

		/** Indicates that the parent token stream has been merged with ours. */
	case EClassFlags::CLASS_TokenStreamAssembled: return "TokenStreamAssembled";
		/** Class has component properties. */
	case EClassFlags::CLASS_HasInstancedReference: return "HasInstancedReference";
		/** Don't show this class in the editor class browser or edit inline new menus. */
	case EClassFlags::CLASS_Hidden: return "Hidden";
		/** Don't save objects of this class when serializing */
	case EClassFlags::CLASS_Deprecated: return "Deprecated";
		/** Class not shown in editor drop down for class selection */
	case EClassFlags::CLASS_HideDropDown: return "HideDropDown";
		/** Class settings are saved to <AppData>/..../Blah.ini (as opposed to CLASS_DefaultConfig) */
	case EClassFlags::CLASS_GlobalUserConfig: return "GlobalUserConfig";
		/** Class was declared directly in C++ and has no boilerplate generated by UnrealHeaderTool */
	case EClassFlags::CLASS_Intrinsic: return "Intrinsic";
		/** Class has already been constructed (maybe in a previous DLL version before hot-reload). */
	case EClassFlags::CLASS_Constructed: return "Constructed";
		/** Indicates that object configuration will not check against ini base/defaults when serialized */
	case EClassFlags::CLASS_ConfigDoNotCheckDefaults: return "ConfigDoNotCheckDefaults";
		/** Class has been consigned to oblivion as part of a blueprint recompile, and a newer version currently exists. */
	case EClassFlags::CLASS_NewerVersionExists: return "NewerVersionExists";
	}
	return MEFormat("0x%x", (dword)flag);
}

std::string StringFromEnum(EPropertyFlags flag) {
	switch (flag) {
	case EPropertyFlags::CPF_Edit: return "Edit";
	case EPropertyFlags::CPF_ConstParm: return "ConstParm";
	case EPropertyFlags::CPF_Input: return "Input/BlueprintVisible";
		//case EPropertyFlags::CPF_BlueprintVisible: return "BlueprintVisible";
	case EPropertyFlags::CPF_ExportObject: return "ExportObject";
	case EPropertyFlags::CPF_OptionalParm: return "OptionalParm/BlueprintReadOnly";
		//case EPropertyFlags::CPF_BlueprintReadOnly: return "BlueprintReadOnly";
	case EPropertyFlags::CPF_Net: return "Net";
	case EPropertyFlags::CPF_ConstRef: return "ConstRef/EditFixedSize";
		//case EPropertyFlags::CPF_EditFixedSize: return "EditFixedSize";
	case EPropertyFlags::CPF_Parm: return "Parm";
	case EPropertyFlags::CPF_OutParm: return "OutParm";
	case EPropertyFlags::CPF_SkipParm: return "SkipParm/ZeroConstructor";
		//case EPropertyFlags::CPF_ZeroConstructor: return "ZeroConstructor";
	case EPropertyFlags::CPF_ReturnParm: return "ReturnParm";
	case EPropertyFlags::CPF_CoerceParm: return "CoerceParm/DisableEditOnTemplate";
		//case EPropertyFlags::CPF_DisableEditOnTemplate: return "DisableEditOnTemplate";
	case EPropertyFlags::CPF_Native: return "Native";
	case EPropertyFlags::CPF_Transient: return "Transient";
	case EPropertyFlags::CPF_Config: return "Config";
	case EPropertyFlags::CPF_Localized: return "Localized";
	case EPropertyFlags::CPF_Travel: return "Travel/DisableEditOnInstance";
		//case EPropertyFlags::CPF_DisableEditOnInstance: return "DisableEditOnInstance";
	case EPropertyFlags::CPF_EditConst: return "EditConst";
	case EPropertyFlags::CPF_GlobalConfig: return "GlobalConfig";
	case EPropertyFlags::CPF_InstancedReference: return "InstancedReference";
	case EPropertyFlags::CPF_OnDemand: return "OnDemand";
	case EPropertyFlags::CPF_New: return "New/DuplicateTransient";
		//case EPropertyFlags::CPF_DuplicateTransient: return "DuplicateTransient";
	case EPropertyFlags::CPF_NeedCtorLink: return "NeedCtorLink/SubobjectReference";
		//case EPropertyFlags::CPF_SubobjectReference: return "SubobjectReference";
	case EPropertyFlags::CPF_SaveGame: return "SaveGame";
	case EPropertyFlags::CPF_NoClear: return "NoClear";
	case EPropertyFlags::CPF_ReferenceParm: return "ReferenceParm";
	case EPropertyFlags::CPF_BlueprintAssignable: return "BlueprintAssignable";
	case EPropertyFlags::CPF_Deprecated: return "Deprecated";
	case EPropertyFlags::CPF_IsPlainOldData: return "IsPlainOldData";
	case EPropertyFlags::CPF_RepSkip: return "RepSkip";
	case EPropertyFlags::CPF_RepNotify: return "RepNotify";
	case EPropertyFlags::CPF_Interp: return "Interp";
	case EPropertyFlags::CPF_NonTransactional: return "NonTransactional";
	case EPropertyFlags::CPF_EditorOnly: return "EditorOnly";
	case EPropertyFlags::CPF_NoDestructor: return "NoDestructor";
	case EPropertyFlags::CPF_AutoWeak: return "AutoWeak";
	case EPropertyFlags::CPF_ContainsInstancedReference: return "ContainsInstancedReference";
	case EPropertyFlags::CPF_AssetRegistrySearchable: return "AssetRegistrySearchable";
	case EPropertyFlags::CPF_SimpleDisplay: return "SimpleDisplay";
	case EPropertyFlags::CPF_AdvancedDisplay: return "AdvancedDisplay";
	case EPropertyFlags::CPF_Protected: return "Protected";
	case EPropertyFlags::CPF_BlueprintCallable: return "BlueprintCallable";
	case EPropertyFlags::CPF_BlueprintAuthorityOnly: return "BlueprintAuthorityOnly";
	case EPropertyFlags::CPF_TextExportTransient: return "TextExportTransient";
	case EPropertyFlags::CPF_NonPIEDuplicateTransient: return "NonPIEDuplicateTransient";
	case EPropertyFlags::CPF_ExposeOnSpawn: return "ExposeOnSpawn";
	case EPropertyFlags::CPF_PersistentInstance: return "PersistentInstance";
	case EPropertyFlags::CPF_UObjectWrapper: return "UObjectWrapper";
	case EPropertyFlags::CPF_HasGetValueTypeHash: return "HasGetValueTypeHash";
	case EPropertyFlags::CPF_NativeAccessSpecifierPublic: return "NativeAccessSpecifierPublic";
	case EPropertyFlags::CPF_NativeAccessSpecifierProtected: return "NativeAccessSpecifierProtected";
	case EPropertyFlags::CPF_NativeAccessSpecifierPrivate: return "NativeAccessSpecifierPrivate";
	case EPropertyFlags::CPF_SkipSerialization: return "SkipSerialization";
	}
	return MEFormat("0x%" PRIx64, (qword)flag);
}

std::string StringFromEnum(EObjectFlags flag) {
	switch (flag) {
	case EObjectFlags::RF_NoFlags: return "NoFlags";
	case EObjectFlags::RF_Transactional: return "Transactional/PublicUE4";
		//case EObjectFlags::RF_PublicUE4: return "PublicUE4";
	case EObjectFlags::RF_Unreachable: return "Unreachable/StandaloneUE4";
		//case EObjectFlags::RF_StandaloneUE4: return "StandaloneUE4";
	case EObjectFlags::RF_Public: return "Public/MarkAsNativeUE4";
		//case EObjectFlags::RF_MarkAsNativeUE4: return "MarkAsNativeUE4";
	case EObjectFlags::RF_TagImp: return "TagImp/TransactionalUE4";
		//case EObjectFlags::RF_TransactionalUE4: return "TransactionalUE4";
	case EObjectFlags::RF_TagExp: return "TagExp/ClassDefaultObjectUE4";
		//case EObjectFlags::RF_ClassDefaultObjectUE4: return "ClassDefaultObjectUE4";
	case EObjectFlags::RF_SourceModified: return "SourceModified/ArchetypeObjectUE4";
		//case EObjectFlags::RF_ArchetypeObjectUE4: return "ArchetypeObjectUE4";
	case EObjectFlags::RF_TagGarbage: return "TagGarbage/TransientUE4";
		//case EObjectFlags::RF_TransientUE4: return "TransientUE4";
	case EObjectFlags::RF_MarkAsRootSetUE4: return "MarkAsRootSetUE4";
	case EObjectFlags::RF_TagGarbageTempUE4: return "TagGarbageTempUE4";
	case EObjectFlags::RF_NeedLoad: return "NeedLoad/NeedInitializationUE4";
		//case EObjectFlags::RF_NeedInitializationUE4: return "NeedInitializationUE4";
	case EObjectFlags::RF_HighlightedName: return "HighlightedName/EliminateObject/NeedLoadUE4";
		//case EObjectFlags::RF_EliminateObject: return "EliminateObject";
		//case EObjectFlags::RF_NeedLoadUE4: return "NeedLoadUE4";
	case EObjectFlags::RF_InSingularFunc: return "InSingularFunc/RemappedName/KeepForCookerUE4";
		//case EObjectFlags::RF_RemappedName: return "RemappedName";
		//case EObjectFlags::RF_KeepForCookerUE4: return "KeepForCookerUE4";
	case EObjectFlags::RF_Suppress: return "Suppress/StateChanged/RF_NeedPostLoadUE4";
		//case EObjectFlags::RF_StateChanged: return "StateChanged";
		//case EObjectFlags::RF_NeedPostLoadUE4: return "NeedPostLoadUE4";
	case EObjectFlags::RF_InEndState: return "InEndState/NeedPostLoadSubobjectsUE4";
		//case EObjectFlags::RF_NeedPostLoadSubobjectsUE4: return "NeedPostLoadSubobjectsUE4";
	case EObjectFlags::RF_Transient: return "Transient/NewerVersionExistsUE4";
		//case EObjectFlags::RF_NewerVersionExistsUE4: return "NewerVersionExistsUE4";
	case EObjectFlags::RF_Preloading: return "Preloading/BeginDestroyedUE4";
		//case EObjectFlags::RF_BeginDestroyedUE4: return "BeginDestroyedUE4";
	case EObjectFlags::RF_LoadForClient: return "LoadForClient/FinishDestroyedUE4";
		//case EObjectFlags::RF_FinishDestroyedUE4: return "FinishDestroyedUE4";
	case EObjectFlags::RF_LoadForServer: return "LoadForServer/BeingRegeneratedUE4";
		//case EObjectFlags::RF_BeingRegeneratedUE4: return "BeingRegeneratedUE4";
	case EObjectFlags::RF_LoadForEdit: return "LoadForEdit/DefaultSubObjectUE4";
		//case EObjectFlags::RF_DefaultSubObjectUE4: return "DefaultSubObjectUE4";
	case EObjectFlags::RF_Standalone: return "Standalone";
	case EObjectFlags::RF_NotForClient: return "NotForClient";
	case EObjectFlags::RF_NotForServer: return "NotForServer";
	case EObjectFlags::RF_NotForEdit: return "NotForEdit";
	case EObjectFlags::RF_Destroyed: return "Destroyed/WasLoadedUE4";
		//case EObjectFlags::RF_WasLoadedUE4: return "WasLoadedUE4";
	case EObjectFlags::RF_NeedPostLoad: return "NeedPostLoad/TextExportTransientUE4";
		//case EObjectFlags::RF_TextExportTransientUE4: return "TextExportTransientUE4";
	case EObjectFlags::RF_HasStack: return "HasStack/LoadCompletedUE4";
		//case EObjectFlags::RF_LoadCompletedUE4: return "LoadCompletedUE4";
	case EObjectFlags::RF_Native: return "Native/InheritableComponentTemplateUE4";
		//case EObjectFlags::RF_InheritableComponentTemplateUE4: return "InheritableComponentTemplateUE4";
	case EObjectFlags::RF_Marked: return "Marked/DuplicateTransientUE4";
		//case EObjectFlags::RF_DuplicateTransientUE4: return "DuplicateTransientUE4";
	case EObjectFlags::RF_ErrorShutdown: return "ErrorShutdown/StrongRefOnFrameUE4";
		//case EObjectFlags::RF_StrongRefOnFrameUE4: return "StrongRefOnFrameUE4";
	case EObjectFlags::RF_DebugPostLoad: return "DebugPostLoad/NonPIEDuplicateTransientUE4";
		//case EObjectFlags::RF_NonPIEDuplicateTransientUE4: return "NonPIEDuplicateTransientUE4";
	case EObjectFlags::RF_DebugSerialize: return "DebugSerialize/DynamicUE4";
		//case EObjectFlags::RF_DynamicUE4: return "DynamicUE4";
	case EObjectFlags::RF_DebugDestroy: return "DebugDestroy";
	}
	return MEFormat("0x%" PRIx64, (qword)flag);
}

std::string StringFromEnum(EFunctionFlags flag) {
	switch (flag) {
	case EFunctionFlags::FUNC_None: return "None";
	case EFunctionFlags::FUNC_Final: return "Final";
	case EFunctionFlags::FUNC_RequiredAPI: return "RequiredAPI";
	case EFunctionFlags::FUNC_BlueprintAuthorityOnly: return "BlueprintAuthorityOnly";
	case EFunctionFlags::FUNC_BlueprintCosmetic: return "BlueprintCosmetic";
	case EFunctionFlags::FUNC_Net: return "Net";
	case EFunctionFlags::FUNC_NetReliable: return "NetReliable";
	case EFunctionFlags::FUNC_NetRequest: return "NetRequest";
	case EFunctionFlags::FUNC_Exec: return "Exec";
	case EFunctionFlags::FUNC_Native: return "Native";
	case EFunctionFlags::FUNC_Event: return "Event";
	case EFunctionFlags::FUNC_NetResponse: return "NetResponse";
	case EFunctionFlags::FUNC_Static: return "Static";
	case EFunctionFlags::FUNC_NetMulticast: return "NetMulticast";
	case EFunctionFlags::FUNC_MulticastDelegate: return "MulticastDelegate";
	case EFunctionFlags::FUNC_Public: return "Public";
	case EFunctionFlags::FUNC_Private: return "Private";
	case EFunctionFlags::FUNC_Protected: return "Protected";
	case EFunctionFlags::FUNC_Delegate: return "Delegate";
	case EFunctionFlags::FUNC_NetServer: return "NetServer";
	case EFunctionFlags::FUNC_HasOutParms: return "HasOutParms";
	case EFunctionFlags::FUNC_HasDefaults: return "HasDefaults";
	case EFunctionFlags::FUNC_NetClient: return "NetClient";
	case EFunctionFlags::FUNC_DLLImport: return "DLLImport";
	case EFunctionFlags::FUNC_BlueprintCallable: return "BlueprintCallable";
	case EFunctionFlags::FUNC_BlueprintEvent: return "BlueprintEvent";
	case EFunctionFlags::FUNC_BlueprintPure: return "BlueprintPure";
	case EFunctionFlags::FUNC_EditorOnly: return "EditorOnly";
	case EFunctionFlags::FUNC_Const: return "Const";
	case EFunctionFlags::FUNC_NetValidate: return "NetValidate";
	}
	return MEFormat("0x%x", (dword)flag);
}

