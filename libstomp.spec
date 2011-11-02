Name: libstomp
Version: 0.1.0
Release:	1%{?dist}
Summary: Libstomp is a C library used to talk the Stomp which is simple to implement client protocol for working with ActiveMQ and other messaging systems.

Group:		
License: Apache License
URL: http://stop.codehaus.org/
Source0:	
BuildRoot:	%(mktemp -ud %{_tmppath}/%{name}-%{version}-%{release}-XXXXXX)

BuildRequires: apr-devel
Requires: apr

%description
Libstomp is a C library used to talk the Stomp which is simple to implement client protocol for working with ActiveMQ and other messaging systems.

%prep
%setup -q


%build
%configure
make %{?_smp_mflags}


%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT


%clean
rm -rf $RPM_BUILD_ROOT


%files
%defattr(-,root,root,-)
%doc



%changelog

