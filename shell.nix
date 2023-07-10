{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
     nativeBuildInputs = with pkgs; [
      xorg.libX11
      xorg.libX11.dev
      xorg.libxcb.dev
      pkg-config
    ];
}
