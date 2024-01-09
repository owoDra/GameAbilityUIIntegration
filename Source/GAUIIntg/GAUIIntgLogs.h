// Copyright (C) 2024 owoDra

#pragma once

#include "Logging/LogMacros.h"

GAUIINTG_API DECLARE_LOG_CATEGORY_EXTERN(LogGAUII, Log, All);

#if !UE_BUILD_SHIPPING

#define GAUIILOG(FormattedText, ...) UE_LOG(LogGAUII, Log, FormattedText, __VA_ARGS__)

#define GAUIIENSURE(InExpression) ensure(InExpression)
#define GAUIIENSURE_MSG(InExpression, InFormat, ...) ensureMsgf(InExpression, InFormat, __VA_ARGS__)
#define GAUIIENSURE_ALWAYS_MSG(InExpression, InFormat, ...) ensureAlwaysMsgf(InExpression, InFormat, __VA_ARGS__)

#define GAUIICHECK(InExpression) check(InExpression)
#define GAUIICHECK_MSG(InExpression, InFormat, ...) checkf(InExpression, InFormat, __VA_ARGS__)

#else

#define GAUIILOG(FormattedText, ...)

#define GAUIIENSURE(InExpression) InExpression
#define GAUIIENSURE_MSG(InExpression, InFormat, ...) InExpression
#define GAUIIENSURE_ALWAYS_MSG(InExpression, InFormat, ...) InExpression

#define GAUIICHECK(InExpression) InExpression
#define GAUIICHECK_MSG(InExpression, InFormat, ...) InExpression

#endif