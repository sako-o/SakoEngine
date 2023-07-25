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
    xorg.xorgproto
    ## END XORG ##
    ## WAYLAND ##
    ## END WAYLAND ##
    # SDL Requirements
    libdrm
    # OpenGL support for windows
    freeglut
    libGL
    mesa
    mesa_glu
    # We build SDL from source to get to
    # SDL3, so we don't need this 
    #SDL2
    #SDL2_image
    # Extras go here
    libzip
  ];

  LD_LIBRARY_PATH="/run/opengl-driver/lib:/run/opengl-driver-32/lib";

}
