with import <nixpkgs> {};

mkShell {
  nativeBuildInputs = [
    pkg-config 
    cmake 
    gnumake
    gcc
  ];
  buildInputs = [
    xorg.libX11 
    xorg.libXext
    xorg.libXrandr
    xorg.libXcursor
    xorg.xinput
    SDL2
    SDL2_image
    glfw
    glew
    libzip
  ];

}
