{ pkgs ? import (fetchTarball "https://github.com/NixOS/nixpkgs/archive/841889913dfd06a70ffb39f603e29e46f45f0c1a.tar.gz") {} }:

pkgs.llvmPackages_15.stdenv.mkDerivation {
  name = "cashew-nix-shell";
  buildInputs = with pkgs; [
    catch2_3
    clang_15
    cmake
    cxxopts
    libffi
    libxml2
    llvmPackages_15.libllvm
    sphinx
  ];
}

