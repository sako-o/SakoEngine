{
  description = "SakoEngine Flake";

  inputs = {nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";};

  outputs = {
    self,
    nixpkgs,
  }: let
    inherit (nixpkgs) lib;
    inherit (builtins) attrValues;
    eachSystem = f:
      lib.genAttrs ["x86_64-linux"]
      (system: f nixpkgs.legacyPackages.${system});
  in {
    #     packages = eachSystem (pkgs: rec {
    # default = sakoEngine;
    # sakoEngine = pkgs.callPackage ./package.nix { };
    #       SDL3 = pkgs.callPackage ./nix/sdl3.nix { };
    #     });

    devShells = eachSystem (pkgs: {
      default = pkgs.mkShell {
        packages = attrValues {
          inherit
            (pkgs)
            meson
            cmake # we need this apparently for some libraries...?????? what????
            ninja
            gcc
            gdb
            pkg-config
            #sdl3
            #libGL
            #glew
            glm
            glfw
            vulkan-headers
            vulkan-loader
            vulkan-tools
            vulkan-validation-layers
            clang-tools
            cmake-language-server
            wayland # the way land
            shaderc # shaders whatever it was called
            ;
        };
      };
    });

    formatter = eachSystem (pkgs: pkgs.alejandra);
  };
}
