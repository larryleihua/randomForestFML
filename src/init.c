#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* .C calls */
extern void classForest(void *, void *, void *, void *, void *, void *, void *, void *,
                        void *, void *, void *, void *, void *, void *, void *, void *,
                        void *, void *, void *, void *, void *, void *, void *, void *);
extern void classRF(void *, void *, void *, void *, void *, void *, void *, void *,
                    void *, void *, void *, void *, void *, void *, void *, void *,
                    void *, void *, void *, void *, void *, void *, void *, void *,
                    void *, void *, void *, void *, void *, void *, void *, void *,
                    void *, void *, void *, void *, void *, void *, void *, void *);
extern void regForest(void *, void *, void *, void *, void *, void *, void *, void *,
                      void *, void *, void *, void *, void *, void *, void *, void *,
                      void *, void *, void *, void *, void *);
extern void regRF(void *, void *, void *, void *, void *, void *, void *, void *,
                  void *, void *, void *, void *, void *, void *, void *, void *,
                  void *, void *, void *, void *, void *, void *, void *, void *,
                  void *, void *, void *, void *, void *, void *, void *, void *,
                  void *, void *, void *, void *, void *, void *, void *, void *,
                  void *, void *);

static const R_CMethodDef CEntries[] = {
  {"classForest", (DL_FUNC) &classForest, 24},
  {"classRF",     (DL_FUNC) &classRF,     40},
  {"regForest",   (DL_FUNC) &regForest,   21},
  {"regRF",       (DL_FUNC) &regRF,       42},
  {NULL, NULL, 0}
};

void R_init_randomForestFML(DllInfo *dll)
{
  R_registerRoutines(dll, CEntries, NULL, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
