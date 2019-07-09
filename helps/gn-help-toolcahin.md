### <a name="toolchain"></a>**toolchain**: Defines a toolchain.

```
  A toolchain is a set of commands and build flags used to compile the source
  code. The toolchain() function defines these commands.
```

#### **Toolchain overview**

```
  You can have more than one toolchain in use at once in a build and a target
  can exist simultaneously in multiple toolchains. A build file is executed
  once for each toolchain it is referenced in so the GN code can vary all
  parameters of each target (or which targets exist) on a per-toolchain basis.

  When you have a simple build with only one toolchain, the build config file
  is loaded only once at the beginning of the build. It must call
  set_default_toolchain() (see "gn help set_default_toolchain") to tell GN the
  label of the toolchain definition to use. The "toolchain_args" section of the
  toolchain definition is ignored.

  When a target has a dependency on a target using different toolchain (see "gn
  help labels" for how to specify this), GN will start a build using that
  secondary toolchain to resolve the target. GN will load the build config file
  with the build arguments overridden as specified in the toolchain_args.
  Because the default toolchain is already known, calls to
  set_default_toolchain() are ignored.

  To load a file in an alternate toolchain, GN does the following:

    1. Loads the file with the toolchain definition in it (as determined by the
       toolchain label).
    2. Re-runs the master build configuration file, applying the arguments
       specified by the toolchain_args section of the toolchain definition.
    3. Loads the destination build file in the context of the configuration file
       in the previous step.

  The toolchain configuration is two-way. In the default toolchain (i.e. the
  main build target) the configuration flows from the build config file to the
  toolchain. The build config file looks at the state of the build (OS type,
  CPU architecture, etc.) and decides which toolchain to use (via
  set_default_toolchain()). In secondary toolchains, the configuration flows
  from the toolchain to the build config file: the "toolchain_args" in the
  toolchain definition specifies the arguments to re-invoke the build.
```

#### **Functions and variables**

```
  tool()
    The tool() function call specifies the commands commands to run for a given
    step. See "gn help tool".

  toolchain_args
    Overrides for build arguments to pass to the toolchain when invoking it.
    This is a variable of type "scope" where the variable names correspond to
    variables in declare_args() blocks.

    When you specify a target using an alternate toolchain, the master build
    configuration file is re-interpreted in the context of that toolchain.
    toolchain_args allows you to control the arguments passed into this
    alternate invocation of the build.

    Any default system arguments or arguments passed in via "gn args" will also
    be passed to the alternate invocation unless explicitly overridden by
    toolchain_args.

    The toolchain_args will be ignored when the toolchain being defined is the
    default. In this case, it's expected you want the default argument values.

    See also "gn help buildargs" for an overview of these arguments.

  deps
    Dependencies of this toolchain. These dependencies will be resolved before
    any target in the toolchain is compiled. To avoid circular dependencies
    these must be targets defined in another toolchain.

    This is expressed as a list of targets, and generally these targets will
    always specify a toolchain:
      deps = [ "//foo/bar:baz(//build/toolchain:bootstrap)" ]

    This concept is somewhat inefficient to express in Ninja (it requires a lot
    of duplicate of rules) so should only be used when absolutely necessary.
```

#### **Example of defining a toolchain**

```
  toolchain("32") {
    tool("cc") {
      command = "gcc {{source}}"
      ...
    }

    toolchain_args = {
      use_doom_melon = true  # Doom melon always required for 32-bit builds.
      current_cpu = "x86"
    }
  }

  toolchain("64") {
    tool("cc") {
      command = "gcc {{source}}"
      ...
    }

    toolchain_args = {
      # use_doom_melon is not overridden here, it will take the default.
      current_cpu = "x64"
    }
  }
```

#### **Example of cross-toolchain dependencies**

```
  If a 64-bit target wants to depend on a 32-bit binary, it would specify a
  dependency using data_deps (data deps are like deps that are only needed at
  runtime and aren't linked, since you can't link a 32-bit and a 64-bit
  library).

    executable("my_program") {
      ...
      if (target_cpu == "x64") {
        # The 64-bit build needs this 32-bit helper.
        data_deps = [ ":helper(//toolchains:32)" ]
      }
    }

    if (target_cpu == "x86") {
      # Our helper library is only compiled in 32-bits.
      shared_library("helper") {
        ...
      }
    }
```
