#### **.gn file**

```
  When gn starts, it will search the current directory and parent directories
  for a file called ".gn". This indicates the source root. You can override
  this detection by using the --root command-line argument

  The .gn file in the source root will be executed. The syntax is the same as a
  buildfile, but with very limited build setup-specific meaning.

  If you specify --root, by default GN will look for the file .gn in that
  directory. If you want to specify a different file, you can additionally pass
  --dotfile:

    gn gen out/Debug --root=/home/build --dotfile=/home/my_gn_file.gn
```

#### **Variables**

```
  arg_file_template [optional]
      Path to a file containing the text that should be used as the default
      args.gn content when you run `gn args`.

  buildconfig [required]
      Path to the build config file. This file will be used to set up the
      build file execution environment for each toolchain.

  check_targets [optional]
      A list of labels and label patterns that should be checked when running
      "gn check" or "gn gen --check". If unspecified, all targets will be
      checked. If it is the empty list, no targets will be checked. To
      bypass this list, request an explicit check of targets, like "//*".

      The format of this list is identical to that of "visibility" so see "gn
      help visibility" for examples.

  exec_script_whitelist [optional]
      A list of .gn/.gni files (not labels) that have permission to call the
      exec_script function. If this list is defined, calls to exec_script will
      be checked against this list and GN will fail if the current file isn't
      in the list.

      This is to allow the use of exec_script to be restricted since is easy to
      use inappropriately. Wildcards are not supported. Files in the
      secondary_source tree (if defined) should be referenced by ignoring the
      secondary tree and naming them as if they are in the main tree.

      If unspecified, the ability to call exec_script is unrestricted.

      Example:
        exec_script_whitelist = [
          "//base/BUILD.gn",
          "//build/my_config.gni",
        ]

  root [optional]
      Label of the root build target. The GN build will start by loading the
      build file containing this target name. This defaults to "//:" which will
      cause the file //BUILD.gn to be loaded.

  script_executable [optional]
      Path to specific Python executable or potentially a different language
      interpreter that is used to execute scripts in action targets and
      exec_script calls.

  secondary_source [optional]
      Label of an alternate directory tree to find input files. When searching
      for a BUILD.gn file (or the build config file discussed above), the file
      will first be looked for in the source root. If it's not found, the
      secondary source root will be checked (which would contain a parallel
      directory hierarchy).

      This behavior is intended to be used when BUILD.gn files can't be checked
      in to certain source directories for whatever reason.

      The secondary source root must be inside the main source tree.

  default_args [optional]
      Scope containing the default overrides for declared arguments. These
      overrides take precedence over the default values specified in the
      declare_args() block, but can be overriden using --args or the
      args.gn file.

      This is intended to be used when subprojects declare arguments with
      default values that need to be changed for whatever reason.
```

#### **Example .gn file contents**

```
  buildconfig = "//build/config/BUILDCONFIG.gn"

  check_targets = [
    "//doom_melon/*",  # Check everything in this subtree.
    "//tools:mind_controlling_ant",  # Check this specific target.
  ]

  root = "//:root"

  secondary_source = "//build/config/temporary_buildfiles/"

  default_args = {
    # Default to release builds for this project.
    is_debug = false
    is_component_build = false
  }
```
