
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
It is recommended to place the software at **ShellPkg/Application/ShellDynListProtocols/** within the EDKII source.  
This allows using one of those examples building with _Shell_ or _Nt32_ package..

#### Building with Shell package
Add this to you _ShellPkg.dsc_:
>&nbsp;&nbsp;ShellPkg/Application/ShellDynListProtocols/ShellDynListProtocols.inf {  
>&nbsp;&nbsp;&nbsp;&nbsp;\<LibraryClasses\>  
>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;UefiDriverEntryPoint\|MdePkg/Library/UefiDriverEntryPoint/UefiDriverEntryPoint.inf  
>&nbsp;&nbsp;}

#### Building with NT32 package
Add this to you _Nt32.dsc_:
>&nbsp;&nbsp;ShellPkg/Application/ShellDynListProtocols/ShellDynListProtocols.inf
  
  
  
> Praise the sun!  :sunny: . . . :fire: . . .  :running: :dash: 