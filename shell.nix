with import <nixpkgs> {};

let
  buildInputs = [ xorg.libX11.dev xorg.libXext ];
in

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
    
  ];

}
