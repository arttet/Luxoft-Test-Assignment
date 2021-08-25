#!/usr/bin/env bash

set -euo pipefail

# Visual Studio
conan install . -g cmake -if build -b outdated \
    -s build_type=Debug -s arch_target=x86_64 -s compiler.cppstd=17 \
    -s compiler.version=16 -s compiler="Visual Studio" -s compiler.runtime=MTd -s compiler.toolset=v142 \
    -o tests=True

conan build . -bf build
