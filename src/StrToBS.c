/* $Xorg: StrToBS.c,v 1.4 2001/02/09 02:03:53 xorgcvs Exp $ */

/* 
 
Copyright 1988, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from The Open Group.

*/

#include <X11/Intrinsic.h>
#include "Converters.h"
#include "CharSet.h"

#define	done(address, type) \
	{ (*toVal).size = sizeof(type); (*toVal).addr = (XPointer) address; }

/* ARGSUSED */
void
XmuCvtStringToBackingStore (args, num_args, fromVal, toVal)
    XrmValue	*args;		/* unused */
    Cardinal	*num_args;	/* unused */
    XrmValuePtr fromVal;
    XrmValuePtr toVal;
{
    char	lowerString[40];
    XrmQuark	q;
    static int	backingStoreType;
    static XrmQuark XtQEnotUseful, XtQEwhenMapped, XtQEalways, XtQEdefault;
    static int haveQuarks = 0;

    if (*num_args != 0)
        XtWarning("String to BackingStore conversion needs no extra arguments");
    if (!haveQuarks) {
	XmuCopyISOLatin1Lowered (lowerString, XtEnotUseful);
	XtQEnotUseful = XrmStringToQuark(lowerString);
	XmuCopyISOLatin1Lowered (lowerString, XtEwhenMapped);
	XtQEwhenMapped = XrmStringToQuark(lowerString);
	XmuCopyISOLatin1Lowered (lowerString, XtEalways);
	XtQEalways = XrmStringToQuark(lowerString);
	XmuCopyISOLatin1Lowered (lowerString, XtEdefault);
	XtQEdefault = XrmStringToQuark(lowerString);
	haveQuarks = 1;
    }
    if (strlen ((char*)fromVal->addr) >= sizeof lowerString)
        XtStringConversionWarning((char *) fromVal->addr, "BackingStore");
    XmuCopyISOLatin1Lowered (lowerString, (char *) fromVal->addr);
    q = XrmStringToQuark (lowerString);
    if (q == XtQEnotUseful) {
	backingStoreType = NotUseful;
	done (&backingStoreType, int);
    } else if (q == XtQEwhenMapped) {
    	backingStoreType = WhenMapped;
	done (&backingStoreType, int);
    } else if (q == XtQEalways) {
	backingStoreType = Always;
	done (&backingStoreType, int);
    } else if (q == XtQEdefault) {
    	backingStoreType = Always + WhenMapped + NotUseful;
	done (&backingStoreType, int);
    } else {
        XtStringConversionWarning((char *) fromVal->addr, "BackingStore");
    }
}
