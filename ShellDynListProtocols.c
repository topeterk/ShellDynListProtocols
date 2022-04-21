/** @file

  Copyright (c) 2022, Peter Kirmeier <topeterk@users.noreply.github.com>. All rights reserved.

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "ShellDynListProtocols.h"

/**
  GUID definitions
**/
STATIC CONST EFI_GUID mShellDynListProtocolsHiiGuid = { 0X4AC75E15, 0X5DF5, 0X4F57,{ 0XAA, 0X08, 0X06, 0XD8, 0XB4, 0XB0, 0X5D, 0X1D } };

/**
  Local variables
**/
STATIC CONST EFI_SHELL_DYNAMIC_COMMAND_PROTOCOL mShellDynCmdProtocolLp = {
    L"lp",                        // Name of the command = list protocols
    ShellDynCmdProtocolLpHandler, // Handler
    ShellDynCmdProtocolLpGetHelp  // GetHelp
};

STATIC EFI_HANDLE mShellDynListProtocolsHiiHandle;

/**
  Main entry point of the dynamic Shell extension driver.

  @param[in]  ImageHandle   The firmware allocated handle for the present driver UEFI image.
  @param[in]  *SystemTable  A pointer to the EFI System table.

  @retval  EFI_SUCCESS           The driver was initialized.
  @retval  EFI_OUT_OF_RESOURCES  The "End of DXE" event could not be allocated or
                                 there was not enough memory in pool to install
                                 the Shell Dynamic Command protocol.
  @retval  EFI_LOAD_ERROR        Unable to add the HII package.

**/
EFI_STATUS
ShellDynListProtocolsEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
    EFI_BOOT_SERVICES * pBS = SystemTable->BootServices;
    EFI_STATUS  Status;
    EFI_HANDLE  Handle;

    DEBUG((EFI_D_INFO, "ShellDynListProtocolsEntryPoint()\n"));

    mShellDynListProtocolsHiiHandle = HiiAddPackages (
                                        &mShellDynListProtocolsHiiGuid,
                                        ImageHandle,
                                        ShellDynListProtocolsStrings,
                                        NULL
                                        );
    if (NULL == mShellDynListProtocolsHiiHandle)
    {
        DEBUG((EFI_D_ERROR, "Loading language failed\n"));
        return EFI_LOAD_ERROR;
    }

    Handle = NULL; // let's create a new handle
    Status = pBS->InstallMultipleProtocolInterfaces (
                    &Handle,
                    &gEfiShellDynamicCommandProtocolGuid,
                    &mShellDynCmdProtocolLp,
                    NULL
                    );
    if (EFI_ERROR (Status))
    {
        DEBUG((EFI_D_WARN, "Unable to install \"lp\" EFI Shell command - %r \n", Status));
        HiiRemovePackages(mShellDynListProtocolsHiiHandle);
        return EFI_LOAD_ERROR;
    }

    return EFI_SUCCESS;
}

/**
This is the shell command "lp"'s handler function. This function handles
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
    )
{
    EFI_BOOT_SERVICES * pBS = SystemTable->BootServices;
    EFI_STATUS Status;
    UINTN HandleCount;
    EFI_HANDLE * pHandleBuffer;
    UINTN HandleIndex;
    UINTN ProtocolCount;
    EFI_GUID ** pProtocolBuffer;
    UINTN ProtocolIndex;

    // 1st get list of all handles
    Status = pBS->LocateHandleBuffer(
        AllHandles,
        NULL,
        NULL,
        &HandleCount,
        &pHandleBuffer);
    if (EFI_ERROR(Status))
    {
        DEBUG((EFI_D_ERROR, "LocateHandleBuffer failed %r\n", Status));
        return SHELL_ABORTED;
    }

    // 2nd interate handles and get+print all protocols
    for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++)
    {
        Status = pBS->ProtocolsPerHandle(
            pHandleBuffer[HandleIndex],
            &pProtocolBuffer,
            &ProtocolCount);
        if (EFI_ERROR(Status))
        {
            DEBUG((EFI_D_ERROR, "ProtocolsPerHandle failed on handle #%d = 0x%x: %r\n", HandleIndex, pHandleBuffer[HandleIndex], Status));
            pBS->FreePool(pHandleBuffer);
            return SHELL_ABORTED;
        }

        for (ProtocolIndex = 0; ProtocolIndex < ProtocolCount; ProtocolIndex++)
        {
            if (0 == ProtocolIndex)
                Print(L"Handle 0x%08X:   %g\n", pHandleBuffer[HandleIndex], pProtocolBuffer[ProtocolIndex]);
            else
                Print(L"                     %g\n", pProtocolBuffer[ProtocolIndex]);
        }

        pBS->FreePool(pProtocolBuffer);
    }

    pBS->FreePool(pHandleBuffer);

    return SHELL_SUCCESS;
}

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
    )
{
    return HiiGetString(
             mShellDynListProtocolsHiiHandle,
             STRING_TOKEN(STR_GET_HELP_LP),
             Language
             );
}
