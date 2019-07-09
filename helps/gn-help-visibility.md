### <a name="visibility"></a>**visibility**: A list of labels that can depend on a target.

```
  A list of labels and label patterns that define which targets can depend on
  the current one. These permissions are checked via the "check" command (see
  "gn help check").

  If visibility is not defined, it defaults to public ("*").

  If visibility is defined, only the targets with labels that match it can
  depend on the current target. The empty list means no targets can depend on
  the current target.

  Tip: Often you will want the same visibility for all targets in a BUILD file.
  In this case you can just put the definition at the top, outside of any
  target, and the targets will inherit that scope and see the definition.
```

#### **Patterns**

```
  See "gn help label_pattern" for more details on what types of patterns are
  supported. If a toolchain is specified, only targets in that toolchain will
  be matched. If a toolchain is not specified on a pattern, targets in all
  toolchains will be matched.
```

#### **Examples**

```
  Only targets in the current buildfile ("private"):
    visibility = [ ":*" ]

  No targets (used for targets that should be leaf nodes):
    visibility = []

  Any target ("public", the default):
    visibility = [ "*" ]

  All targets in the current directory and any subdirectory:
    visibility = [ "./*" ]

  Any target in "//bar/BUILD.gn":
    visibility = [ "//bar:*" ]

  Any target in "//bar/" or any subdirectory thereof:
    visibility = [ "//bar/*" ]

  Just these specific targets:
    visibility = [ ":mything", "//foo:something_else" ]

  Any target in the current directory and any subdirectory thereof, plus
  any targets in "//bar/" and any subdirectory thereof.
    visibility = [ "./*", "//bar/*" ]
```
