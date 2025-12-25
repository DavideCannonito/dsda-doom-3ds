/*
    STUBBED SYMBOLS AS THE BEST AS I CAN. Here are symbols referenced from
   gl_preprocess.c that must be deleted or altered in some form.
*/

#ifndef GL_PREPROCESS_STUBS_H
#define GL_PREPROCESS_STUBS_H
#include <stddef.h>
#include <stdint.h>
#include "r_defs.h"

typedef struct GLUtesselator GLUtesselator;

extern enum{
  GLU_TESS_BEGIN,
  GLU_TESS_VERTEX,
  GLU_TESS_ERROR,
  GLU_TESS_COMBINE,
  GLU_TESS_END
} GLU_TESS_ENUM;

void gluTessCallback(GLUtesselator* tess, uint8_t glu_tess_op, void* callback_ptr);
void gluTessBeginPolygon(GLUtesselator* tess, void* data);
void gluTessBeginContour(GLUtesselator* tess);
void gluTessEndContour(GLUtesselator* tess);
GLUtesselator* gluNewTess();
void gluTessVertex(GLUtesselator* tess, void*vertex_address, vertex_t* vertex);
void gluTessEndPolygon(GLUtesselator* tess);
void gluDeleteTess(GLUtesselator* tess);
#endif