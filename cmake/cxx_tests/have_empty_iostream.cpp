// DESCRIPTION
//
//   Check if the C++ compiler allow the empty iostream constructor.
//   Ok before gcc3, not after.
//   In sync with AC_CXX_HAVE_EMPTY_IOSTREAM (2008-04-12).
//
// COPYLEFT
//
//   Copyright (c) 2009 Theo Papadopoulo <Theodore.Papadopoulo@sophia.inria.fr>
//   Copyright (c) 2008 Alain BARBET <alian@cpan.org>
//
//   This program is free software; you can redistribute it and/or modify it
//   under the terms of the GNU General Public License as published by the
//   Free Software Foundation; either version 2 of the License, or (at your
//   option) any later version.
//
//   This program is distributed in the hope that it will be useful, but
//   WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
//   Public License for more details.
//
//   You should have received a copy of the GNU General Public License along
//   with this program. If not, see <http://www.gnu.org/licenses/>.
//
//   As a special exception, the respective Autoconf Macro's copyright owner
//   gives unlimited permission to copy, distribute and modify the configure
//   scripts that are the output of Autoconf when processing the Macro. You
//   need not follow the terms of the GNU General Public License when using
//   or distributing such scripts, even though portions of the text of the
//   Macro appear in them. The GNU General Public License (GPL) does govern
//   all other use of the material that constitutes the Autoconf Macro.
//
//   This special exception to the GPL applies to versions of the Autoconf
//   Macro released by the Autoconf Macro Archive. When you make and
//   distribute a modified version of the Autoconf Macro, you may extend this
//   special exception to the GPL to apply to your modified version as well.

#include <iostream>
#ifdef HAVE_NAMESPACES
using namespace std;
#endif

int main() {
    iostream iostr;
    return 0;
}
