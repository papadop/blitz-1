/***************************************************************************
 * blitz/meta/vecassign.h   TinyVector assignment metaprogram
 *
 * $Id$
 *
 * Copyright (C) 1997-2001 Todd Veldhuizen <tveldhui@oonumerics.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * Suggestions:          blitz-dev@oonumerics.org
 * Bugs:                 blitz-bugs@oonumerics.org
 *
 * For more information, please see the Blitz++ Home Page:
 *    http://oonumerics.org/blitz/
 *
 ***************************************************************************
 * $Log$
 * Revision 1.3  2002/12/19 20:41:02  julianc
 * Removed names of function arguments in the static methods of the
 * _bz_meta_vecAssign<0,0> specialization to eliminate compiler
 * warnings about unused variables.
 *
 * Revision 1.2  2001/01/24 20:22:51  tveldhui
 * Updated copyright date in headers.
 *
 * Revision 1.1.1.1  2000/06/19 12:26:13  tveldhui
 * Imported sources
 *
 * Revision 1.2  1998/03/14 00:08:44  tveldhui
 * 0.2-alpha-05
 *
 * Revision 1.1  1997/07/16 14:51:20  tveldhui
 * Update: Alpha release 0.2 (Arrays)
 *
 */

#ifndef BZ_META_VECASSIGN_H
#define BZ_META_VECASSIGN_H

BZ_NAMESPACE(blitz)

template<int N, int I> 
class _bz_meta_vecAssign {
public:
    enum { loopFlag = (I < N-1) ? 1 : 0 };

    template<class T_vector, class T_expr, class T_updater>
    static inline void fastAssign(T_vector& vec, T_expr expr, T_updater u)
    {
        u.update(vec[I], expr._bz_fastAccess(I));
        _bz_meta_vecAssign<N * loopFlag, (I+1) * loopFlag>
           ::fastAssign(vec,expr,u);
    }

    template<class T_vector, class T_expr, class T_updater>
    static inline void assign(T_vector& vec, T_expr expr, T_updater u)
    {
        u.update(vec[I], expr[I]);
        _bz_meta_vecAssign<N * loopFlag, (I+1) * loopFlag>
           ::assign(vec,expr,u);
    }

    template<class T_vector, class T_numtype, class T_updater>
    static inline void assignWithArgs(T_vector& vec, T_updater u,
        T_numtype x0, T_numtype x1=0, T_numtype x2=0, T_numtype x3=0,
        T_numtype x4=0, T_numtype x5=0, T_numtype x6=0, T_numtype x7=0,
        T_numtype x8=0, T_numtype x9=0)
    {
        u.update(vec[I], x0);
        _bz_meta_vecAssign<N * loopFlag, (I+1) * loopFlag>
            ::assignWithArgs(vec, u, x1, x2, x3, x4, x5, x6, x7, x8, x9);
    }
        
};

template<>
class _bz_meta_vecAssign<0,0> {
public:
    template<class T_vector, class T_expr, class T_updater>
    static inline void fastAssign(T_vector&, T_expr, T_updater)
    { }

    template<class T_vector, class T_expr, class T_updater>
    static inline void assign(T_vector&, T_expr, T_updater)
    { }

    template<class T_vector, class T_numtype, class T_updater>
    static inline void assignWithArgs(T_vector&, T_updater,
        T_numtype, T_numtype =0, T_numtype =0, T_numtype =0,
        T_numtype =0, T_numtype =0, T_numtype =0, T_numtype =0,
        T_numtype =0, T_numtype =0)
    {
    }
};

BZ_NAMESPACE_END

#endif // BZ_META_ASSIGN_H
