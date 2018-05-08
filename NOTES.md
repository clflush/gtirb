# -*- org -*-
#+Title: Notes

* Tasks [0/8]
** TODO JSON serialization
- Currently code is using a polymorphic serializer.  This can be a JSON serializer with zero code changes.

** TODO Protobuf serialization
Maybe?  Not sure if this is worth the effort/complication.

** TODO Publish to github
- A public repo on github.com?

** TODO Configure documentation [0/1]
- [ ] gh-pages populated by CI system

** TODO CI tests on additional platforms [/]
- [ ] Redhat (maybe redhawk)
- [ ] CentOS
- [ ] MacOS (if this is easy to do)
- [ ] Windows

** TODO Be explicit about versioning
- Include a version number in each instance of the IR.
- Ensure we're always backwards compatible with previous versions.
- Use the version number inside serialization functions to provide for backwards compatability.

** TODO Announcement email to TPCP

* Core Utilities [0/4]
Requirements:
- Every one should have a man page
- Every one should print help and version information
- A top-level dispatch script (=gtirb=) should allow invocation of each sub function

** TODO Validator [0/4]
The validator should provide a number of checks.  These should maybe
be configurable.  By default a standard group of checks should be run
to validate an instance of GT-IRB.

- [ ] Check that the CFG is consistent with the dataflow
- [ ] Check that all symbols in symbolization exist
- [ ] Check that all symbols point to something
- [ ] Check that all external symbols are resolved in some module
...

** TODO Compare [0/2]
Compare multiple instances of GT-IRB and report differences
- [ ] Nice textual output format(s)
- [ ] Configurable to stifle certain types of differences
...

** TODO Select
Select a subset of an instance of GT-IRB and return it extracted as a
new instance of GT-IRB.

** TODO Combine
Combine N instances of GT-IRB.