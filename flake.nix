{
  description = "REDRIVER2 - portable Linux AppImage build";

  inputs = {
    self.submodules = true; # src_rebuild/PsyCross
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
      lib = pkgs.lib;

      version = "8.0-${self.shortRev or self.dirtyShortRev or "dirty"}";

      # The repo's premake_modules/usage clashes with newer premake ("name 'uses' in use"),
      # so use the same prebuilt 5.0.0-beta1 as CI.
      premake5-beta1 = pkgs.stdenv.mkDerivation {
        pname = "premake5";
        version = "5.0.0-beta1";
        src = pkgs.fetchurl {
          url = "https://github.com/premake/premake-core/releases/download/v5.0.0-beta1/premake-5.0.0-beta1-linux.tar.gz";
          hash = "sha256-B0/Ae+F4iO9BygfuocUnw5CgTqRVC/eWLusL6gzJ0vU=";
        };
        sourceRoot = ".";
        nativeBuildInputs = [ pkgs.autoPatchelfHook ];
        installPhase = "install -Dm755 premake5 $out/bin/premake5";
      };

      redriver2 = pkgs.stdenv.mkDerivation {
        pname = "redriver2";
        inherit version;
        src = lib.cleanSource ./.;

        nativeBuildInputs = [ premake5-beta1 ];
        buildInputs = with pkgs; [ SDL2 openal libjpeg libGL ];

        # premake hardcodes /usr/include/SDL2
        env.NIX_CFLAGS_COMPILE = "-I${lib.getDev pkgs.SDL2}/include/SDL2";
        env.APPVEYOR_BUILD_VERSION = version;

        configurePhase = ''
          runHook preConfigure
          cd src_rebuild
          premake5 gmake2
          runHook postConfigure
        '';

        buildPhase = ''
          runHook preBuild
          make -C build config=release_x64 REDRIVER2 -j$NIX_BUILD_CORES
          runHook postBuild
        '';

        installPhase = ''
          runHook preInstall
          install -Dm755 bin/Release/REDRIVER2 $out/bin/REDRIVER2
          runHook postInstall
        '';
      };

      # Static AppImage type2 runtime (prepended to the squashfs image)
      appimage-runtime = pkgs.fetchurl {
        url = "https://github.com/AppImage/type2-runtime/releases/download/20251108/runtime-x86_64";
        hash = "sha256-L8qLRDySUQ8Ug6iD9gBhrQm0a5eLJjHIB82HOkfsJg0=";
      };

      # Everything except the game data. The binary, its full library closure,
      # the glibc loader and Mesa are bundled so nothing is taken from the host.
      appdir =
        let
          # libraries SDL3, glvnd and openal-soft dlopen() at runtime
          runtimeLibs = with pkgs; [
            mesa libglvnd sdl3 libx11 libxext libxcursor libxi libxfixes libxrandr
            libxscrnsaver libxkbcommon wayland libdecor libpulseaudio alsa-lib
            systemdLibs dbus libdrm
          ];
          dlopenRoots = [
            "libGLX_mesa.so.0" "libEGL_mesa.so.0" "libGL.so.1" "libGLX.so.0" "libEGL.so.1"
            "libOpenGL.so.0" "libGLESv2.so.2" "libSDL3.so.0"
            "libX11.so.6" "libX11-xcb.so.1" "libXext.so.6" "libXcursor.so.1" "libXi.so.6"
            "libXfixes.so.3" "libXrandr.so.2" "libXss.so.1" "libxkbcommon.so.0"
            "libwayland-client.so.0" "libwayland-egl.so.1" "libwayland-cursor.so.0"
            "libdecor-0.so.0" "libpulse.so.0" "libasound.so.2" "libudev.so.1" "libdbus-1.so.3"
          ];
          closure = pkgs.closureInfo { rootPaths = [ redriver2 ] ++ runtimeLibs; };
          python = pkgs.python3.withPackages (ps: [ ps.pyelftools ]);
          eglVendor = pkgs.writeText "50_mesa.json" (builtins.toJSON {
            file_format_version = "1.0.0";
            ICD.library_path = "libEGL_mesa.so.0";
          });
        in
        pkgs.runCommand "redriver2-appdir-${version}" { } ''
          mkdir -p $out/usr/bin $out/usr/lib $out/usr/share/redriver2 \
            $out/usr/share/glvnd/egl_vendor.d

          install -m755 ${redriver2}/bin/REDRIVER2 $out/usr/bin/

          # the DT_NEEDED closure of the game, the Mesa DRI loader and the
          # dlopen()ed libraries, one file per soname (glibc's loader included)
          for p in $(cat ${closure}/store-paths); do
            for d in "$p/lib" "$p/lib/pulseaudio"; do [ -d "$d" ] && echo "$d"; done
          done > libdirs
          mkdir -p $out/usr/lib/dri
          cp -P ${pkgs.mesa}/lib/dri/*_dri.so $out/usr/lib/dri/
          install -m755 ${pkgs.mesa}/lib/dri/libdril_dri.so $out/usr/lib/dri/
          ${python}/bin/python3 ${./appimage/bundle_libs.py} $out/usr/lib libdirs \
            $out/usr/bin/REDRIVER2 $out/usr/lib/dri/libdril_dri.so ${toString dlopenRoots}
          cp ${eglVendor} $out/usr/share/glvnd/egl_vendor.d/50_mesa.json

          # default config: no CD image (data is pre-extracted), fullscreen
          sed -e 's/^image=/# image=/' -e 's/^fullscreen=0/fullscreen=1/' \
            ${./data/config.ini} > $out/usr/share/redriver2/config.ini

          install -m755 ${./appimage/AppRun} $out/AppRun
          install -m644 ${./.flatpak/icon.png} $out/redriver2.png
          ln -s redriver2.png $out/.DirIcon
          cat > $out/redriver2.desktop <<EOF
          [Desktop Entry]
          Type=Application
          Name=REDRIVER2
          Comment=Reverse-engineered Driver 2
          Icon=redriver2
          Exec=REDRIVER2
          Categories=Game;
          EOF
          chmod -R u+w $out
        '';

      tools = pkgs.buildEnv {
        name = "redriver2-appimage-tools";
        paths = with pkgs; [ python3 jdk_headless squashfsTools coreutils findutils ];
      };
    in
    {
      packages.${system} = {
        inherit redriver2 appdir appimage-runtime tools;
        default = appdir;
      };

      devShells.${system}.default = pkgs.mkShell {
        inputsFrom = [ redriver2 ];
        packages = [ tools pkgs.gnumake ];
      };
    };
}
