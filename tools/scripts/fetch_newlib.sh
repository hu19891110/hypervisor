#!/bin/bash -e
#
# Bareflank Hypervisor
#
# Copyright (C) 2015 Assured Information Security, Inc.
# Author: Rian Quinn        <quinnr@ainfosec.com>
# Author: Brendan Kerrigan  <kerriganb@ainfosec.com>
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

%ENV_SOURCE%

pushd $BUILD_ABS

echo "Fetching newlib. Please wait..."

n=0
until [ $n -ge 5 ]
do
    wget -nv ftp://sourceware.org/pub/newlib/newlib-2.3.0.20160226.tar.gz && break
    n=$[$n+1]
    sleep 15
done

tar xf newlib-*.tar.gz
mv newlib-*/ source_newlib
rm newlib-*.tar.gz

pushd source_newlib
patch -p1 < $HYPER_ABS/tools/patches/newlib.patch
if [[ $compiler == "clang_39" ]] || [[ $compiler == "gcc_"* ]] ; then
    patch -p1 < $HYPER_ABS/tools/patches/newlib_memcpy_memset.patch
fi
popd

popd
