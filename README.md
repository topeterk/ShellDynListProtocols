
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

## Installation
The shell command must be compiled for the specific target system.

### Systemrequirements
This source is based [EDKII](https://github.com/tianocore/edk2) which is required to build this shell command.

### How to integrate into EDKII
It is recommended to place the software at **ShellPkg/DynamicCommand/ShellDynListProtocols/** within the EDKII source.
Add this to your DSC file like _ShellPkg.dsc_ or _Nt32.dsc_ under the **[Components]** section:
>&nbsp;&nbsp;ShellPkg/DynamicCommand/ShellDynListProtocols/ShellDynListProtocols.inf

### Visual Studio debugging using NT32 Emulator
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