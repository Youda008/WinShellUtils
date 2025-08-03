#include <tchar.h>
#include <shlobj.h>        // SHGetKnownFolderPath  (link library Shell32.lib or uuid)
#include <KnownFolders.h>  // FOLDERID_SavedGames   (link library Shell32.lib or uuid)
#include <combaseapi.h>    // CoTaskMemFree         (link library Ole32.lib  or ole32)

#include <map>
#include <string_view>
#include <cstdio>

#ifdef UNICODE
	using tstring = std::wstring;
	using tstring_view = std::wstring_view;
	#define ftprintf fwprintf
#else
	using tstring = std::string;
	using tstring_view = std::string_view;
	#define ftprintf fprintf
#endif


static const std::map< tstring_view, const KNOWNFOLDERID * > knownFolderIDs =
{
	{ _T("AccountPictures"), &FOLDERID_AccountPictures },
	{ _T("AddNewPrograms"), &FOLDERID_AddNewPrograms },
	{ _T("AdminTools"), &FOLDERID_AdminTools },
	{ _T("AllAppMods"), &FOLDERID_AllAppMods },
	{ _T("AppCaptures"), &FOLDERID_AppCaptures },
	{ _T("AppDataDesktop"), &FOLDERID_AppDataDesktop },
	{ _T("AppDataDocuments"), &FOLDERID_AppDataDocuments },
	{ _T("AppDataFavorites"), &FOLDERID_AppDataFavorites },
	{ _T("AppDataProgramData"), &FOLDERID_AppDataProgramData },
	{ _T("AppsFolder"), &FOLDERID_AppsFolder },
	{ _T("ApplicationShortcuts"), &FOLDERID_ApplicationShortcuts },
	{ _T("AppUpdates"), &FOLDERID_AppUpdates },
	{ _T("CameraRoll"), &FOLDERID_CameraRoll },
	{ _T("CameraRollLibrary"), &FOLDERID_CameraRollLibrary },
	{ _T("CDBurning"), &FOLDERID_CDBurning },
	{ _T("ChangeRemovePrograms"), &FOLDERID_ChangeRemovePrograms },
	{ _T("CommonAdminTools"), &FOLDERID_CommonAdminTools },
	{ _T("CommonOEMLinks"), &FOLDERID_CommonOEMLinks },
	{ _T("CommonPrograms"), &FOLDERID_CommonPrograms },
	{ _T("CommonStartMenu"), &FOLDERID_CommonStartMenu },
	{ _T("CommonStartMenuPlaces"), &FOLDERID_CommonStartMenuPlaces },
	{ _T("CommonStartup"), &FOLDERID_CommonStartup },
	{ _T("CommonTemplates"), &FOLDERID_CommonTemplates },
	{ _T("ComputerFolder"), &FOLDERID_ComputerFolder },
	{ _T("ConflictFolder"), &FOLDERID_ConflictFolder },
	{ _T("ConnectionsFolder"), &FOLDERID_ConnectionsFolder },
	{ _T("Contacts"), &FOLDERID_Contacts },
	{ _T("ControlPanelFolder"), &FOLDERID_ControlPanelFolder },
	{ _T("Cookies"), &FOLDERID_Cookies },
	{ _T("CurrentAppMods"), &FOLDERID_CurrentAppMods },
	{ _T("Desktop"), &FOLDERID_Desktop },
	{ _T("DevelopmentFiles"), &FOLDERID_DevelopmentFiles },
	{ _T("Device"), &FOLDERID_Device },
	{ _T("DeviceMetadataStore"), &FOLDERID_DeviceMetadataStore },
	{ _T("Documents"), &FOLDERID_Documents },
	{ _T("DocumentsLibrary"), &FOLDERID_DocumentsLibrary },
	{ _T("Downloads"), &FOLDERID_Downloads },
	{ _T("Favorites"), &FOLDERID_Favorites },
	{ _T("Fonts"), &FOLDERID_Fonts },
	{ _T("Games"), &FOLDERID_Games },
	{ _T("GameTasks"), &FOLDERID_GameTasks },
	{ _T("History"), &FOLDERID_History },
	{ _T("HomeGroup"), &FOLDERID_HomeGroup },
	{ _T("HomeGroupCurrentUser"), &FOLDERID_HomeGroupCurrentUser },
	{ _T("ImplicitAppShortcuts"), &FOLDERID_ImplicitAppShortcuts },
	{ _T("InternetCache"), &FOLDERID_InternetCache },
	{ _T("InternetFolder"), &FOLDERID_InternetFolder },
	{ _T("Libraries"), &FOLDERID_Libraries },
	{ _T("Links"), &FOLDERID_Links },
	{ _T("LocalAppData"), &FOLDERID_LocalAppData },
	{ _T("LocalAppDataLow"), &FOLDERID_LocalAppDataLow },
	{ _T("LocalDocuments"), &FOLDERID_LocalDocuments },
	{ _T("LocalDownloads"), &FOLDERID_LocalDownloads },
	{ _T("LocalizedResourcesDir"), &FOLDERID_LocalizedResourcesDir },
	{ _T("LocalMusic"), &FOLDERID_LocalMusic },
	{ _T("LocalPictures"), &FOLDERID_LocalPictures },
	{ _T("LocalStorage"), &FOLDERID_LocalStorage },
	{ _T("LocalVideos"), &FOLDERID_LocalVideos },
	{ _T("Music"), &FOLDERID_Music },
	{ _T("MusicLibrary"), &FOLDERID_MusicLibrary },
	{ _T("NetHood"), &FOLDERID_NetHood },
	{ _T("NetworkFolder"), &FOLDERID_NetworkFolder },
	{ _T("Objects3D"), &FOLDERID_Objects3D },
	{ _T("OneDrive"), &FOLDERID_OneDrive },
	{ _T("OriginalImages"), &FOLDERID_OriginalImages },
	{ _T("PhotoAlbums"), &FOLDERID_PhotoAlbums },
	{ _T("Pictures"), &FOLDERID_Pictures },
	{ _T("PicturesLibrary"), &FOLDERID_PicturesLibrary },
	{ _T("Playlists"), &FOLDERID_Playlists },
	{ _T("PrintHood"), &FOLDERID_PrintHood },
	{ _T("PrintersFolder"), &FOLDERID_PrintersFolder },
	{ _T("Profile"), &FOLDERID_Profile },
	{ _T("ProgramData"), &FOLDERID_ProgramData },
	{ _T("ProgramFiles"), &FOLDERID_ProgramFiles },
	{ _T("ProgramFilesX64"), &FOLDERID_ProgramFilesX64 },
	{ _T("ProgramFilesX86"), &FOLDERID_ProgramFilesX86 },
	{ _T("ProgramFilesCommon"), &FOLDERID_ProgramFilesCommon },
	{ _T("ProgramFilesCommonX64"), &FOLDERID_ProgramFilesCommonX64 },
	{ _T("ProgramFilesCommonX86"), &FOLDERID_ProgramFilesCommonX86 },
	{ _T("Programs"), &FOLDERID_Programs },
	{ _T("Public"), &FOLDERID_Public },
	{ _T("PublicDesktop"), &FOLDERID_PublicDesktop },
	{ _T("PublicDocuments"), &FOLDERID_PublicDocuments },
	{ _T("PublicDownloads"), &FOLDERID_PublicDownloads },
	{ _T("PublicGameTasks"), &FOLDERID_PublicGameTasks },
	{ _T("PublicLibraries"), &FOLDERID_PublicLibraries },
	{ _T("PublicMusic"), &FOLDERID_PublicMusic },
	{ _T("PublicPictures"), &FOLDERID_PublicPictures },
	{ _T("PublicRingtones"), &FOLDERID_PublicRingtones },
	{ _T("PublicUserTiles"), &FOLDERID_PublicUserTiles },
	{ _T("PublicVideos"), &FOLDERID_PublicVideos },
	{ _T("QuickLaunch"), &FOLDERID_QuickLaunch },
	{ _T("Recent"), &FOLDERID_Recent },
	{ _T("RecordedCalls"), &FOLDERID_RecordedCalls },
	{ _T("RecordedTVLibrary"), &FOLDERID_RecordedTVLibrary },
	{ _T("RecycleBinFolder"), &FOLDERID_RecycleBinFolder },
	{ _T("ResourceDir"), &FOLDERID_ResourceDir },
	{ _T("RetailDemo"), &FOLDERID_RetailDemo },
	{ _T("Ringtones"), &FOLDERID_Ringtones },
	{ _T("RoamingAppData"), &FOLDERID_RoamingAppData },
	{ _T("RoamingTiles"), &FOLDERID_RoamingTiles },
	{ _T("RoamedTileImages"), &FOLDERID_RoamedTileImages },
	{ _T("SampleMusic"), &FOLDERID_SampleMusic },
	{ _T("SamplePictures"), &FOLDERID_SamplePictures },
	{ _T("SamplePlaylists"), &FOLDERID_SamplePlaylists },
	{ _T("SampleVideos"), &FOLDERID_SampleVideos },
	{ _T("SavedGames"), &FOLDERID_SavedGames },
	{ _T("SavedPictures"), &FOLDERID_SavedPictures },
	{ _T("SavedPicturesLibrary"), &FOLDERID_SavedPicturesLibrary },
	{ _T("SavedSearches"), &FOLDERID_SavedSearches },
	{ _T("Screenshots"), &FOLDERID_Screenshots },
	{ _T("SEARCH_MAPI"), &FOLDERID_SEARCH_MAPI },
	{ _T("SEARCH_CSC"), &FOLDERID_SEARCH_CSC },
	{ _T("SearchHistory"), &FOLDERID_SearchHistory },
	{ _T("SearchHome"), &FOLDERID_SearchHome },
	{ _T("SearchTemplates"), &FOLDERID_SearchTemplates },
	{ _T("SendTo"), &FOLDERID_SendTo },
	{ _T("SidebarDefaultParts"), &FOLDERID_SidebarDefaultParts },
	{ _T("SidebarParts"), &FOLDERID_SidebarParts },
	{ _T("SkyDrive"), &FOLDERID_SkyDrive },
	{ _T("SkyDriveCameraRoll"), &FOLDERID_SkyDriveCameraRoll },
	{ _T("SkyDriveDocuments"), &FOLDERID_SkyDriveDocuments },
	{ _T("SkyDriveMusic"), &FOLDERID_SkyDriveMusic },
	{ _T("SkyDrivePictures"), &FOLDERID_SkyDrivePictures },
	{ _T("StartMenu"), &FOLDERID_StartMenu },
	{ _T("StartMenuAllPrograms"), &FOLDERID_StartMenuAllPrograms },
	{ _T("Startup"), &FOLDERID_Startup },
	{ _T("SyncManagerFolder"), &FOLDERID_SyncManagerFolder },
	{ _T("SyncResultsFolder"), &FOLDERID_SyncResultsFolder },
	{ _T("SyncSetupFolder"), &FOLDERID_SyncSetupFolder },
	{ _T("System"), &FOLDERID_System },
	{ _T("SystemX86"), &FOLDERID_SystemX86 },
	{ _T("Templates"), &FOLDERID_Templates },
	{ _T("UserPinned"), &FOLDERID_UserPinned },
	{ _T("UserProfiles"), &FOLDERID_UserProfiles },
	{ _T("UserProgramFiles"), &FOLDERID_UserProgramFiles },
	{ _T("UserProgramFilesCommon"), &FOLDERID_UserProgramFilesCommon },
	{ _T("UsersFiles"), &FOLDERID_UsersFiles },
	{ _T("UsersLibraries"), &FOLDERID_UsersLibraries },
	{ _T("Videos"), &FOLDERID_Videos },
	{ _T("VideosLibrary"), &FOLDERID_VideosLibrary },
	{ _T("Windows"), &FOLDERID_Windows },
};

static void printFolderNames( FILE * out )
{
	for (const auto & [name, id] : knownFolderIDs)
	{
		ftprintf( out, _T("%s\n"), name.data() );
	}
}

static void printHelp( FILE * out, const TCHAR * arg0 )
{
	ftprintf( out, _T("usage: %s {folder_name}\n"), arg0 );
	ftprintf( out, _T("to show possible folder names use: %s /list\n"), arg0 );
}

int _tmain( int argc, _TCHAR * argv [] )
{
	if (argc != 2)
	{
		printHelp( stderr, argv[0] );
		return 1;
	}

	tstring_view arg1( argv[1] );

	if (arg1 == _T("/?") || arg1 == _T("/help") || arg1 == _T("-h") || arg1 == _T("--help"))
	{
		printHelp( stdout, argv[0] );
		return 0;
	}
	else if (arg1 == _T("/list") || arg1 == _T("--list"))
	{
		printFolderNames( stdout );
		return 0;
	}
	else
	{
		tstring_view folderName = arg1;

		auto iter = knownFolderIDs.find( folderName );
		if (iter == knownFolderIDs.end())
		{
			ftprintf( stderr, _T("unrecognized folder name: %s\n"), folderName.data() );
			ftprintf( stderr, _T("\npossible folder names:\n"), folderName.data() );
			printFolderNames( stderr );
			return 2;
		}

		PTSTR knownFolderPath = nullptr;
		HRESULT hr = SHGetKnownFolderPath( *iter->second, 0, NULL, &knownFolderPath );
		if (!SUCCEEDED(hr))
		{
			ftprintf( stderr, _T("SHGetKnownFolderPath( %s ) failed: error = ld%\n"), folderName.data(), hr );
			return 3;
		}

		ftprintf( stdout, _T("%s"), knownFolderPath );

		CoTaskMemFree( knownFolderPath );

		return 0;
	}
}
