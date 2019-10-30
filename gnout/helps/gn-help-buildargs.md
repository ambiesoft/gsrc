#### **Build Arguments Overview**

```
  Build arguments are variables passed in from outside of the build that build
  files can query to determine how the build works.
```

#### **How build arguments are set**

```
  First, system default arguments are set based on the current system. The
  built-in arguments are:
   - host_cpu
   - host_os
   - current_cpu
   - current_os
   - target_cpu
   - target_os

  Next, project-specific overrides are applied. These are specified inside
  the default_args variable of //.gn. See "gn help dotfile" for more.

  If specified, arguments from the --args command line flag are used. If that
  flag is not specified, args from previous builds in the build directory will
  be used (this is in the file args.gn in the build directory).

  Last, for targets being compiled with a non-default toolchain, the toolchain
  overrides are applied. These are specified in the toolchain_args section of a
  toolchain definition. The use-case for this is that a toolchain may be
  building code for a different platform, and that it may want to always
  specify Posix, for example. See "gn help toolchain" for more.

  If you specify an override for a build argument that never appears in a
  "declare_args" call, a nonfatal error will be displayed.
```

#### **Examples**

```
  gn args out/FooBar
      Create the directory out/FooBar and open an editor. You would type
      something like this into that file:
          enable_doom_melon=false
          os="android"

  gn gen out/FooBar --args="enable_doom_melon=true os=\"android\""
      This will overwrite the build directory with the given arguments. (Note
      that the quotes inside the args command will usually need to be escaped
      for your shell to pass through strings values.)
```

#### **How build arguments are used**

```
  If you want to use an argument, you use declare_args() and specify default
  values. These default values will apply if none of the steps listed in the
  "How build arguments are set" section above apply to the given argument, but
  the defaults will not override any of these.

  Often, the root build config file will declare global arguments that will be
  passed to all buildfiles. Individual build files can also specify arguments
  that apply only to those files. It is also useful to specify build args in an
  "import"-ed file if you want such arguments to apply to multiple buildfiles.
```
