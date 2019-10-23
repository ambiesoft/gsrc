#### **gn gen [\--check] [&lt;ide options&gt;] &lt;out_dir&gt;**

```
  Generates ninja files from the current tree and puts them in the given output
  directory.

  The output directory can be a source-repo-absolute path name such as:
      //out/foo
  Or it can be a directory relative to the current directory such as:
      out/foo

  "gn gen --check" is the same as running "gn check". See "gn help check"
  for documentation on that mode.

  See "gn help switches" for the common command-line switches.
```

#### **IDE options**

```
  GN optionally generates files for IDE. Possibilities for <ide options>

  --ide=<ide_name>
      Generate files for an IDE. Currently supported values:
      "eclipse" - Eclipse CDT settings file.
      "vs" - Visual Studio project/solution files.
             (default Visual Studio version: 2017)
      "vs2013" - Visual Studio 2013 project/solution files.
      "vs2015" - Visual Studio 2015 project/solution files.
      "vs2017" - Visual Studio 2017 project/solution files.
      "vs2019" - Visual Studio 2019 project/solution files.
      "xcode" - Xcode workspace/solution files.
      "qtcreator" - QtCreator project files.
      "json" - JSON file containing target information

  --filters=<path_prefixes>
      Semicolon-separated list of label patterns used to limit the set of
      generated projects (see "gn help label_pattern"). Only matching targets
      and their dependencies will be included in the solution. Only used for
      Visual Studio, Xcode and JSON.
```

#### **Visual Studio Flags**

```
  --sln=<file_name>
      Override default sln file name ("all"). Solution file is written to the
      root build directory.

  --no-deps
      Don't include targets dependencies to the solution. Changes the way how
      --filters option works. Only directly matching targets are included.

  --winsdk=<sdk_version>
      Use the specified Windows 10 SDK version to generate project files.
      As an example, "10.0.15063.0" can be specified to use Creators Update SDK
      instead of the default one.

  --ninja-extra-args=<string>
      This string is passed without any quoting to the ninja invocation
      command-line. Can be used to configure ninja flags, like "-j".
```

#### **Xcode Flags**

```
  --workspace=<file_name>
      Override defaut workspace file name ("all"). The workspace file is
      written to the root build directory.

  --ninja-extra-args=<string>
      This string is passed without any quoting to the ninja invocation
      command-line. Can be used to configure ninja flags, like "-j".

  --root-target=<target_name>
      Name of the target corresponding to "All" target in Xcode. If unset,
      "All" invokes ninja without any target and builds everything.
```

#### **QtCreator Flags**

```
  --root-target=<target_name>
      Name of the root target for which the QtCreator project will be generated
      to contain files of it and its dependencies. If unset, the whole build
      graph will be emitted.
```

#### **Eclipse IDE Support**

```
  GN DOES NOT generate Eclipse CDT projects. Instead, it generates a settings
  file which can be imported into an Eclipse CDT project. The XML file contains
  a list of include paths and defines. Because GN does not generate a full
  .cproject definition, it is not possible to properly define includes/defines
  for each file individually. Instead, one set of includes/defines is generated
  for the entire project. This works fairly well but may still result in a few
  indexer issues here and there.
```

#### **Generic JSON Output**

```
  Dumps target information to a JSON file and optionally invokes a
  python script on the generated file. See the comments at the beginning
  of json_project_writer.cc and desc_builder.cc for an overview of the JSON
  file format.

  --json-file-name=<json_file_name>
      Overrides default file name (project.json) of generated JSON file.

  --json-ide-script=<path_to_python_script>
      Executes python script after the JSON file is generated. Path can be
      project absolute (//), system absolute (/) or relative, in which case the
      output directory will be base. Path to generated JSON file will be first
      argument when invoking script.

  --json-ide-script-args=<argument>
      Optional second argument that will passed to executed script.
```

#### **Compilation Database**

```
  --export-compile-commands[=<target_name1,target_name2...>]
      Produces a compile_commands.json file in the root of the build directory
      containing an array of “command objects”, where each command object
      specifies one way a translation unit is compiled in the project. If a list
      of target_name is supplied, only targets that are reachable from the list
      of target_name will be used for “command objects” generation, otherwise
      all available targets will be used. This is used for various Clang-based
      tooling, allowing for the replay of individual compilations independent
      of the build system.
```