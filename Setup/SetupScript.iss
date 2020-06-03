[Setup]
AppName=DrumSampler
AppVersion=1.0.0
DefaultDirName={autocf}\{#SetupSetting("AppName")}
DefaultGroupName={#SetupSetting("AppName")}
OutputBaseFilename={#SetupSetting("AppName")}-windows
DisableWelcomePage=no
UsePreviousAppDir=no 
[Files]
Source: "..\..\Builds\VisualStudio2017\x64\Release\VST3\DrumSampler.vst3"; DestDir: "{app}\Steinberg\VST3"; BeforeInstall: WriteFolderPath()
Source: "DrumSamples\*"; DestDir: "{app}\Samples"; Flags: recursesubdirs
Source: "MidiMapping.ini"; DestDir: "{app}";
[Code]
var
    destPath: String;
    appName: String;
procedure WriteFolderPath();
begin
  appName := '{#SetupSetting("AppName")}'; 
  destPath := ExpandConstant('{userappdata}\')+ appName ;
  Log('Writing the chosen folder path to ' + destPath);
  CreateDir(destPath);
  if SaveStringToFile( destPath + '\installPath', ExpandConstant('{app}'), False) then
    Log('RETURNED TRUE')
  else
    Log('RETURNED FALSE');
end;