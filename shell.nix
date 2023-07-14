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
    glfw
    glew
    libzip
  ];

}
