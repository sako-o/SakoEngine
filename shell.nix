with import <nixpkgs> {};

mkShell {
  nativeBuildInputs = [ pkg-config cmake ];
  buildInputs = [ xorg.libX11 ];
}
