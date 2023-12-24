{
  description = "SakoEngine flake";
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-23.11";
  };
  outputs = {nixpkgs, ...}: let
    system = "x86_64-linux";
    pkgs = nixpkgs.legacyPackages.${system};

    nativeBuildInputs = with pkgs; [
      clang-tools
      pkg-config
      cmake
      gnumake
      gcc
    ];
    buildInputs = with pkgs; [
      # OpenGL
      libGL
      # Vulkan
      vulkan-headers
      vulkan-loader
      vulkan-tools
      vulkan-validation-layers
      # SDL2
      SDL2.dev
      SDL2_image
    ];
    windowsNativeBuildInputs = with pkgs; [
      pkgsCross.mingwW64.buildPackages.gcc
    ];
  in {
    devShells.${system}.default = pkgs.mkShell {
      packages = [
        nativeBuildInputs
        buildInputs
        windowsNativeBuildInputs
      ];
      mingwW64dir = "${pkgs.pkgsCross.mingwW64.buildPackages.gcc}";
    };
  };
}
