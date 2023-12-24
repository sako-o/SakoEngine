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
    ];
    sdlDeps = with pkgs; [
      # xorg deps
      xorg.libX11
      xorg.xorgproto
      xorg.libICE
      xorg.libXi
      xorg.libXScrnSaver
      xorg.libXcursor
      xorg.libXinerama
      xorg.libXext
      xorg.libXrandr
      xorg.libXxf86vm
      xorg.libXext
      xorg.libXext.dev
      xorg.libxcb
      xorg.libxcb.dev
      # for audio libraries
      pipewire
      libpulseaudio
      alsa-lib
      audiofile
      sndio
      # drm support
      libdrm
      mesa
      # graphics
      libGL
      vulkan-headers
      vulkan-loader
      vulkan-tools
      vulkan-validation-layers
      # wayland deps
      wayland
      wayland-scanner
      # extras
      zlib
      libzip
      udev
      libiconv
    ];
    windowsNativeBuildInputs = with pkgs; [
      pkgsCross.mingwW64.buildPackages.gcc
    ];
  in {
    devShells.${system}.default = pkgs.mkShell {
      packages = [
        nativeBuildInputs
        sdlDeps
        windowsNativeBuildInputs
      ];
      mingwW64dir = "${pkgs.pkgsCross.mingwW64.buildPackages.gcc}";
    };
  };
}
