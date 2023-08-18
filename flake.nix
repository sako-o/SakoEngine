{
  description = "SakoEngine flake";
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-23.05";
  };
  outputs = {nixpkgs, ...}: let
    system = "x86_64-linux";
    pkgs = nixpkgs.legacyPackages.${system};

    nativeBuildInputs = with pkgs; [
      clang-tools
      pkg-config
      cmake
      gnumake
    ];
    buildInputs = with pkgs; [
      # SDL2
      SDL2.dev
      SDL2_image
    ];
  in {
    devShells.${system}.default = pkgs.mkShell {
      packages = [
        nativeBuildInputs
        buildInputs
      ];
      # ...
    };
  };
}
