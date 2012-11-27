#
# spec file for package 
#
# Copyright (c) specCURRENT_YEAR SUSE LINUX Products GmbH, Nuernberg, Germany.
#
# All modifications and additions to the file contributed by third parties
# remain the property of their copyright owners, unless otherwise agreed
# upon. The license for this file, and modifications and additions to the
# file, is the same license as for the pristine package itself (unless the
# license for the pristine package is not an Open Source License, in which
# case the license is the MIT License). An "Open Source License" is a
# license that conforms to the Open Source Definition (Version 1.9)
# published by the Open Source Initiative.

# Please submit bugfixes or comments via http://bugs.opensuse.org/
#

Name:           libstomp
Version:        0.1.0
Release:        0
License:        Apache-2.0
Summary:        C library used to talk the Stomp 
Url:            https://github.com/bmanojlovic/libstomp
Group:          BLAH
Source:         %{name}-%{version}.tar.bz2
BuildRequires:  autoconf
BuildRequires:  automake
BuildRequires:  libtool
BuildRequires:  libapr1-devel
BuildRoot:      %{_tmppath}/%{name}-%{version}-build

%description
libstomp is a c library used to talk the Stomp which
is a simple to implement client protocol for
working with ActiveMQ and other messaging systems.

%prep
%setup -q

%build
autoreconf -i
%configure
make %{?_smp_mflags}

%install
make install DESTDIR=%buildroot

%post

%postun

%files
%defattr(-,root,root)
%doc ChangeLog README COPYING

%changelog
