# testframework TriBITS Upgrade Notes

## What changed

Three files were added. No existing testframework files were modified.

| File | Status |
|------|--------|
| `PackagesList.cmake` | New |
| `TPLsList.cmake` | New |
| `cmake/CallbackSetupExtraOptions.cmake` | New |

## Why

Previously, testframework was listed as a package inside the daem and radix
`PackagesList.cmake` files. TriBITS then expected the package to live at a
path relative to the declaring repository (e.g. `daem/testframework` or
`radix/submodules/testframework`). This worked when testframework was a git
submodule, but broke as soon as it became a peer repository in the daem
meta-project — TriBITS would try to register it from multiple parent repos and
the `setup/` subdirectory `ADD_SUBDIRECTORY` calls scattered across daem's,
radix's, and samoa's callbacks would all fire, causing duplicate target
definitions and hard CMake errors.

### Fix: promote testframework to a native TriBITS repository

A TriBITS repository is self-describing. By adding the three required files
testframework now carries its own identity and TriBITS loads it exactly once,
via `cmake/NativeRepositoriesList.cmake` in the daem root project. Each of the
other repos (radix, samoa) can still declare `testframework` as an optional
package in their own `PackagesList.cmake` for standalone builds where
testframework is available as a submodule — `TRIBITS_ALLOW_MISSING_EXTERNAL_PACKAGES`
handles the case where it isn't.

### `PackagesList.cmake`

Declares the single `testframework` package at the repository root (`.`).
Required by TriBITS to know what packages this repository provides.

### `TPLsList.cmake`

Required boilerplate for every TriBITS repository. testframework has no
external TPL dependencies so the list is empty.

### `cmake/CallbackSetupExtraOptions.cmake`

Owns the single authoritative `ADD_SUBDIRECTORY(${testframework_SOURCE_DIR}/setup)`
call that registers the GoogleTest CMake integration. Because TriBITS calls
each repository's callback exactly once during configure, this eliminates the
duplicate registration problem entirely. The guarded `IF(EXISTS ...)` copies
that were previously spread across daem/radix/samoa callbacks are no longer
needed for the daem meta-project build (they remain in radix/samoa for
standalone builds where testframework is a submodule).
