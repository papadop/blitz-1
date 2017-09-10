// -*- C++ -*-
/***************************************************************************
 * blitz/array/iter.h  Basic iterator for arrays.
 *
 * $Id$
 *
 * Copyright (C) 1997-2011 Todd Veldhuizen <tveldhui@acm.org>
 *
 * This file is a part of Blitz.
 *
 * Blitz is free software: you can redistribute it and/or modify 
 * it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * Blitz is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public 
 * License along with Blitz.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * Suggestions:          blitz-devel@lists.sourceforge.net
 * Bugs:                 blitz-support@lists.sourceforge.net    
 *
 * For more information, please see the Blitz++ Home Page:
 *    https://sourceforge.net/projects/blitz/
 *
 ****************************************************************************/
#ifndef BZ_ARRAY_H
 #error <blitz/array/iter.h> must be included via <blitz/array.h>
#endif

#ifndef BZ_ARRAY_ITER_H
#define BZ_ARRAY_ITER_H

#ifdef BZ_HAVE_STL
#include <iterator>
#endif

#if defined(BZ_DEBUG)
#define DataIterator DataIteratorDebug
#define CheckIterator(X,Y)                                                         \
        CheckIteratorValidity(Y,X " invalid iterator (empty array)",               \
                                X " invalid iterator (before beginning of array)", \
                                X " invalid iterator (past end of array)",         \
                              __FILE__, __LINE__)
#else
#define CheckIterator(X,Y)
#endif

BZ_NAMESPACE(blitz)

inline int division(const int a,const int b) { return (a<0) ? -((-a)/b)-1    : a/b; }
inline int modulo(const int a,const int b)   { return (a<0) ? (b-((-a)%b))%b : a%b; }

#if 0
template <typename T, int N>
class VoidIterator {
private:

    void Init(const Array<T,N>& array) {
#if defined(BZ_DEBUG)
        end_ = end_value(array);
#endif
    }

public:

    VoidIterator(): cptr_(0) { }
    VoidIterator(const Array<T,N>& array) : cptr_(const_cast<T*>(array.dataFirst())) {
        Init(array);
    }

    VoidIterator(const Array<T,N>& array, const int) : cptr_(end_value(array)) {
        Init(array);
    }

    bool operator==(const VoidIterator<T,N>& x) const { return cptr_ == x.cptr_; }
    
    bool operator!=(const VoidIterator<T,N>& x) const { return cptr_ != x.cptr_; }
 
    const T& operator*() const {
        CheckIterator("Attempted to dereference",0);
        return *data_;
    }

    const T* restrict operator->() const {
        CheckIterator("Attempted to dereference",0);
        return data_;
    }

#if defined(BZ_DEBUG)
    void CheckIteratorValidity(const int i,const char* mesg1,const char* mesg2,
                               const char* mesg3,const char* file,const int line) const {
        BZPRECHECK_WITH_LOCATION(data_!=0,mesg1,file,line);
        BZPRECHECK_WITH_LOCATION((data_>=beg_+i && data_<=end_+i),((data_<beg_+i) ? mesg2 : mesg3),
                                 file,line);
    }
#endif

protected:

    int order(const int i) const { return i; }
    int init(const Array<T,N>& array,const int i,const int s) const { }
    int incr(const int i) { ++cptr_; return i; }
    int decr(const int i) { --cptr_; return i; }

private:

    static T* end_value(const Array<T,N>& array) {
        T* endval = const_cast<T*>(array.dataFirst()) +
                                   array.stride(array.ordering(0));
        for (int i=0;i<N;++i)
            endval +=  array.stride(i)*(array.extent(i)-1);
        return endval;
    }

    int cptr_;
#if defined(BZ_DEBUG)
    const int end_;
#endif
};
#endif

template <typename T, int N>
class DataIterator {
private:

    void Init(const Array<T,N>& array) {
        order_ = array.ordering();
#if defined(BZ_DEBUG)
        beg_ = array.data();
        end_ = end_value(array)-1;
        if (beg_>end_)
            std::swap(beg_,end_);
#endif
    }

public:

    DataIterator(): data_(0) { }
    DataIterator(const Array<T,N>& array): data_(const_cast<T*>(array.data())) {
        Init(array);
    }

    DataIterator(const Array<T,N>& array, const int) : data_(end_value(array)) {
        Init(array);
    }

    bool operator==(const DataIterator<T,N>& x) const { return data_ == x.data_; }
    bool operator!=(const DataIterator<T,N>& x) const { return data_ != x.data_; }
    bool operator<(const DataIterator<T,N>& x)  const { return data_ <  x.data_; }
    bool operator>(const DataIterator<T,N>& x)  const { return data_ >  x.data_; }
 
    const T& operator*() const {
        CheckIterator("Attempted to dereference",0);
        return *data_;
    }

    const T* restrict operator->() const {
        CheckIterator("Attempted to dereference",0);
        return data_;
    }

#if defined(BZ_DEBUG)
    void CheckIteratorValidity(const int i,const char* mesg1,const char* mesg2,
                               const char* mesg3,const char* file,const int line) const {
        BZPRECHECK_WITH_LOCATION(data_!=0,mesg1,file,line);
        BZPRECHECK_WITH_LOCATION((data_>=beg_+i && data_<=end_+i),((data_<beg_) ? mesg2 : mesg3),
                                 file,line);
    }
#endif

protected:

    int order(const int i) const { return order_(i); }

    int init(const Array<T,N>& array,const int i,const int s) {
        const int r = order(i);
        dataincr_(r) = array.stride(r)-((s==-1) ? 0 : array.extent(s)*array.stride(s));
        return r;
    }

    void add(const int r,const int value) { data_ += value*dataincr_[r]; }

    T* restrict data() const { return data_; }

private:

    TinyVector<int,N> dataincr_, order_;

    static T* end_value(const Array<T,N>& array) {
        T* endval = const_cast<T*>(array.data()) +
                                   array.stride(array.ordering(0));
        for (int i=0;i<N;++i)
            endval +=  array.stride(i)*(array.extent(i)-1);
        return endval;
    }

    T * restrict data_;
#if defined(BZ_DEBUG)
    const T* restrict beg_;
    const T* restrict end_;
#endif
};

template<typename T, int N,typename OPTION>
class ConstArrayIterator: public OPTION {
private:

    //  Initialization common to begin,end constructors.

    void Init(const Array<T,N>& array) {
        // Making internal copies of these avoids keeping
        // a pointer to the array and doing indirection.
        lbound_ = array.lbound();
        ubound_(0) = array.ubound(0)+1;
        for (int i=1,s=OPTION::init(array,0,-1);i<N;++i) {
            s = OPTION::init(array,i,s);
            ubound_(i) = array.ubound(i)+1;
        }
    }

public:

    typedef TinyVector<int,N> Position;

#if defined(BZ_DEBUG)
    using OPTION::CheckIteratorValidity;
#endif

    ConstArrayIterator() : OPTION() { }

    ConstArrayIterator(const Array<T,N>& array) : OPTION(array) {
        Init(array);
        pos_ = lbound_;
    }

    ConstArrayIterator(const Array<T,N>& array, const int) : OPTION(array,0) {
        Init(array);
        pos_ = array.ubound();
        ++pos_(OPTION::order(0));
    }

    ConstArrayIterator<T,N,OPTION>& operator++();
    ConstArrayIterator<T,N,OPTION>& operator--();

    ConstArrayIterator<T,N,OPTION> operator++(int) {
        ConstArrayIterator<T,N,OPTION> tmp = *this;
        ++(*this); 
        return tmp;
    }

    ConstArrayIterator<T,N,OPTION> operator--(int) {
        ConstArrayIterator<T,N,OPTION> tmp = *this;
        --(*this); 
        return tmp;
    }

    ConstArrayIterator<T,N,OPTION>& operator+=(const int inc) {
        add(inc);
        return *this;
    }

    ConstArrayIterator<T,N,OPTION>& operator-=(const int inc) {
        return operator+=(-inc);
    }

    ConstArrayIterator<T,N,OPTION>& operator+(const int inc) const {
        ConstArrayIterator<T,N,OPTION> tmp = *this;
        return tmp += inc;
    }

    ConstArrayIterator<T,N,OPTION>& operator-(const int inc) const {
        ConstArrayIterator<T,N,OPTION> tmp = *this;
        return tmp += -inc;
    }

    // get the current position of the Array iterator in index space
    const Position& position() const { 
        CheckIterator("Array<T,N>::iterator::position() called on",0);
        return pos_; 
    }
   
private:
    Position lbound_, ubound_;

    void add(int);

protected:

    using OPTION::data;

    Position pos_;
};


template<typename T,int N,typename OPTION>
class ArrayIterator : public ConstArrayIterator<T,N,OPTION> {
private:
    typedef ConstArrayIterator<T,N,OPTION> T_base;

#if defined(BZ_DEBUG)
    using T_base::CheckIteratorValidity;
#endif

public:
    ArrayIterator() { }

    ArrayIterator(Array<T,N>& x) : T_base(x) { }

    ArrayIterator(const Array<T,N>& array, const int): T_base(array,0) { }

    T& operator*() const {
        CheckIterator("Attempted to dereference",0);
        return *T_base::data();
    }

    T* restrict operator->() const {
        CheckIterator("Attempted to dereference",0);
        return T_base::data();
    }

    ArrayIterator<T,N>& operator++() {
        T_base::operator++();
        return *this;
    }

    ArrayIterator<T,N> operator++(int) {
        ArrayIterator<T,N> tmp = *this;
        ++(*this); 
        return tmp;
    }

    ArrayIterator<T,N>& operator--() {
        T_base::operator--();
        return *this;
    }

    ArrayIterator<T,N> operator--(int) {
        ArrayIterator<T,N> tmp = *this;
        --(*this); 
        return tmp;
    }
};

template<typename T, int N, typename OPTION>
ConstArrayIterator<T,N,OPTION>& ConstArrayIterator<T,N,OPTION>::operator++() {
    CheckIterator("Attempted to increment",0);

    //   The first loop iteration is peeled as it increases performance.
    //   The same improvement can be obtained by telling the compiler that
    //   the test is likely to be true, but this has too many portability issues
    //   for now.

    // With a compiler peeling loops correctly (or with an effective BZ_LIKELY)
    // macro, this could be simply written as:
    //
    // for (int i=0;i<N;++i) {
    //     const int r = order_(i);
    //     data_ += dataincr_[r];
    //     if (BZ_LIKELY(++pos_(r)!=ubound_(r)))
    //         return *this;
    //     pos_(r) = lbound_(r);
    // }

    const int r0 = OPTION::order(0);
    OPTION::add(r0,1);
    if (BZ_LIKELY(++pos_(r0)!=ubound_(r0)))
        return *this;
    pos_(r0) = lbound_(r0);

    for (int i=1;i<N;++i) {
        const int r = OPTION::order(i);
        OPTION::add(r,1);
        if (BZ_LIKELY(++pos_(r)!=ubound_(r)))
            return *this;
        pos_(r) = lbound_(r);
    }

    // At this place the value of data_ should match that of the end iterator.
    // Do the proper correction to achieve that.
    
    for (int i=1;i<N;++i) {
        const int r = OPTION::order(i);
        OPTION::add(r,-1);
        pos_(r) = ubound_(r)-1;
    }
    pos_(r0) = ubound_(r0);

    return *this;
}

template<typename T, int N, typename OPTION>
ConstArrayIterator<T,N,OPTION>& ConstArrayIterator<T,N,OPTION>::operator--() {
    CheckIterator("Attempted to decrement",1);

    //   The first loop iteration is peeled as it increases performance.
    //   The same improvement can be obtained by telling the compiler that
    //   the test is likely to be true, but this has too many portability issues
    //   for now.

    // With a compiler peeling loops correctly (or with an effective BZ_LIKELY
    // macro, this could be simply written as:
    //
    // for (int i=0;i<N;++i) {
    //     const int r = order_(i);
    //     data_ -= dataincr_[r];
    //     if (BZ_LIKELY(pos_(r)--!=lbound_(r)))
    //         return *this;
    //     pos_(r) = ubound_(r)-1;
    // }

    const int r0 = OPTION::order(0);
    OPTION::add(r0,-1);
    if (BZ_LIKELY(pos_(r0)--!=lbound_(r0)))
        return *this;
    pos_(r0) = ubound_(r0)-1;

    for (int i=1;i<N;++i) {
        const int r = OPTION::order(i);
        OPTION::add(r,-1);
        if (BZ_LIKELY(pos_(r)--!=lbound_(r)))
            return *this;
        pos_(r) = ubound_(r)-1;
    }

    // At this place the value of data_ should match that of the begin iterator.
    // No correction is needed for operator--

    return *this;
}

template<typename T, int N, typename OPTION>
void ConstArrayIterator<T,N,OPTION>::add(int inc) {
    //CheckIterator("Attempted to increment",0);

    //   The first loop iteration could be peeled as it increases performance.
    //   This is not done for the time being.

    for (int i=0;i<N;++i) {
        const int r  = OPTION::order(i);
        const int pr = pos_(r)-lbound_(r);        //  Index from lbound in r direction.
        const int ni = pr+inc;                    //  New index in r direction.
        const int extent = ubound_(r)-lbound_(r); //  Extent in r direction.
        int rinc = modulo(ni,extent);             //  Folded index in r direction.
        int dinc = rinc-pr;
        inc  = division(ni,extent);               //  Carry.
        if (inc<0) {
            dinc -= extent;
        } else if (inc>0) {
            dinc += extent;
        }
        OPTION::add(r,dinc);
        pos_(r) = lbound_(r)+rinc;
        if (BZ_LIKELY(inc==0))
            return;
    }
}

BZ_NAMESPACE_END


#ifdef BZ_HAVE_STL
// support for std::iterator_traits
BZ_NAMESPACE(std)

template <typename T, int N, typename OPTION>
struct iterator_traits< BZ_BLITZ_SCOPE(ConstArrayIterator)<T,N,OPTION> > {
    typedef random_access_iterator_tag iterator_category;
    typedef T                          value_type;
    typedef blitz::diffType            difference_type;
    typedef const T*                   pointer;
    typedef const T&                   reference;
};

template <typename T, int N, typename OPTION>
struct iterator_traits< BZ_BLITZ_SCOPE(ArrayIterator)<T,N,OPTION> > {
    typedef random_access_iterator_tag iterator_category;
    typedef T                          value_type;
    typedef blitz::diffType            difference_type;
    typedef T*                         pointer;
    typedef T&                         reference;
};

BZ_NAMESPACE_END

#endif // BZ_HAVE_STL

#endif // BZ_ARRAY_ITER_H

