{
  description = "A Nix-flake-based C/C++ development environment";

  inputs.nixpkgs.url = "https://flakehub.com/f/NixOS/nixpkgs/0.1.*.tar.gz";

  outputs = { self, nixpkgs }:
    let
      supportedSystems = [ "x86_64-linux" "aarch64-linux" "x86_64-darwin" "aarch64-darwin" ];
      forEachSupportedSystem = f: nixpkgs.lib.genAttrs supportedSystems (system: f {
        pkgs = import nixpkgs { inherit system; };
      });
    in
    {
      devShells = forEachSupportedSystem ({ pkgs }: {
        default = pkgs.mkShell.override
          { # Override stdenv in order to change compiler:
            # stdenv = pkgs.clangStdenv;
          }
          {
            packages = with pkgs; [
              clang-tools
              cmake
              codespell
              conan
              cppcheck
              doxygen
              gtest
              lcov
              vcpkg
              vcpkg-tool
              SDL2
            ] ++ (if system == "aarch64-darwin" then [ ] else [ gdb ]);
          };
      });

      packages.x86_64-linux.doxygen =
        with import nixpkgs { system = "x86_64-linux"; };
        stdenv.mkDerivation {
          name = "document";
          src = ./.;
          buildInputs = with pkgs; [ doxygen ];
          buildPhase = ''
            doxygen
          '';
          installPhase = ''
            mkdir -p $out/html
            cp -r html/* $out/html/
          '';
        };
                

      packages.x86_64-linux.default =
        with import nixpkgs { system = "x86_64-linux"; };
        stdenv.mkDerivation {
          name = "shooter";
          src = ./src;
          buildInputs = with pkgs; [ SDL2 ];
          buildPhase = ''
            g++ -o shooter \
                main.cpp \
                base.cpp \
                triangle.cpp \
                matrix.cpp \
                v2.cpp \
                v3.cpp \
                v4.cpp \
                hsl.cpp \
                mesh.cpp \
                `sdl2-config --cflags --libs`
          '';
          installPhase = ''
            mkdir -p $out/bin
            cp shooter $out/bin/shooter
          '';
        };

    };
}

