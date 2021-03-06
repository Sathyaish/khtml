/*
   Copyright (C) 2007 Eric Seidel <eric@webkit.org>
   Copyright (C) 2007 Nikolas Zimmermann <zimmermann@kde.org>
   Copyright (C) 2008 Apple, Inc

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
 */

#ifndef SVGHKernElement_h
#define SVGHKernElement_h

#if ENABLE(SVG_FONTS)
#include "SVGStyledElement.h"

#include <limits>
#include "Path.h"

namespace khtml
{
class AtomicString;
}

namespace WebCore
{

//class AtomicString;
using khtml::AtomicString;
class SVGFontData;

// Describe an SVG <hkern> element
struct SVGHorizontalKerningPair {
    String unicode1;
    String glyphName1;
    String unicode2;
    String glyphName2;
    double kerning;

    SVGHorizontalKerningPair()
        : kerning(0)
    {
    }
};

class SVGHKernElement : public SVGElement
{
public:
    SVGHKernElement(const QualifiedName &, Document *);
    virtual ~SVGHKernElement();

    void insertedIntoDocument() Q_DECL_OVERRIDE;
    void removedFromDocument() Q_DECL_OVERRIDE;

    bool rendererIsNeeded(RenderStyle *) Q_DECL_OVERRIDE
    {
        return false;
    }

    SVGHorizontalKerningPair buildHorizontalKerningPair() const;

    // KHTML ElementImpl pure virtual method
    quint32 id() const Q_DECL_OVERRIDE
    {
        return SVGNames::textTag.id();
    }
};

} // namespace WebCore

#endif // ENABLE(SVG_FONTS)
#endif
