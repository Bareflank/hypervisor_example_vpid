//
// Bareflank Hypervisor Examples
//
// Copyright (C) 2015 Assured Information Security, Inc.
// Author: Rian Quinn        <quinnr@ainfosec.com>
// Author: Brendan Kerrigan  <kerriganb@ainfosec.com>
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

#include <vmcs/vmcs_intel_x64.h>

class vmcs_vpid : public vmcs_intel_x64
{
public:

    /// Default Constructor
    ///
    vmcs_vpid() {}

    /// Destructor
    ///
    virtual ~vmcs_vpid() {}

    /// Write 16bit Control State
    ///
    virtual void
    write_16bit_control_state(const std::shared_ptr<vmcs_intel_x64_state> &state) override
    {
        static uint16_t vpid = 1;

        bfdebug << "enabling vpid" << bfendl;

        // To enable VPID, we need to pvoide a non-zero unique ID for each
        // VMCS that we create. If you want to see what an error looks like,
        // change the initial value for the vpid to 0, and run bareflank.
        // When this happens, an exception will be thrown, and the check
        // logic will inform you that the vpid is incorrectly set. Assuming
        // the check logic is accurate and complete, this logic should assist
        // in enabling VT-x features.
        vmwrite(VMCS_VIRTUAL_PROCESSOR_IDENTIFIER, vpid++);
        
        // Call base class
        vmcs_intel_x64::write_16bit_control_state(state);
    }

    /// Default Primary Controls
    ///
    virtual void
    primary_processor_based_vm_execution_controls() override
    {
        // To Enable VPID, we need to enabled the secondary controls.
        // To do this, we read the primary controls, enable the secondary
        // controls, and then write them back. Before we are finished, we call
        // into the base class just in case there is something the base class
        // also needs to do.

        // Enable secondary controls
        auto controls = vmread(VMCS_PRIMARY_PROCESSOR_BASED_VM_EXECUTION_CONTROLS);
        controls |= VM_EXEC_P_PROC_BASED_ACTIVATE_SECONDARY_CONTROLS;
        vmwrite(VMCS_PRIMARY_PROCESSOR_BASED_VM_EXECUTION_CONTROLS, controls);

        // Call base class
        vmcs_intel_x64::primary_processor_based_vm_execution_controls();
    }

    /// Default Secondary Controls
    ///
    virtual void
    secondary_processor_based_vm_execution_controls() override
    {
        // To Enable VPID, we need to enabled the VPID secondary control.
        // To do this, we read the secondary controls, set the vpid,
        // and then write them back. Before we are finished, we call into the
        // base class just in case there is something the base class also needs
        // to do.

        // Set the VPID secondary controls
        auto controls = vmread(VMCS_SECONDARY_PROCESSOR_BASED_VM_EXECUTION_CONTROLS);
        controls |= VM_EXEC_S_PROC_BASED_ENABLE_VPID;
        vmwrite(VMCS_SECONDARY_PROCESSOR_BASED_VM_EXECUTION_CONTROLS, controls);

        // Call base class
        vmcs_intel_x64::secondary_processor_based_vm_execution_controls();
    }
};
