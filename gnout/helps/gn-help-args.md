#### **\--args**: Specifies build arguments overrides.

```
  See "gn help buildargs" for an overview of how build arguments work.

  Most operations take a build directory. The build arguments are taken from
  the previous build done in that directory. If a command specifies --args, it
  will override the previous arguments stored in the build directory, and use
  the specified ones.

  The args specified will be saved to the build directory for subsequent
  commands. Specifying --args="" will clear all build arguments.
```

#### **Formatting**

```
  The value of the switch is interpreted in GN syntax. For typical usage of
  string arguments, you will need to be careful about escaping of quotes.
```

#### **Examples**

```
  gn gen out/Default --args="foo=\"bar\""

  gn gen out/Default --args='foo="bar" enable=true blah=7'

  gn check out/Default --args=""
    Clears existing build args from the directory.

  gn desc out/Default --args="some_list=[1, false, \"foo\"]"
```
