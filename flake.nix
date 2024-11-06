{
  description = "SakoEngine Flake";

  inputs = { nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable"; };

  outputs = { self, nixpkgs }:
    let
      inherit (nixpkgs) lib;
      inherit (builtins) attrValues;
      eachSystem = f:
        lib.genAttrs [ "x86_64-linux" ]
        (system: f nixpkgs.legacyPackages.${system});
    in {

      packages = eachSystem (pkgs: rec {
        # default = sakoEngine;
        # sakoEngine = pkgs.callPackage ./package.nix { };
        SDL3 = pkgs.callPackage ./nix/sdl3.nix { };
      });

      devShells = eachSystem (pkgs: {
        default = pkgs.mkShell {
          packages = attrValues {
            inherit (pkgs)
              cmake gcc gdb pkg-config SDL2 glew glm vulkan-headers
              vulkan-loader vulkan-tools;
            inherit (self.packages."x86_64-linux") SDL3;
          };
        };
      });

      formatter = eachSystem (pkgs: pkgs.alejandra);

    };
}
