# default.nix
with import <nixpkgs> {};
stdenv.mkDerivation rec {
    name = "dev-environment"; # Probably put a more meaningful name here
    nativeBuildInputs = [
      pkg-config
      gcc
      gnumake
    ];
    buildInputs = [ 
      xorg.libX11.dev 
      xorg.libXxf86vm.dev
      xorg.libxkbfile.dev
      xorg.libXv.dev
      xorg.libxrandr.dev
      zlib
    ];

    #LD_LIBRARY_PATH = "${lib.makeLibraryPath buildInputs}";
    X11_X11_INCLUDE_PATH = "${pkgs.xorg.libX11.dev}/include";
    X11_X11_LIB = "${pkgs.xorg.libX11.dev}/lib";
}
