# Created by: ijliao
# $FreeBSD$

PORTNAME=	linkchecker
PORTVERSION=	9.3
PORTREVISION=	5
CATEGORIES=	www python
MASTER_SITES=	CHEESESHOP
DISTNAME=	LinkChecker-${PORTVERSION}

MAINTAINER=	ports@FreeBSD.org
COMMENT=	Check HTML documents for broken links

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/COPYING

RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}dnspython>0:dns/py-dnspython@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}requests>=2:www/py-requests@${PY_FLAVOR}

WRKSRC=		${WRKDIR}/${DISTNAME}

USES=		cpe python:2.7
CPE_VENDOR=	bastian_kleineidam
USE_PYTHON=	distutils autoplist
INSTALLS_ICONS=	yes

OPTIONS_DEFINE=		CLAMAV EXAMPLES GTK2 LOGIN NLS \
			SQLITE3 SYNTAX
OPTIONS_DEFAULT=	SQLITE3 SYNTAX
OPTIONS_SUB=		yes

CLAMAV_DESC=		Clam Antivirus
CLAMAV_RUN_DEPENDS=	clamscan:security/clamav
GTK2_USE=		gnome=pygtk2
LOGIN_DESC=		Login form submission
LOGIN_RUN_DEPENDS=	twill>=0:www/twill
NLS_USES=		gettext
SQLITE3_RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}sqlite3>0:databases/py-sqlite3@${PY_FLAVOR}
SYNTAX_DESC=		HTML/CSS syntax check
SYNTAX_RUN_DEPENDS=\
		${PYTHON_PKGNAMEPREFIX}cssutils>=0.9.5:www/py-cssutils@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}utidylib>=0.2:www/py-utidylib@${PY_FLAVOR}

.include <bsd.port.options.mk>

post-patch:
	@${REINPLACE_CMD} -e \
		'/^Icon/s|=.*|=linkchecker|' ${WRKSRC}/doc/*.desktop
	@${REINPLACE_CMD} -e 's|share/man|man|' ${WRKSRC}/setup.py

post-build:
.if ${PORT_OPTIONS:MNLS}
.for lang in de es fr
	(cd ${WRKSRC}/po && msgfmt -c -o ${lang}.mo ${lang}.po)
.endfor
.endif

post-install:
	${STRIP_CMD} ${STAGEDIR}${PYTHONPREFIX_SITELIBDIR}/linkcheck/*/*.so
.for i in 16 32 48 64 128
	@${MKDIR} ${STAGEDIR}${PREFIX}/share/icons/hicolor/${i}x${i}/apps
	(cd ${WRKSRC}/doc/html && ${INSTALL_DATA} logo${i}x${i}.png \
		${STAGEDIR}${PREFIX}/share/icons/hicolor/${i}x${i}/apps/linkchecker.png)
.endfor
	@${MKDIR} ${STAGEDIR}${EXAMPLESDIR}
	(cd ${WRKSRC}/cgi-bin/lconline && ${INSTALL_DATA} * \
		${STAGEDIR}${EXAMPLESDIR})
.for i in linkchecker.apache2.conf linkchecker-completion
	(cd ${WRKSRC}/config && ${INSTALL_DATA} ${i} \
		${STAGEDIR}${EXAMPLESDIR})
.endfor
.for i in check_blacklist.sh check_for_x_errors.sh check_urls.sh
	(cd ${WRKSRC}/doc/examples && ${INSTALL_DATA} ${i} \
		${STAGEDIR}${EXAMPLESDIR})
.endfor

.include <bsd.port.mk>
