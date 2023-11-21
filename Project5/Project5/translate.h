﻿// 모델 변환
#ifndef MODEL_TRANSLATOR_H
#define MODEL_TRANSLATOR_H
#include "config.h"

void setCamera();
void setProjection(int projectionMode);
void setLight();
void setTransformLight(int idx);
void setTransform(int idx);
void setColorLight(int idx);
void finishTransform(int idx);
void modelOutput(int idx);

#endif
