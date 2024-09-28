{ stdenv, fetchFromGitHub }:
let
  pinned = "7d21a49c9cac39e8803ce152b121470ec5bbb77f";
in
stdenv.mkDerivation {
  pname = "SDL3";
  version = "${pinned}";

  src = fetchFromGitHub {
    owner = "libsdl-org";
    repo = "SDL";
    rev = "${pinned}";
    hash = "sha256-ij9/VhSacUaPbMGX1hx2nz0n8b1tDb1PnC7IO9TlNhE=";
  };
}
