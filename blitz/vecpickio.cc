/*
 * $Id$
 *
 * Copyright (C) 1997 Todd Veldhuizen <tveldhui@oonumerics.org>
 * All rights reserved.  Please see <blitz/blitz.h> for terms and
 * conditions of use.
 *
 * $Log$
 * Revision 1.1  2000/06/19 12:26:09  tveldhui
 * Initial revision
 *
 * Revision 1.2  1997/01/24 14:42:00  tveldhui
 * Periodic RCS update
 *
 */

#ifndef BZ_VECPICKIO_CC
#define BZ_VECPICKIO_CC

#ifndef BZ_VECPICK_H
 #error <blitz/vecpickio.cc> must be included via <blitz/vecpick.h>
#endif // BZ_VECPICK_H

BZ_NAMESPACE(blitz)

template<class P_numtype>
ostream& operator<<(ostream& os, const VectorPick<P_numtype>& x)
{
    Vector<P_numtype> y(x.length());
    y = x;
    os << y;
    return os;
}

BZ_NAMESPACE_END

#endif // BZ_VECPICKIO_CC