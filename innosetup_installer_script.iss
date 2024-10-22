; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "BuzzBot"
#define MyAppVersion "2.5.0"
#define MyAppURL "www.github.com/minorsecond/BuzzBot"
#define MyAppExeName "BuzzBot.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application. Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{A5E7C39F-562E-4BE8-813C-0292778B294E}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={autopf}\{#MyAppName}
DisableProgramGroupPage=yes
; Uncomment the following line to run in non administrative install mode (install for current user only.)
;PrivilegesRequired=lowest
OutputDir=C:\Users\rossw\CLionProjects\BuzzBot\cmake-build-release
OutputBaseFilename=BuzzBot-Installer
Compression=lzma
SolidCompression=yes
WizardStyle=modern

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "C:\Users\rossw\CLionProjects\BuzzBot\cmake-build-release\{#MyAppExeName}"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\msys64\mingw64\bin\libsqlite3-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\msys64\mingw64\bin\Qt6Core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\msys64\mingw64\bin\Qt6Gui.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\msys64\mingw64\bin\Qt6PrintSupport.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\msys64\mingw64\bin\Qt6Widgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\msys64\mingw64\bin\libb2-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\msys64\mingw64\bin\libdouble-conversion.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\msys64\mingw64\bin\libicuin72.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\msys64\mingw64\bin\libpcre2-16-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\msys64\mingw64\bin\zlib1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\msys64\mingw64\bin\libfreetype-6.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\msys64\mingw64\bin\libharfbuzz-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\msys64\mingw64\bin\libmd4c.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\msys64\mingw64\bin\libpng16-16.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\msys64\mingw64\bin\libbz2-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\msys64\mingw64\bin\libbrotlidec.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\msys64\mingw64\bin\libicudt72.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\msys64\mingw64\bin\libicuuc72.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\msys64\mingw64\bin\libglib-2.0-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\msys64\mingw64\bin\libsqlite3-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\msys64\mingw64\bin\libgraphite2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\msys64\mingw64\bin\libintl-8.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\msys64\mingw64\bin\libbrotlicommon.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\msys64\mingw64\bin\libpcre2-8-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\msys64\mingw64\bin\libiconv-2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\msys64\mingw64\bin\libgcc_s_seh-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\msys64\mingw64\bin\libstdc++-6.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\msys64\mingw64\bin\libwinpthread-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\rossw\CLionProjects\BuzzBot\cmake-build-release\res\*"; DestDir: "{app}\res\"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:\Users\rossw\CLionProjects\BuzzBot\cmake-build-release\styles\*"; DestDir: "{app}\styles\"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:\Users\rossw\CLionProjects\BuzzBot\cmake-build-release\platforms\*"; DestDir: "{app}\platforms\"; Flags: ignoreversion recursesubdirs createallsubdirs
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{autoprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; IconFilename: "{app}\res\windows_icon.ico"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon; IconFilename: "{app}\res\windows_icon.ico"

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

