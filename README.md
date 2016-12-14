# Bareflank Hypervisor VPID Example

## Description

This example demonstrates how to extend the Bareflank hypervisor to use
Intel's VPID to increase performance. For more information on how Bareflank
extensions work, please see the following:

[API Documentation](http://bareflank.github.io/hypervisor/html/)

## Compilation / Usage

To setup our extension, we can either clone the extension into the Bareflank
root folder and run make, or we can use the configure script to create an
out-of-tree build environment that has our extension setup for easy development.
Note that using the later approach, we can have more than one build
environment (the following assumes this is running on Linux).

```
cd ~/
git clone https://github.com/Bareflank/hypervisor.git
git clone https://github.com/Bareflank/hypervisor_example_vpid.git
cd ~/hypervisor

./tools/scripts/setup-<xxx>.sh --no-configure
sudo reboot

cd ~/
mkdir build
cd ~/build

~/hypervisor/configure -m ~/hypervisor_example_vpid/bin/vpid.modules -e ~/hypervisor_example_vpid

make
```

To test out our extended version of Bareflank, all we need to do is run the
make shortcuts as usual:

```
make driver_load
make quick

make status
make dump

make stop
make driver_load
```
