/*
    STUBBED SYMBOLS AS THE BEST AS I CAN. Here are symbols referenced from
   gl_preprocess.c that must be deleted or altered in some form.
*/

#include "gl_preprocess_stubs.h"


GLUtesselator *gluNewTess() { return NULL; }

void gluTessCallback(GLUtesselator *tess, uint8_t glu_tess_op,
                     void *callback_ptr) {
  return;
}
void gluTessBeginPolygon(GLUtesselator *tess, void *data) { return; }
void gluTessBeginContour(GLUtesselator *tess) { return; }
void gluTessEndContour(GLUtesselator *tess) { return; }

void gluTessVertex(GLUtesselator *tess, void *vertex_address,
                   vertex_t *vertex) {
  return;
}

void gluTessEndPolygon(GLUtesselator *tess) { return; }

void gluDeleteTess(GLUtesselator *tess) { return; }
