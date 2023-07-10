{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    nativeBuildInputs = with pkgs; [
      gcc
      xorg.libX11
      xorg.libX11.dev
    ];
    buildInputs = with pkgs; [
      glibc.static
      xorg.libX11
      xorg.libX11.dev
    ];

    LD_LIBRARY_PATH = "${lib.makeLibraryPath buildInputs}";
}
