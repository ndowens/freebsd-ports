# $FreeBSD$

PORTNAME=	xen
PKGNAMESUFFIX=	-tools
PORTVERSION=	4.12.1
PORTREVISION=	0
CATEGORIES=	sysutils emulators
MASTER_SITES=	http://downloads.xenproject.org/release/xen/${PORTVERSION}/

MAINTAINER=	royger@FreeBSD.org
COMMENT=	Xen management tools

LICENSE=	GPLv2 LGPL3
LICENSE_COMB=	multi

LIB_DEPENDS=	libyajl.so:devel/yajl \
		liblzo2.so:archivers/lzo2 \
		libpixman-1.so:x11/pixman \
		libargp.so:devel/argp-standalone
BUILD_DEPENDS=	seabios>0:misc/seabios
RUN_DEPENDS=	seabios>0:misc/seabios
DOCS_BUILD_DEPENDS=markdown:textproc/markdown

OPTIONS_DEFINE=		DOCS SPICE
OPTIONS_DEFAULT=	DOCS
OPTIONS_SUB=		yes

SPICE_DESC=		Enable SPICE protocol for QEMU
SPICE_CONFIGURE_WITH=	extra-qemuu-configure-args="--enable-spice"
SPICE_BUILD_DEPENDS=	spice-protocol>=0.12.10:devel/spice-protocol
SPICE_LIB_DEPENDS=	libspice-server.so:devel/libspice-server

ONLY_FOR_ARCHS=	amd64
ONLY_FOR_ARCHS_REASON=	"not yet ported to anything other than amd64"

USES=		cpe gettext gmake libtool localbase:ldflags perl5 pkgconfig \
		python:2.7 shebangfix
USE_GNOME=	glib20
USE_LDCONFIG=	yes
HAS_CONFIGURE=	yes
# Set ARCH=x86_64 in order to overwrite the environment ARCH=amd64
MAKE_ARGS=	clang=y ARCH=x86_64

CONFIGURE_ARGS+=	--with-system-seabios=${LOCALBASE}/share/seabios/bios.bin \
			--mandir=${MANPREFIX}/man

SHEBANG_FILES=	tools/misc/xencov_split \
		tools/python/scripts/convert-legacy-stream \
		tools/python/scripts/verify-stream-v2 \
		tools/xenmon/xenmon.py

ALL_TARGET=		tools
DOCS_ALL_TARGET=	docs
INSTALL_TARGET=		install-tools
DOCS_INSTALL_TARGET=	install-docs

EXTRA_PATCHES+=	${PATCHDIR}/0001-tools-include-propagate-python-interpreter-path.patch:-p1

# LLD 8 changed the behaviour re the placement of orphaned sections, which
# produces a non-bootable Xen kernel:
#
# https://bugs.llvm.org/show_bug.cgi?id=42327
#
# Backport the fixes from upstream
EXTRA_PATCHES+=	${PATCHDIR}/0001-x86-linker-add-a-reloc-section-to-ELF-linker-script.patch:-p1 \
		${PATCHDIR}/0003-xen-link-handle-.init.rodata.cst-sections-in-the-lin.patch:-p1 \
		${PATCHDIR}/0004-x86-check-for-multiboot-1-2-header-presence.patch:-p1

.include <bsd.port.options.mk>

.if ${OPSYS} != FreeBSD
IGNORE=		only supported on FreeBSD
.endif

.if ${OSVERSION} < 1200074
IGNORE=		only supported on FreeBSD 12.0 or newer
.endif

.if ${PORT_OPTIONS:MSPICE} && ${OSVERSION} < 1300008
BROKEN=	SPICE support requires FreeBSD version 13.0 or higher
.endif

post-patch:
	@for p in `ls ${FILESDIR}/*qemuu*.patch 2>/dev/null`; do \
		${ECHO_CMD} "====> Applying $${p##*/}" ; \
		${PATCH} -s -p1 -i $${p} -d ${WRKSRC}/tools/qemu-xen ; \
	done

# The ports native 'build' target cannot be used because it sets CFLAGS, and
# that breaks the Xen kernel build system that's used by the tools in order to
# build the pv-shim.
do-build:
	${MAKE_CMD} -j${MAKE_JOBS_NUMBER} -C ${WRKSRC} ${MAKE_ARGS} ${ALL_TARGET}

do-install:
	${MAKE_CMD} -j${MAKE_JOBS_NUMBER} -C ${WRKSRC} ${MAKE_ARGS} ${INSTALL_TARGET}

post-install:
	${MKDIR} ${STAGEDIR}/var/run/xen

.include <bsd.port.mk>
