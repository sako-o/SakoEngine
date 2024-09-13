{
  description = "SakoEngine Flake";

  inputs = { nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable"; };

  outputs = { self, nixpkgs }:
    let
      inherit (nixpkgs) lib;
      inherit (builtins) attrValues;
      eachSystem = f:
        lib.genAttrs [ "x86_64-linux" "aarch64-linux" ]
        (system: f nixpkgs.legacyPackages.${system});
    in {

      # packages = eachSystem (pkgs: rec {
      #   default = sakoEngine;
      #   sakoEngine = pkgs.callPackage ./package.nix { };
      # });

      devShells = eachSystem (pkgs: {
        default = pkgs.mkShell {
         packages = attrValues { inherit (pkgs) cmake gcc; };
        };
      });

      formatter = eachSystem (pkgs: pkgs.alejandra);

    };
}
