# OpenFst
This is a read-only unofficial mirror of [OpenFst](http://openfst.org/).

This is simply a mirror of recent OpenFst releases, for convenience. The OpenFst library was not developed here, the project is not active here, it does not accept pull requests here, and there is no issue tracker or wiki here. For all of these things, the [OpenFst project home](http://openfst.org/) is the best place to go.

[![Build Status](https://travis-ci.com/mjansche/openfst.svg?branch=master)](https://travis-ci.com/mjansche/openfst)


OpenFst is a library for constructing, combining, optimizing, and searching
weighted finite-state transducers (FSTs).

## REQUIREMENTS:

  This version is known to work under Linux using g++ (>= 4.9) and OS X using
  XCode (>= 5). It is expected to work wherever adequate POSIX (dlopen,
  ssize_t, basename), C99 (snprintf, strtoll, <stdint.h>), and C++17
  (constexpr-if, <forward_list>, <string_view>, <unordered_map>,
  <unordered_set>) support is available.


## INSTALLATION:

  Follow the generic GNU build system instructions in ./INSTALL. We
  recommend configuring with --enable-static=no for faster compiles.

  Optional features:

  --enable-bin             Enable fst::script and executables (def: yes)
  --enable-compact-fsts    Enable CompactFst extensions (def: no)
  --enable-compress        Enable compression extension (def: no)
  --enable-const-fsts      Enable ConstFst extensions (def: no)
  --enable-far             Enable FAR extensions (def: no)
  --enable-fsts            Enable all FST SO extensions (def: no)
  --enable-grm             Enable all dependencies of OpenGrm (def: no)
  --enable-linear-fsts     Enable LinearTagger/ClassifierFst extensions (def: no)
  --enable-lookahead-fsts  Enable LookAheadFst extensions (def: no)
  --enable-mpdt            Enable MPDT extensions (def: no)
  --enable-ngram-fsts      Enable NGramFst extensions (def: no)
  --enable-pdt             Enable PDT extensions (def: no)
  --enable-python          Enable Python extension (def: no)
  --enable-special         Enable special-matcher extensions (def: no)

  Configuring with --enable-bin=no gives very fast compiles, but excludes the
  command line utilities.

  Configuring with --enable-python will attempt to install the Python module to
  whichever site-packages (or dist-packages, on Debian or Ubuntu) is found
  during configuration. If `import pywrapfst` fails from a PYthon 3.6 or better 
  interpreter after installation, relocate pywrapfst.so to a directory in your
  interpreter's `sys.path` or $PYTHONPATH.

  The flag --with-libfstdir specifies where FST extensions should be installed;
  it defaults to ${libdir}/fst.

  Compiling with -Wall -Wno-sign-compare under g++ should give no warnings from
  this library.

  If you encounter an error about loading shared objects when attempting to use
  the library immediately after installation, (e.g, `...cannot open shared
  object file...`) you may need to refresh your system's shared object cache.
  On Linux, this is accomplished by invoking ldconfig; the corresponding command
  on OS X is called update_dyld_shared_cache. Both of these require superuser
  privileges (and so should be executed with sudo).


## USAGE:

  Assuming you've installed under the default /usr/local, the FST binaries are
  found on /usr/local/bin.

  To use in your own program, include <fst/fstlib.h> and compile with 
  -I/usr/local/include. The compiler must support C++11 (for g++ add the flag
  -std=c++17). Link against /usr/local/lib/libfst.so and -ldl. Set your
  LD_LIBRARY_PATH (or equivalent) to contain /usr/local/lib. The linking is,
  by default, dynamic so that the Fst and Arc type DSO extensions can be used
  correctly if desired. Any extensions will be found under /usr/local/lib/fst
  or /usr/local/include/fst/extensions.


## BUILDING WITH BAZEL:

  Release 1.7.2 provides the ability to build the core library and binaries as
  well as several extensions with Bazel and to depend on OpenFst as an
  external dependency in other projects compiled with Bazel. Please refer to
  https://bazel.build for information on using Bazel. OpenFst can be compiled
  from anywhere in the source tree, as follows:

  $ bazel build //:all

  Tests can be run in a similar fashion:

  $ bazel test //:all

  The Bazel build-file is provided as-is.


## DOCUMENTATION:

  See www.openfst.org for general documentation.
  See ./NEWS for updates since the last release.
