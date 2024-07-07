{
  description = "SakoEngine flake";
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-24.05";
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
      glslang 
      vulkan-headers
      vulkan-loader
      vulkan-validation-layers
    ];
  in {
    # TODO:: Pre commit hooks
    devShells.${system}.default = pkgs.mkShell {
      packages = [
        nativeBuildInputs
        buildInputs
      ];
    };
  };
}
