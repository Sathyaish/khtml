/*
    Copyright (C) 2004, 2005, 2007, 2008 Nikolas Zimmermann <zimmermann@kde.org>
                  2004, 2005, 2006 Rob Buis <buis@kde.org>

    This file is part of the KDE project

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

#ifndef SVGGElement_h
#define SVGGElement_h

#if ENABLE(SVG)
#include "SVGExternalResourcesRequired.h"
#include "SVGLangSpace.h"
#include "SVGStyledTransformableElement.h"
#include "SVGTests.h"

namespace WebCore
{

class SVGGElement : public SVGStyledTransformableElement,
    public SVGTests,
    public SVGLangSpace,
    public SVGExternalResourcesRequired
{
public:
    SVGGElement(const QualifiedName &, Document *);
    virtual ~SVGGElement();

    bool isValid() const Q_DECL_OVERRIDE
    {
        return SVGTests::isValid();
    }

    void parseMappedAttribute(MappedAttribute *) Q_DECL_OVERRIDE;
    void svgAttributeChanged(const QualifiedName &) Q_DECL_OVERRIDE;
    using DOM::NodeImpl::childrenChanged;
    void childrenChanged(bool changedByParser = false, Node *beforeChange = nullptr, Node *afterChange = nullptr, int childCountDelta = 0) Q_DECL_OVERRIDE;

    RenderObject *createRenderer(RenderArena *, RenderStyle *) Q_DECL_OVERRIDE;

    // KHTML ElementImpl pure virtual method
    quint32 id() const Q_DECL_OVERRIDE
    {
        return SVGNames::gTag.id();
    }
protected:
    const SVGElement *contextElement() const Q_DECL_OVERRIDE
    {
        return this;
    }

private:
    ANIMATED_PROPERTY_FORWARD_DECLARATIONS(SVGExternalResourcesRequired, bool, ExternalResourcesRequired, externalResourcesRequired)

private:
    friend class SVGUseElement;
    AffineTransform localMatrix() const;
};

} // namespace WebCore

#endif // ENABLE(SVG)
#endif
