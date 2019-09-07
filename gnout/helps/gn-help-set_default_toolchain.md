### <a name="set_default_toolchain"></a>**set_default_toolchain**: Sets the default toolchain name.

```
  set_default_toolchain(toolchain_label)

  The given label should identify a toolchain definition (see "gn help
  toolchain"). This toolchain will be used for all targets unless otherwise
  specified.

  This function is only valid to call during the processing of the build
  configuration file. Since the build configuration file is processed
  separately for each toolchain, this function will be a no-op when called
  under any non-default toolchains.

  For example, the default toolchain should be appropriate for the current
  environment. If the current environment is 32-bit and somebody references a
  target with a 64-bit toolchain, we wouldn't want processing of the build
  config file for the 64-bit toolchain to reset the default toolchain to
  64-bit, we want to keep it 32-bits.
```

#### **Argument**

```
  toolchain_label
      Toolchain name.
```

#### **Example**

```
  # Set default toolchain only has an effect when run in the context of the
  # default toolchain. Pick the right one according to the current CPU
  # architecture.
  if (target_cpu == "x64") {
    set_default_toolchain("//toolchains:64")
  } else if (target_cpu == "x86") {
    set_default_toolchain("//toolchains:32")
  }
```
