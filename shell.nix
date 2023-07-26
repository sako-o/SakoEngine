with import <nixpkgs> {};

mkShell {
  nativeBuildInputs = [
    clang-tools
    pkg-config 
    cmake 
    gnumake
    gcc
  ];
  buildInputs = [
    ## XORG ##
    xorg.libX11
    xorg.libXrandr
    xorg.libXrender
    xorg.libXScrnSaver
    xorg.libXext
    xorg.libXft
    xorg.libXpm.out
    xorg.libXrandr
    xorg.libXrender
    xorg.libXcursor
    xorg.xinput
    xorg.libXi
    xorg.libICE
    xorg.xorgproto
    xorg.libXinerama
    xorg.libXxf86vm
    ## END XORG ##
    ## WAYLAND ##
    ## END WAYLAND ##
    # Nvidia Proprietary Linux  
    libdrm
    mesa
    # OpenGL support for windows
    libGL
    # vulkan
    vulkan-headers
    vulkan-loader
    vulkan-validation-layers
    # We build SDL from source to get to
    # SDL3, so we don't need this 
    #SDL2
    #SDL2_image
    # Extras go here
    zlib
    libzip
    udev
    libiconv
    # audio
    libpulseaudio
    pipewire
    # lsp for neovim
  ];

}
