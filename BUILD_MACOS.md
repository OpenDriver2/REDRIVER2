# REDRIVER2 — Building on macOS Apple Silicon

Build port of REDRIVER2 for macOS arm64 (Apple Silicon — M1/M2/M3/M4).
Also works on Intel macs (x86_64) via the same automatic prefix
detection.

## Prerequisites

1. **Xcode Command Line Tools**

   ```bash
   xcode-select --install
   ```

2. **Homebrew** — https://brew.sh

3. **Dependencies via Homebrew**

   OpenGL build (default):

   ```bash
   brew install premake sdl2 jpeg openal-soft
   ```

   Vulkan / MoltenVK build (optional):

   ```bash
   brew install premake sdl2 jpeg openal-soft \
                vulkan-headers vulkan-loader molten-vk shaderc
   ```

   On Apple Silicon brew installs under `/opt/homebrew`; on Intel macs
   it's `/usr/local`. `premake5.lua` detects either automatically.

## Build

```bash
git clone https://github.com/OpenDriver2/REDRIVER2.git
cd REDRIVER2
git submodule update --init --recursive
cd src_rebuild

# OpenGL backend (default)
premake5 gmake

# OR: Vulkan / MoltenVK backend
premake5 --renderer=vulkan gmake

cd project_gmake_macosx

# Apple Silicon
make config=release_arm64 -j$(sysctl -n hw.ncpu)

# Intel
make config=release_x64 -j$(sysctl -n hw.ncpu)
```

Available configurations: `debug_arm64`, `release_arm64`,
`release_dev_arm64` (and the matching `x64` variants).

Final binary: `src_rebuild/bin/Release/REDRIVER2`.

## Running the game

REDRIVER2 needs the original Driver 2 (PSX) data files alongside the
executable. See the
[installation wiki](https://github.com/OpenDriver2/REDRIVER2/wiki/Installation-instructions)
for the asset extraction steps.

## Optional environment variables

To point at non-Homebrew dependency installs:

```bash
export MAC_SDL2_DIR=/path/to/sdl2
export MAC_OPENAL_DIR=/path/to/openal-soft
export MAC_JPEG_DIR=/path/to/jpeg
# Vulkan-only:
export MAC_VULKAN_HEADERS=/path/to/vulkan-headers
export MAC_VULKAN_LOADER=/path/to/vulkan-loader
export MAC_MOLTENVK=/path/to/molten-vk
```

## What changed for macOS arm64

Summary of the deltas vs upstream:

### Build system
- `src_rebuild/premake5.lua` — `system:macosx` filter with `x64` and
  `arm64` platforms, Homebrew `includedirs`/`libdirs`, framework links
  (`Cocoa`, `OpenGL` or `Metal`+`QuartzCore`+`IOSurface`+`vulkan`),
  rpaths for the brew dylibs. Adds the `--renderer={opengl|vulkan}`
  option that gates the OpenGL vs Vulkan source files.
- `src_rebuild/premake5_psycross.lua` — equivalent macOS filter on the
  static-lib side, plus `removefiles` to switch `PsyX_render.cpp` ↔
  `PsyX_render_vk.cpp` based on the renderer option.
- `src_rebuild/premake_modules/usage/usage.lua` — guard so the custom
  `uses` API doesn't collide with the one premake5 ≥ beta8 ships in
  core.

### arm64 / 64-bit portability
- `src_rebuild/Game/driver2.h` — `trap()` now uses `__builtin_trap()`
  instead of the x86-only `__asm__("int3")`.
- `src_rebuild/PsyCross/include/psx/libgpu.h` — `P_LEN = 3` on arm64
  (same value used for x86_64), so the prim-tag struct lays out
  identically across all 64-bit targets.
- `src_rebuild/PsyCross/include/psx/types.h` — on LP64 (macOS arm64/x64,
  Linux x64) `u_long` and `ulong` map to `uint32_t` so the PSX 32-bit
  semantics are preserved. Pre-defines `_U_LONG`/`_U_INT`/`_U_CHAR`/
  `_U_SHORT` on macOS to stop `<sys/types.h>` from re-declaring those
  types as 64-bit.
- `premake5.lua` adds a forced `-include` of `psx/types.h` on the macOS
  filter so those guards are seen before any system header.

### macOS-specific headers
- `<malloc.h>` (non-existent on macOS) replaced by `<stdlib.h>` with a
  guard in:
  - `src_rebuild/PsyCross/src/psx/LIBCD.C`
  - `src_rebuild/utils/fs.cpp`
  - `src_rebuild/utils/audio_source/snd_wav_cache.cpp`
  - `src_rebuild/utils/targa.cpp`
  - `src_rebuild/Game/dr2locale.c`
  - `src_rebuild/tools/font_tool/font_tool_main.cpp`
- `LIBCD.C` and `utils/fs.{cpp,h}` — `__unix__` guards extended to
  include `__APPLE__` (macOS doesn't define `__unix__`).

### Pointer→int casts on LP64
Pointers are 64-bit on arm64/x86_64; `(int)ptr` loses information and
clang treats that as an error. Routed through `intptr_t` /
`u_intptr`:
- `src_rebuild/Game/dr2locale.h` — `GET_GAME_TXT`/`GET_MISSION_TXT`
- `src_rebuild/Game/C/civ_ai.c` — `Random2((int)straight)`
- `src_rebuild/Game/C/dr2roads.c` — `(int)plane & 3`
- `src_rebuild/Game/C/draw.c` — `primtab`/`primptr` checks
- `src_rebuild/Game/C/event.c` — `FIXEDH((int)ev->node * RSIN(...))`
- `src_rebuild/Game/C/glaunch.c` — `(int)param` in several callbacks
- `src_rebuild/Game/C/mission.c` — `(u_int)((char*)...)`

### Stricter C++ checks
- `src_rebuild/PsyCross/src/psx/LIBETC.C` — pointer→int cast routed
  via `intptr_t` (`ResetCallback`/`VSyncCallback`).
- `src_rebuild/PsyCross/src/psx/LIBGPU.C` — explicit `(DR_TPAGE*)opri`
  cast.
- `src_rebuild/PsyCross/src/psx/LIBSPU.C` — added `psx/libetc.h`
  include for `ResetCallback()`.

### Missing GTE function
- `src_rebuild/Game/C/targets.c:327` — `RotTransPers()` is declared but
  not defined inside PsyCross. Replaced with the equivalent
  `gte_RotTransPers()` macro and the otz output captured locally.

## Status

- ✅ Clean build on arm64 (Apple Silicon).
- ✅ Native Mach-O arm64 binary (`file` confirms `arm64`).
- ⚠️ macOS OpenGL has been *deprecated* since 10.14 but the legacy
  driver still works up to OpenGL 4.1. PsyCross uses GL 2.x so it
  runs, though Apple's GL-on-Metal compatibility layer has subtly
  different sync behaviour and produces flicker / dropped primitives
  on some scenes.
- ⚠️ The Vulkan / MoltenVK backend (opt-in via `--renderer=vulkan`)
  side-steps the GL-on-Metal issues. Currently a work-in-progress —
  Driver 2 main menu, HUD and 3D world geometry render; some passes
  (blend modes, stencil, scissor, framebuffer-back-to-VRAM) are still
  in flight.
- ⚠️ A full playtest hasn't been run end-to-end — the game requires
  the original Driver 2 assets to launch.
