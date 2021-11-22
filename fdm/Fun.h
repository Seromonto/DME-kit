/****************************************************************************//*
* MIT License
* Copyright (c) 2020 Dawid Marzec
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom
* the Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
* IN THE SOFTWARE.
******************************************************************************/
#ifndef FUN_H
#define FUN_H

#include <iostream>

using namespace std;

template<class TYPE>
static void erase( TYPE *ptr )
{
    if( ptr ) delete ptr; ptr = 0;
}

template <class TYP> static TYP Interpolation( TYP x  , TYP y_val[] ,  TYP x_data[]  , int n )
{
   int z =  0;    int zs = 0;    int zk = 0;

   if( x <= x_data[0] )        { return y_val[0];   }
   else if( x >= x_data[n-1] ) { return y_val[n-1]; }
   zs = 0;    zk = n-1;

   while( zk-zs > 1 )
   {
     z = ( zs + zk ) / 2;
     if( x <= x_data[z] )
       zk = z;
     else
       zs = z;
   }

   return ( y_val[zs] + ( y_val[zs] - y_val[zs] ) / ( x_data[zk] - x_data[zs] ) * ( x - x_data[zs] ) );
}



#endif // FUN_H
