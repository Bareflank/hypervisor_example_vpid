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

#ifndef VMCS_VPID_H
#define VMCS_VPID_H

#include <vmcs/vmcs_intel_x64.h>
#include <vmcs/vmcs_intel_x64_16bit_control_fields.h>
#include <vmcs/vmcs_intel_x64_32bit_control_fields.h>

using namespace intel_x64;
using namespace vmcs;

class vmcs_vpid : public vmcs_intel_x64
{
public:

    /// Default Constructor
    ///
    vmcs_vpid() = default;

    /// Destructor
    ///
    ~vmcs_vpid() override  = default;

    /// Write Fields
    ///
    /// This functions is provided by the VMCS class as a means to
    /// extend the existing VMCS setup with custom logic. In this
    /// example, we add VPID support.
    ///
    void
    write_fields(gsl::not_null<vmcs_intel_x64_state *> host_state,
                 gsl::not_null<vmcs_intel_x64_state *> guest_state) override
    {
        static uint16_t vpid = 1;

        bfdebug << "enabling vpid: " << vpid << bfendl;

        // Before we setup VPID, we let the existing VMCS set itself up. This way
        // whatever changes we are making are done on top of the default setup.
        vmcs_intel_x64::write_fields(host_state, guest_state);

        // Finally we setup VPID. This is done by providing a custom 16bit unique
        // number greater than 0, and turning on the secondary control field for
        // VPID. Note that we do not have to enable the secondary controls ourselves
        // because Bareflank does that for us.
        vmcs::virtual_processor_identifier::set(vpid++);
        secondary_processor_based_vm_execution_controls::enable_vpid::enable();
    }
};

#endif
