{ pkgs ? import (fetchTarball "https://github.com/NixOS/nixpkgs/archive/ca012a02bf8327be9e488546faecae5e05d7d749.tar.gz") {} }:

pkgs.llvmPackages_16.stdenv.mkDerivation {
  name = "cashew-nix-shell";
  buildInputs = with pkgs; [
    catch2_3
    clang_16
    cmake
    cxxopts
    libffi
    libxml2
    llvmPackages_16.libllvm
    ninja
    sphinx
  ];
  shellHook = ''
    export CMAKE_GENERATOR=Ninja
  '';
}

