{ pkgs ? (import <nixpkgs> ){ } }: {
  default = pkgs.mkShell {
    # Enable experimental features without having to specify the argument
    nativeBuildInputs = with pkgs; [ xorg.libX11 ];
  };
}
