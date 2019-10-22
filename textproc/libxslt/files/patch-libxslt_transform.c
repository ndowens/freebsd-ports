From ee31512213544a869418a06a819e9cb9a7346f65 Mon Sep 17 00:00:00 2001
From: Nick Wellnhofer <wellnhofer@aevum.de>
Date: Sat, 17 Aug 2019 16:51:53 +0200
Subject: [PATCH] Fix dangling pointer in xsltCopyText

xsltCopyText didn't reset ctxt->lasttext in some cases which could
lead to various memory errors in relation with CDATA sections in input
documents.

Found by OSS-Fuzz.
---
 libxslt/transform.c | 2 ++
 1 file changed, 2 insertions(+)

diff --git a/libxslt/transform.c b/libxslt/transform.c
index ed5afacb..477265c2 100644
--- libxslt/transform.c
+++ libxslt/transform.c
@@ -1090,6 +1090,8 @@ xsltCopyText(xsltTransformContextPtr ctxt, xmlNodePtr target,
 	    if ((copy->content = xmlStrdup(cur->content)) == NULL)
 		return NULL;
 	}
+
+	ctxt->lasttext = NULL;
     } else {
         /*
 	 * normal processing. keep counters to extend the text node
-- 
2.23.0

