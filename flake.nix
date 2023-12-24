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
      # FIXME: Surely theres a better way to this? We are we adding .dev for #include to work
      xorg.libX11
      xorg.libX11.dev
      xorg.xorgproto
      xorg.xorgproto.dev
      xorg.libICE
      xorg.libICE.dev
      xorg.libXi
      xorg.libXi.dev
      xorg.libXScrnSaver
      xorg.libXScrnSaver.dev
      xorg.libXcursor
      xorg.libXcursor.dev
      xorg.libXinerama
      xorg.libXinerama.dev
      xorg.libXext
      xorg.libXext.dev
      xorg.libXrandr
      xorg.libXrandr.dev
      xorg.libXxf86vm
      xorg.libXxf86vm.dev
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
