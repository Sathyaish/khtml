/*
 * This file is part of the render object implementation for KHTML.
 *
 * Copyright (C) 1999-2003 Lars Knoll (knoll@kde.org)
 *           (C) 1999-2003 Antti Koivisto (koivisto@kde.org)
 *           (C) 2002-2003 Dirk Mueller (mueller@kde.org)
 *           (C) 2003 Apple Computer, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#ifndef RENDER_INLINE_H
#define RENDER_INLINE_H

#include "render_flow.h"

namespace khtml
{

class RenderInline : public RenderFlow
{
public:
    RenderInline(DOM::NodeImpl *node) : RenderFlow(node), m_isContinuation(false) {}

    const char *renderName() const Q_DECL_OVERRIDE;

    bool isRenderInline() const Q_DECL_OVERRIDE
    {
        return true;
    }
    bool isInlineFlow() const Q_DECL_OVERRIDE
    {
        return true;
    }
    bool childrenInline() const Q_DECL_OVERRIDE
    {
        return true;
    }

    bool isInlineContinuation() const Q_DECL_OVERRIDE;

    void addChildToFlow(RenderObject *newChild, RenderObject *beforeChild) Q_DECL_OVERRIDE;

    void splitInlines(RenderBlock *fromBlock, RenderBlock *toBlock, RenderBlock *middleBlock,
                      RenderObject *beforeChild, RenderFlow *oldCont);

    void splitFlow(RenderObject *beforeChild, RenderBlock *newBlockBox,
                   RenderObject *newChild, RenderFlow *oldCont);

    void setStyle(RenderStyle *_style) Q_DECL_OVERRIDE;
    void attach() Q_DECL_OVERRIDE;

    void layout() Q_DECL_OVERRIDE
    {
        setNeedsLayout(false);    // Do nothing for layout()
    }

    void paint(PaintInfo &, int tx, int ty) Q_DECL_OVERRIDE;

    bool nodeAtPoint(NodeInfo &info, int _x, int _y, int _tx, int _ty, HitTestAction hitTestAction, bool inside) Q_DECL_OVERRIDE;

    void calcMinMaxWidth() Q_DECL_OVERRIDE;

    // overrides RenderObject
    bool requiresLayer() const Q_DECL_OVERRIDE
    {
        return isRelPositioned();
    }

    short width() const Q_DECL_OVERRIDE;
    int height() const Q_DECL_OVERRIDE;

    int inlineXPos() const Q_DECL_OVERRIDE;
    int inlineYPos() const Q_DECL_OVERRIDE;

    // used to calculate offsetWidth/Height.  Overridden by inlines (render_flow) to return
    // the remaining width on a given line (and the height of a single line).
    int offsetLeft() const Q_DECL_OVERRIDE;
    int offsetTop() const Q_DECL_OVERRIDE;

    RenderPosition positionForCoordinates(int x, int y) Q_DECL_OVERRIDE;

    void caretPos(int offset, int flags, int &_x, int &_y, int &width, int &height) const Q_DECL_OVERRIDE;
    void paintOutlines(QPainter *p, int tx, int ty);

protected:
    static RenderInline *cloneInline(RenderFlow *src);
    void paintOutlinePath(QPainter *p, int tx, int ty, const QPoint *begin, const QPoint *end, BorderSide startingBS, int initialDirection, BorderSide endingBS);

private:
    bool m_isContinuation : 1; // Whether or not we're a continuation of an inline.

};

} // namespace

#endif // RENDER_BLOCK_H

