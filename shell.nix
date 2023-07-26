with import <nixpkgs> {};

mkShell {
  nativeBuildInputs = [
    clang
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
    # SDL Requirements
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
    libzip
    udev
    libiconv
    # audio
    libpulseaudio
    pipewire
    # lsp for neovim
  ];

  LD_LIBRARY_PATH="/run/opengl-driver/lib:/run/opengl-driver-32/lib";

}
