#### **gn path &lt;out_dir&gt; &lt;target_one&gt; &lt;target_two&gt;**

```
  Finds paths of dependencies between two targets. Each unique path will be
  printed in one group, and groups will be separate by newlines. The two
  targets can appear in either order (paths will be found going in either
  direction).

  By default, a single path will be printed. If there is a path with only
  public dependencies, the shortest public path will be printed. Otherwise, the
  shortest path using either public or private dependencies will be printed. If
  --with-data is specified, data deps will also be considered. If there are
  multiple shortest paths, an arbitrary one will be selected.
```

#### **Interesting paths**

```
  In a large project, there can be 100's of millions of unique paths between a
  very high level and a common low-level target. To make the output more useful
  (and terminate in a reasonable time), GN will not revisit sub-paths
  previously known to lead to the target.
```

#### **Options**

```
  --all
     Prints all "interesting" paths found rather than just the first one.
     Public paths will be printed first in order of increasing length, followed
     by non-public paths in order of increasing length.

  --public
     Considers only public paths. Can't be used with --with-data.

  --with-data
     Additionally follows data deps. Without this flag, only public and private
     linked deps will be followed. Can't be used with --public.
```

#### **Example**

```
  gn path out/Default //base //tools/gn
```
