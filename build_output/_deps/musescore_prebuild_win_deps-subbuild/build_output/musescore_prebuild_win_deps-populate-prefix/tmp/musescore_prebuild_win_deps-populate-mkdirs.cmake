# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/Users/hyper/workspace/bobeditpro/build_output/_deps/musescore_prebuild_win_deps-src")
  file(MAKE_DIRECTORY "C:/Users/hyper/workspace/bobeditpro/build_output/_deps/musescore_prebuild_win_deps-src")
endif()
file(MAKE_DIRECTORY
  "C:/Users/hyper/workspace/bobeditpro/build_output/_deps/musescore_prebuild_win_deps-build"
  "C:/Users/hyper/workspace/bobeditpro/build_output/_deps/musescore_prebuild_win_deps-subbuild/build_output/musescore_prebuild_win_deps-populate-prefix"
  "C:/Users/hyper/workspace/bobeditpro/build_output/_deps/musescore_prebuild_win_deps-subbuild/build_output/musescore_prebuild_win_deps-populate-prefix/tmp"
  "C:/Users/hyper/workspace/bobeditpro/build_output/_deps/musescore_prebuild_win_deps-subbuild/build_output/musescore_prebuild_win_deps-populate-prefix/src/musescore_prebuild_win_deps-populate-stamp"
  "C:/Users/hyper/workspace/bobeditpro/build_output/_deps/musescore_prebuild_win_deps-subbuild/build_output/musescore_prebuild_win_deps-populate-prefix/src"
  "C:/Users/hyper/workspace/bobeditpro/build_output/_deps/musescore_prebuild_win_deps-subbuild/build_output/musescore_prebuild_win_deps-populate-prefix/src/musescore_prebuild_win_deps-populate-stamp"
)

set(configSubDirs Debug;Release;MinSizeRel;RelWithDebInfo)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/hyper/workspace/bobeditpro/build_output/_deps/musescore_prebuild_win_deps-subbuild/build_output/musescore_prebuild_win_deps-populate-prefix/src/musescore_prebuild_win_deps-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/hyper/workspace/bobeditpro/build_output/_deps/musescore_prebuild_win_deps-subbuild/build_output/musescore_prebuild_win_deps-populate-prefix/src/musescore_prebuild_win_deps-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
