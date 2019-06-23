#### **gn check &lt;out_dir&gt; [&lt;label_pattern&gt;] [\--force] [\--check-generated]**

```
  GN's include header checker validates that the includes for C-like source
  files match the build dependency graph.

  "gn check" is the same thing as "gn gen" with the "--check" flag except that
  this command does not write out any build files. It's intended to be an easy
  way to manually trigger include file checking.

  The <label_pattern> can take exact labels or patterns that match more than
  one (although not general regular expressions). If specified, only those
  matching targets will be checked. See "gn help label_pattern" for details.
```

#### **Command-specific switches**

```
  --force
      Ignores specifications of "check_includes = false" and checks all
      target's files that match the target label.

  --check-generated
      Generated files are normally not checked since they do not exist
      until after a build. With this flag, those generated files that
      can be found on disk are also checked.
```

#### **What gets checked**

```
  The .gn file may specify a list of targets to be checked in the list
  check_targets (see "gn help dotfile"). If a label pattern is specified
  on the command line, check_targets is not used.

  Targets can opt-out from checking with "check_includes = false" (see
  "gn help check_includes").

  For targets being checked:

    - GN opens all C-like source files in the targets to be checked and scans
      the top for includes.

    - Generated files (that might not exist yet) are ignored unless
      the --check-generated flag is provided.

    - Includes with a "nogncheck" annotation are skipped (see
      "gn help nogncheck").

    - Only includes using "quotes" are checked. <brackets> are assumed to be
      system includes.

    - Include paths are assumed to be relative to any of the "include_dirs" for
      the target (including the implicit current dir).

    - GN does not run the preprocessor so will not understand conditional
      includes.

    - Only includes matching known files in the build are checked: includes
      matching unknown paths are ignored.

  For an include to be valid:

    - The included file must be in the current target, or there must be a path
      following only public dependencies to a target with the file in it
      ("gn path" is a good way to diagnose problems).

    - There can be multiple targets with an included file: only one needs to be
      valid for the include to be allowed.

    - If there are only "sources" in a target, all are considered to be public
      and can be included by other targets with a valid public dependency path.

    - If a target lists files as "public", only those files are able to be
      included by other targets. Anything in the sources will be considered
      private and will not be includable regardless of dependency paths.

    - Outputs from actions are treated like public sources on that target.

    - A target can include headers from a target that depends on it if the
      other target is annotated accordingly. See "gn help
      allow_circular_includes_from".
```

#### **Advice on fixing problems**

```
  If you have a third party project that is difficult to fix or doesn't care
  about include checks it's generally best to exclude that target from checking
  altogether via "check_includes = false".

  If you have conditional includes, make sure the build conditions and the
  preprocessor conditions match, and annotate the line with "nogncheck" (see
  "gn help nogncheck" for an example).

  If two targets are hopelessly intertwined, use the
  "allow_circular_includes_from" annotation. Ideally each should have identical
  dependencies so configs inherited from those dependencies are consistent (see
  "gn help allow_circular_includes_from").

  If you have a standalone header file or files that need to be shared between
  a few targets, you can consider making a source_set listing only those
  headers as public sources. With only header files, the source set will be a
  no-op from a build perspective, but will give a central place to refer to
  those headers. That source set's files will still need to pass "gn check" in
  isolation.

  In rare cases it makes sense to list a header in more than one target if it
  could be considered conceptually a member of both.
```

#### **Examples**

```
  gn check out/Debug
      Check everything.

  gn check out/Default //foo:bar
      Check only the files in the //foo:bar target.

  gn check out/Default "//foo/*
      Check only the files in targets in the //foo directory tree.
```
