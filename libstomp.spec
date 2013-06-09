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
%define soname  libstomp0
Name:           libstomp
Version:        0.1.0
Release:        0
License:        Apache-2.0
Summary:        C library used to talk the Stomp 
Url:            https://github.com/bmanojlovic/libstomp
Group:          Development/Libraries/C and C++
Source:         %{name}-%{version}.tar.bz2
BuildRequires:  autoconf
BuildRequires:  automake
BuildRequires:  libtool
BuildRequires:  pkg-config
BuildRequires:  libapr1-devel
BuildRoot:      %{_tmppath}/%{name}-%{version}-build

%description
libstomp is a c library used to talk the Stomp which
is a simple to implement client protocol for
working with ActiveMQ and other messaging systems.


%package -n %soname
Summary:        C library used to talk the Stomp
Group:          Development/Libraries/C and C++

%description -n %soname
libstomp is a c library used to talk the Stomp which
is a simple to implement client protocol for
working with ActiveMQ and other messaging systems.

%package devel
Summary:        Development files for libstomp
Group:          Development/Libraries/C and C++
Requires:       %{name} = %{version}

%description devel
Development files for libstomp STOMP implementation

%prep
%setup -q

%build
autoreconf -i
%configure
make %{?_smp_mflags}

%install
make install DESTDIR=%buildroot

%post -n %soname -p /sbin/ldconfig

%postun -n %soname -p /sbin/ldconfig

%files -n %soname
%defattr(-,root,root)
%doc %attr(0644,root,root) ChangeLog README COPYING
%exclude %{_libdir}/libstomp.a
%exclude %{_libdir}/libstomp.la
%{_libdir}/libstomp.so.*

%files devel
%defattr(-,root,root)
%{_includedir}/stomp.h
%{_libdir}/libstomp.so

%changelog
