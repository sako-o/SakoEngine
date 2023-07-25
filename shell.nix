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
    ## END XORG ##
    ## WAYLAND ##
    ## END WAYLAND ##
    # OpenGL support for windows
    freeglut
    glew
    glfw
    mesa
    # We build SDL from source to get to
    # SDL3, so we don't need this 
    #SDL2
    #SDL2_image
    # Extras go here
    libzip
  ];

}
