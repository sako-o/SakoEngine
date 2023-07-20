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
    xorg.libX11
    xorg.libXrandr
    xorg.libXrender
    xorg.libXScrnSaver
    xorg.libXext
    xorg.libXft
    xorg.libXpm.out
    xorg.libXrandr
    xorg.libXrender
    libGL
    SDL2
    SDL2_image
    glfw
    glew
    libzip
  ];

}
