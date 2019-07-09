### <a name="public"></a>**public**: Declare public header files for a target.

```
  A list of files that other targets can include. These permissions are checked
  via the "check" command (see "gn help check").

  If no public files are declared, other targets (assuming they have visibility
  to depend on this target) can include any file in the sources list. If this
  variable is defined on a target, dependent targets may only include files on
  this whitelist unless that target is marked as a friend (see "gn help
  friend").

  Header file permissions are also subject to visibility. A target must be
  visible to another target to include any files from it at all and the public
  headers indicate which subset of those files are permitted. See "gn help
  visibility" for more.

  Public files are inherited through the dependency tree. So if there is a
  dependency A -> B -> C, then A can include C's public headers. However, the
  same is NOT true of visibility, so unless A is in C's visibility list, the
  include will be rejected.

  GN only knows about files declared in the "sources" and "public" sections of
  targets. If a file is included that is not known to the build, it will be
  allowed.

  It is common for test targets to need to include private headers for their
  associated code. In this case, list the test target in the "friend" list of
  the target that owns the private header to allow the inclusion. See
  "gn help friend" for more.

  When a binary target has no explicit or implicit public headers (a "public"
  list is defined but is empty), GN assumes that the target can not propagate
  any compile-time dependencies up the dependency tree. In this case, the build
  can be parallelized more efficiently.
  Say there are dependencies:
    A (shared library) -> B (shared library) -> C (action).
  Normally C must complete before any source files in A can compile (because
  there might be generated includes). But when B explicitly declares no public
  headers, C can execute in parallel with A's compile steps. C must still be
  complete before any dependents link.
```

#### **Examples**

```
  These exact files are public:
    public = [ "foo.h", "bar.h" ]

  No files are public (no targets may include headers from this one):
    # This allows starting compile in dependent targets earlier.
    public = []
```
