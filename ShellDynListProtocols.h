/** @file

  Copyright (c) 2022, Peter Kirmeier <topeterk@users.noreply.github.com>. All rights reserved.

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef __SHELL_DYN_LIST_PROTOCOLS_H__
#define __SHELL_DYN_LIST_PROTOCOLS_H__

#include <Uefi.h>

#include <Protocol/ShellDynamicCommand.h>

#include <Library/UefiLib.h> // Print()
#include <Library/HiiLib.h>
#include <Library/DebugLib.h>

/**
This is the shell command "lp" handler function. This function handles
the command when it is invoked in the shell.

@param[in]  This             The instance of the EFI_SHELL_DYNAMIC_COMMAND_PROTOCOL.
@param[in]  SystemTable      The pointer to the UEFI system table.
@param[in]  ShellParameters  The parameters associated with the command.
@param[in]  Shell            The instance of the shell protocol used in the context of processing this command.

@return  SHELL_SUCCESS            The operation was successful.
@return  SHELL_ABORTED            Operation aborted due to internal error.

**/
SHELL_STATUS
EFIAPI
ShellDynCmdProtocolLpHandler(
    IN EFI_SHELL_DYNAMIC_COMMAND_PROTOCOL  *This,
    IN EFI_SYSTEM_TABLE                    *SystemTable,
    IN EFI_SHELL_PARAMETERS_PROTOCOL       *ShellParameters,
    IN EFI_SHELL_PROTOCOL                  *Shell
    );

/**
This is the shell command "lp" help handler function. This
function returns the formatted help for the "lp" command.
The format matchs that in Appendix B of the revision 2.1 of the
UEFI Shell Specification.

@param[in]  This      The instance of the EFI_SHELL_DYNAMIC_COMMAND_PROTOCOL.
@param[in]  Language  The pointer to the language string to use.

@return  CHAR16*  Pool allocated help string, must be freed by caller.
**/
CHAR16*
EFIAPI
ShellDynCmdProtocolLpGetHelp(
    IN EFI_SHELL_DYNAMIC_COMMAND_PROTOCOL  *This,
    IN CONST CHAR8                         *Language
    );

#endif /* __SHELL_DYN_LIST_PROTOCOLS_H__ */
