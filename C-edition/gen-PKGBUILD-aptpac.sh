#!/bin/bash

#$1 = version
#$2 = the filename to use for the PKGBUILD, default is 'PKGBUILD'
#$3 = pkgrel, default is 1

function error() {
	echo -e "\e[31mERROR: $1\e[0m"
	exit 1
}

[[ -z $1 ]] && error "no version provided!"
filename="${2:-PKGBUILD}"
pkgrel="${3:-1}"

echo "checking if version \"$1\" exists..."
if ! curl --output /dev/null --silent --head --fail "https://github.com/Itai-Nelken/aptpac/releases/download/$1/aptpac-$1-src.tar.xz"; then
	error "source file does not exist! incorrect version?"
fi

echo "getting sha256sum..."

sha256="$(wget -qO- https://github.com/Itai-Nelken/aptpac/releases/download/$1/sha256sums.txt | cat | grep aptpac-$1-src.tar.xz | sed "s/ aptpac-$1-src.tar.xz//g" | sed 's/ //g')"

echo "creating PKGBUILD with name \"$filename\"..."

echo 'pkgname="aptpac-c"' > $filename
echo "pkgver=\"${1}\"" >> $filename
echo "pkgrel=\"${pkgrel}\"" >> $filename
echo "source=(https://github.com/Itai-Nelken/aptpac/releases/download/$1/aptpac-$1-src.tar.xz)" >> $filename
echo "sha256sums=('$sha256')" >> $filename
echo 'pkgdesc="A simple pacman wrapper with a syntax similar to apt."' >> $filename
echo "arch=('any')" >> $filename
echo 'url="https://github.com/Itai-Nelken/aptpac"' >> $filename
echo "license=('MIT')" >> $filename
echo "depends=('glibc')" >> $filename
echo "makedepends=('gcc' 'make' 'glibc' 'cmake')" >> $filename
echo -e 'build() {\n\tcd aptpac-${pkgver}-src\n\tmkdir build\n\tcd build\n\tcmake -DCMAKE_BUILD_TYPE=Release ..\n\tmake\n}' >> $filename
echo -e 'package() {\n\tmkdir -p ${pkgdir}/usr/bin\n\tcd aptpac-${pkgver}-src\n\tinstall -m 755 build/aptpac "${pkgdir}/usr/bin/aptpac"\n}' >> $filename

echo "done"
exit 0
