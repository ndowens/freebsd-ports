# $FreeBSD$

PORTNAME=	cointop
PORTVERSION=	1.3.6
CATEGORIES=	finance

MAINTAINER=	ndowens04@gmail.com
COMMENT=	Light cryptocurrency coin stats

LICENSE=	APACHE20
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=		go:modules

USE_GITHUB=	yes
GH_ACCOUNT=	miguelmota

GO_BUILDFLAGS=	-ldflags="-X main.Version=${DISTVERSION}"

PLIST_FILES=	bin/cointop

.include <bsd.port.mk>
