
  # UEFI EDKII Dynamic Shell Extension **List Protocols**

UEFI EDKII Shell command that prints all available protocols grouped by their registered handles.  
  
## Features
This shell command (UEFI driver) can be loaded (e.g. by a shell startup script) directly into the shell with the **load** command:  
> load _ShellDynListProtocols.efi_

Once done, the command connects with the shell's internal **help**:  
> help lp

To actually run the shell command just execute it without command line options:
> lp

## Get the software
There are no special releases available yet. Just go ahead and get latest source.

## How to build
The shell command must be compiled for the specific target system.

### Systemrequirements
This source is based [EDKII](https://github.com/tianocore/edk2) which is required to build this shell command.

### How to integrate into EDKII
It is recommended to place the software at **ShellPkg/DynamicCommand/ShellDynListProtocols/** within the EDKII source.
Add this to your DSC file like _ShellPkg.dsc_ , _EmulatorPkg.dsc_ or _Nt32.dsc_ under the **[Components]** section:
>&nbsp;&nbsp;ShellPkg/DynamicCommand/ShellDynListProtocols/ShellDynListProtocols.inf

:bangbang: On newer EDKII versions some checks are executed, e.g. EccCheck which failed on my environment as I just inserted the whole git repository.
To mitigate this, I think, one either have to add the repository as a submodule or as quick fix just delete the .git folder.
> PermissionError: [WinError 5] Access is denied: '<path>\\Build\\.pytool\\Plugin\\EccCheck\\ShellPkg\\DynamicCommand\\ShellDynListProtocols\\.git\\objects\\pack\\pack-8b7c25379d5d814f491759643322eb93e76116dd.idx'

### How to build (ShellPgk.dsc)

:bangbang: This was done in 2026 using VS2022 at EDKII commit 0049ac1793c4abd0652652286e5506f52aaaa0d4.

:bangbang: The instructions are not complete, please refert to EDKII documentation for details.
Use these steps just as a toplevel guideline of the major steps.

Get source and create python environment.

```batchfile
git clone https://github.com/tianocore/edk2.git
cd edk2
git submodule update --init
py -m venv .venv
.venv\Scripts\activate.bat
pip install -r pip-requirements.txt --upgrade
```
Copy source to directory and integrate it into the build, see "How to integrate into EDKII".
Not sure if this step is actually needed:

```batchfile
.venv\Scripts\activate.bat
stuart_setup -c .pytool/CISettings.py
python BaseTools/Edk2ToolsBuild.py
```

Run the actual build, like so:

```batchfile
stuart_ci_build -c .pytool/CISettings.py -p ShellPkg -a IA32,X64 TOOL_CHAIN_TAG=VS2022
```

Output files are at this location:  
`Build\Shell\<debug/release>_<toolchain>\<arch>\ShellPkg\DynamicCommand\ShellDynListProtocols\ShellDynListProtocols\OUTPUT\ShellDynListProtocols.efi`
> debug/release = e.g. RELEASE  
> toolchain = e.g. VS2022  
> arch = e.g. X64

On errors about pythonXXXt.lib not found, one might need to install Python including the free-threaded binaries.

To resolve uncrustify errors, run this command for the failing file, as here for _ShellDynListProtocols.c_ :
```batchfile
echo ShellPkg\DynamicCommand\ShellDynListProtocols\ShellDynListProtocols.c | .\.pytool\Plugin\UncrustifyCheck\tianocore-uncrustify-release_extdep\Windows-x86\uncrustify.exe -c .\.pytool\Plugin\UncrustifyCheck\uncrustify.cfg -F - --replace --no-backup --if-changed
```

### Visual Studio debugging using NT32 Emulator (Nt32.dsc)

:bangbang: This is kept here for use with old EDKII version as Nt32 package was removed.
It might be adapted to EmulatorPkg, but I personally never build the emulator since 2022.

To debug drivers you have to make sure Visual Studio can detect the loaded driver and load the PDB file and addresses properly.  
Add this to your DSC file under the **[BuildOptions]** section or create the section when it is not available:  
>&nbsp;&nbsp;DEBUG_\*_\*_DLINK_FLAGS = /EXPORT:InitializeDriver=$(IMAGE_ENTRY_POINT) /BASE:0x10000 /ALIGN:4096 /FILEALIGN:4096 /SUBSYSTEM:CONSOLE

Further it is recommended to have easier access to the driver within the emulator by mounting the target directory.  
This can be done by modifying the PCD that is responsible for the mapped drives in _Nt32.dsc_.  
The path must be added, let's say as third mapping to be mapped to fs2, and the size of the string must be increased like that:  
>BEFORE  
>&nbsp;&nbsp;gEfiNt32PkgTokenSpaceGuid.PcdWinNtFileSystem|L".!..\..\..\..\EdkShellBinPkg\Bin\Ia32\Apps"|VOID*|106  
>AFTER  
>&nbsp;&nbsp;gEfiNt32PkgTokenSpaceGuid.PcdWinNtFileSystem|L".!..\..\..\..\EdkShellBinPkg\Bin\Ia32\Apps!..\..\..\Shell\DEBUG_VS2015x86\IA32"|VOID*|256

Moreover it is recommended to have a **startup.nsh** next to _SecMain.exe_ to enter the build directoy immediately at start where the built EFI executable is located:  
>fs2:  

One can also add a further line to directly start the command automatically by adding this next command:  
>load ShellDynListProtocols.efi  
>lp

  
  
  
> Praise the sun!  :sunny: . . . :fire: . . .  :running: :dash: 
