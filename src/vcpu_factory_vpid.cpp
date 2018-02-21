#include <bfvmm/vcpu/vcpu_factory.h>
#include <bfvmm/vcpu/arch/intel_x64/vcpu.h>

using namespace ::intel_x64::vmcs;

namespace example
{
namespace intel_x64
{

class vcpu : public bfvmm::intel_x64::vcpu
{
public:

    vcpu(vcpuid::type id) :
        bfvmm::intel_x64::vcpu{id}
    {
	static uint16_t vpid = 1;

	virtual_processor_identifier::set(vpid++);
	secondary_processor_based_vm_execution_controls::enable_vpid::enable();
    }

    ~vcpu() override = default;
    { }
};

}
}

namespace bfvmm
{

WEAK_SYM std::unique_ptr<vcpu>
vcpu_factory::make_vcpu(vcpuid::type vcpuid, bfobject *obj)
{
    bfignored(obj);
    return std::make_unique<example::intel_x64::vcpu>(vcpuid);
}

}

