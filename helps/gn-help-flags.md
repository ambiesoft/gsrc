### <a name="cflags*"></a>**cflags***: Flags passed to the C compiler.

```
  A list of strings.

  "cflags" are passed to all invocations of the C, C++, Objective C, and
  Objective C++ compilers.

  To target one of these variants individually, use "cflags_c", "cflags_cc",
  "cflags_objc", and "cflags_objcc", respectively. These variant-specific
  versions of cflags* will be appended on the compiler command line after
  "cflags".

  See also "asmflags" for flags for assembly-language files.
```

#### **Ordering of flags and values**

```
  1. Those set on the current target (not in a config).
  2. Those set on the "configs" on the target in order that the
     configs appear in the list.
  3. Those set on the "all_dependent_configs" on the target in order
     that the configs appear in the list.
  4. Those set on the "public_configs" on the target in order that
     those configs appear in the list.
  5. all_dependent_configs pulled from dependencies, in the order of
     the "deps" list. This is done recursively. If a config appears
     more than once, only the first occurence will be used.
  6. public_configs pulled from dependencies, in the order of the
     "deps" list. If a dependency is public, they will be applied
     recursively.
```
