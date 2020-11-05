# Maintainer: Marco Pompili <aur@mg.odd.red>
# Contributor: Anatol Pomozov <anatol.pomozov@gmail.com>
# Contributor: Bartłomiej Piotrowski <nospam@bpiotrowski.pl>
# Contributor: Kaiting Chen <kaitocracy@gmail.com>
# Contributor: tocer <tocer.deng@gmail.com>
# Contributor: David Flemström <david.flemstrom@gmail.com>

pkgname=d8
pkgver=8.4
pkgrel=1
pkgdesc="Fast and modern Javascript engine used in Google Chrome."
arch=('i686' 'x86_64')
url="https://v8.dev"
license=('BSD')
depends=('readline')
makedepends=('clang' 'python2' 'python2-colorama' 'ninja' 'git' 'wget')
conflicts=('v8-3.14' 'v8-3.14-bin' 'v8-3.15' 'v8-3.20' 'v8-6.7-static' 'v8-6.8' 'v8-r' 'v8-static-gyp' 'v8-static-gyp-5.4')
source=("depot_tools::git+https://chromium.googlesource.com/chromium/tools/depot_tools.git"
        "d8")
sha256sums=('SKIP'
            '6abb07ab1cf593067d19028f385bd7ee52196fc644e315c388f08294d82ceff0')

#
# Custom configuration for V8
#

# clang_base_path: Set clang path when not using the clang bundled with V8.
V8_CLANG_PATH="/usr/"

# is_clang: Set to true when compiling with the Clang compiler. Typically this
# is used to configure warnings.
V8_IS_CLANG=false

# is_component_build: Component build. Setting to true compiles targets declared
# as "components" as shared libraries loaded dynamically.
# This speeds up development time.
# When false, components will be linked statically.
V8_COMPONENT_BUILD=true

# is_debug: Enabling official builds (V8_OFFICIAL_BUILD) automatically sets is_debug to false.
V8_DEBUG=false

# is_official_build: Set to enable the official build level of optimization.
# This has nothing to do with branding, but enables an additional level of
# optimization above release (!is_debug). This might be better expressed
# as a tri-state (debug, release, official) but for historical reasons there
# are two separate flags.
V8_OFFICIAL_BUILD=false

# v8_enable_i18n_support: Enable ECMAScript Internationalization API.
# Enabling this feature will add a dependency on the ICU library.
V8_I18N_SUPPORT=false

# v8_use_external_startup_data: Use external files for startup data blobs:
# the JS builtins sources and the start snapshot.
V8_USE_EXTERNAL_STARTUP_DATA=""

# Use sysroot
V8_USE_SYSROOT=false

# treat_warnings_as_errors: Default to warnings as errors for default workflow,
# where we catch warnings with known toolchains. Allow overriding this e.g.
# for Chromium builds on Linux that could use a different version of the compiler.
# With GCC, warnings in no-Chromium code are always not treated as errors.
V8_WARNINGS_AS_ERRORS=false

case "$CARCH" in
  x86_64) V8_ARCH="x64" ;;
  i686) V8_ARCH="ia32" ;;
esac

OUTFLD=out/x64.release

_export_py2()
{
  export PATH=${srcdir}/bin:`pwd`/depot_tools:"$PATH"
  msg2 "Using: `which python`"
}

prepare()
{
  export CC=/usr/bin/clang
  export CXX=/usr/bin/clang++
  
  # Switching to python2 system environment
  mkdir -p bin
  ln -sf /usr/bin/python2 ./bin/python
  ln -sf /usr/bin/python2-config ./bin/python-config

  _export_py2
  export GYP_GENERATORS=ninja

  if [ ! -d "v8" ]; then
    msg2 "Fetching V8 code"
    yes | fetch v8
  fi

  cd v8

  msg2 "Reset repository"
  git reset --hard

  msg2 "Syncing, this might take a while..."
  gclient sync

}

build()
{
  _export_py2
  cd v8
  msg2 "Building, this will take a while..."
  tools/dev/gm.py x64.release
}

package()
{
  cd v8
  install -d ${pkgdir}/usr/lib/v8
  install -Dm755 $OUTFLD/d8 ${pkgdir}/usr/lib/v8/d8
  install -Dm755 $OUTFLD/snapshot_blob.bin ${pkgdir}/usr/lib/v8/snapshot_blob.bin
  install -Dm755 ${srcdir}/d8 ${pkgdir}/usr/bin/d8
}
