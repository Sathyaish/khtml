/*
 * This file is part of the WebKit project.
 *
 * Copyright (C) 2006 Oliver Hunt <ojh16@student.canterbury.ac.nz>
 *           (C) 2006 Apple Computer Inc.
 *           (C) 2007 Nikolas Zimmermann <zimmermann@kde.org>
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

#ifndef SVGRootInlineBox_h
#define SVGRootInlineBox_h

#if ENABLE(SVG)
#include "rendering/render_line.h" // RootInlineBox
#include "SVGCharacterLayoutInfo.h"
#include "rendering/render_text.h"

namespace WebCore
{

using namespace khtml;

//class InlineTextBox;
class RenderSVGRoot;
class SVGInlineTextBox;

struct LastGlyphInfo {
    LastGlyphInfo() : isValid(false) { }

    String unicode;
    String glyphName;
    bool isValid;
};

class SVGRootInlineBox : public RootInlineBox
{
public:
    SVGRootInlineBox(RenderObject *obj)
        : RootInlineBox(obj)
    {
    }

    bool isSVGRootInlineBox() const Q_DECL_OVERRIDE
    {
        return true;
    }

    void paint(RenderObject::PaintInfo &, int tx, int ty) Q_DECL_OVERRIDE;

    virtual int placeBoxesHorizontally(int x, int &leftPosition, int &rightPosition, bool &needsWordSpacing);
    virtual void verticallyAlignBoxes(int &heightOfBlock);

    virtual void computePerCharacterLayoutInformation();

    // Used by SVGInlineTextBox
    const Vector<SVGTextChunk> &svgTextChunks() const;

    void walkTextChunks(SVGTextChunkWalkerBase *, const SVGInlineTextBox *textBox = nullptr);

private:
    friend struct SVGRootInlineBoxPaintWalker;

    void layoutInlineBoxes();
    void layoutInlineBoxes(InlineFlowBox *start, Vector<SVGChar>::iterator &it, int &minX, int &maxX, int &minY, int &maxY);

    void buildLayoutInformation(InlineFlowBox *start, SVGCharacterLayoutInfo &);
    void buildLayoutInformationForTextBox(SVGCharacterLayoutInfo &, InlineTextBox *, LastGlyphInfo &);

    void buildTextChunks(Vector<SVGChar> &, Vector<SVGTextChunk> &, InlineFlowBox *start);
    void buildTextChunks(Vector<SVGChar> &, InlineFlowBox *start, SVGTextChunkLayoutInfo &);
    void layoutTextChunks();

    SVGTextDecorationInfo retrievePaintServersForTextDecoration(RenderObject *start);

private:
    Vector<SVGChar> m_svgChars;
    Vector<SVGTextChunk> m_svgTextChunks;
};

// Shared with SVGRenderTreeAsText / SVGInlineTextBox
/*khtml TextRun svgTextRunForInlineTextBox(const UChar*, int len, RenderStyle* style, const InlineTextBox* textBox, float xPos);*/
FloatPoint topLeftPositionOfCharacterRange(Vector<SVGChar>::iterator start, Vector<SVGChar>::iterator end);
float cummulatedWidthOfInlineBoxCharacterRange(SVGInlineBoxCharacterRange &range);
float cummulatedHeightOfInlineBoxCharacterRange(SVGInlineBoxCharacterRange &range);

RenderSVGRoot *findSVGRootObject(RenderObject *start);

} // namespace WebCore

#endif // ENABLE(SVG)

#endif // SVGRootInlineBox_h
