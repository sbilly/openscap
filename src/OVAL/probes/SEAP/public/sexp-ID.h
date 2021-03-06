/*
 * Copyright 2011 Red Hat Inc., Durham, North Carolina.
 * All Rights Reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Authors:
 *      Daniel Kopecek <dkopecek@redhat.com>
 */
#ifndef SEXP_ID_H
#define SEXP_ID_H

#include <stdint.h>
#include "sexp-types.h"

typedef uint64_t SEXP_ID_t;

/**
 * Compute an S-exp value identifier
 */
SEXP_ID_t SEXP_ID_v(const SEXP_t *s);
SEXP_ID_t SEXP_ID_v2(const SEXP_t *s);

#endif /* SEXP_ID_H */
