# Created by: Nicola Vitale <nivit@email.it>
# $FreeBSD$

PORTNAME=	wxmaxima
PORTVERSION=	19.10.0
DISTVERSIONPREFIX=	Version-
CATEGORIES=	math

MAINTAINER=	phascolarctos@protonmail.ch
COMMENT=	WxWidgets GUI for the computer algebra system maxima

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/COPYING

RUN_DEPENDS=	maxima:math/maxima

USES=		cmake desktop-file-utils shared-mime-info
USE_WX=		3.0
USE_GITHUB=	yes
GH_ACCOUNT=	wxMaxima-Developers

PLIST_SUB=	DESKTOPDIR=${DESKTOPDIR:S,${PREFIX}/,,}
WX_COMPS=	wx
WX_CONF_ARGS=	absolute

OPTIONS_DEFINE=	NLS
OPTIONS_SUB=	yes

NLS_EXTRA_PATCHES_OFF=	${PATCHDIR}/extra-patch-CMakeLists.txt
NLS_USES=	gettext

.include <bsd.port.mk>
