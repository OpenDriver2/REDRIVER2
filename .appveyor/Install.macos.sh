#!/usr/bin/env bash
set -ex

# AppVeyor's macOS image ships Homebrew but not the package set we need.
# This installs everything required to build both renderer backends —
# OpenGL (default) and Vulkan/MoltenVK (opt-in via --renderer=vulkan).

brew update

# Common deps for both backends
brew install premake sdl2 jpeg openal-soft

# Vulkan backend deps. shaderc is statically linked from libshaderc_combined.a
# at link time so the produced binary doesn't need a runtime SPIR-V compiler.
brew install vulkan-headers vulkan-loader molten-vk shaderc
