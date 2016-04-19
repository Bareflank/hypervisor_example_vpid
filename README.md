# Bareflank Hypervisor Example

## Description

This example demonstrates how to extend the bareflank hypervisor to enable VPID.

## Compilation / Usage

First, you must clone the repo into your existing bareflank repo. To see instructions on how to setup bareflank, please see the following:

[Bareflank Hypervisor](https://github.com/Bareflank/hypervisor)

At the moment, out-of-tree compilation is not supported.

```
cd ~/hypervisor
git clone https://github.com/Bareflank/hypervisor_example_vpid
```

Once the example repo is cloned, you can now build the example. Bareflank automatically looks for the examples, or any folder that starts with "src_", and builds these folders along with bareflank itself. 

```
make
```

Finally, you can run the example. This can be done by running bfm manually, and providing the path to your custom modules list:

```
pushd bfm/bin/native
sudo LD_LIBRARY_PATH=. ./bfm load hypervisor_example_vpid/bin/vpid.modules
sudo LD_LIBRARY_PATH=. ./bfm start
sudo LD_LIBRARY_PATH=. ./bfm status
sudo LD_LIBRARY_PATH=. ./bfm dump
popd
```

or you can use the shortcuts:

```
make load MODULES=hypervisor_example_vpid/bin/vpid.modules
make start
make status
make dump
```
