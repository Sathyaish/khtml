/*
    Copyright (C) 2007 Eric Seidel <eric@webkit.org

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    aint with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
 */

#ifndef RenderSVGTransformableContainer_h
#define RenderSVGTransformableContainer_h

#if ENABLE(SVG)
#include "RenderSVGContainer.h"

namespace WebCore
{

class SVGStyledTransformableElement;
class RenderSVGTransformableContainer : public RenderSVGContainer
{
public:
    RenderSVGTransformableContainer(SVGStyledTransformableElement *);

    bool calculateLocalTransform() Q_DECL_OVERRIDE;
};
}

#endif // ENABLE(SVG)
#endif // RenderSVGTransformableContainer_h
