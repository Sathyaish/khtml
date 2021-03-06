/*
    Copyright (C) 2004, 2005, 2006 Nikolas Zimmermann <zimmermann@kde.org>
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

#ifndef SVGPathSegLineto_h
#define SVGPathSegLineto_h

#if ENABLE(SVG)

#include "SVGPathSeg.h"

namespace WebCore
{
class SVGPathSegLinetoAbs : public SVGPathSeg
{
public:
    static PassRefPtr<SVGPathSegLinetoAbs> create(float x, float y)
    {
        return adoptRef(new SVGPathSegLinetoAbs(x, y));
    }
    virtual ~SVGPathSegLinetoAbs();

    unsigned short pathSegType() const Q_DECL_OVERRIDE
    {
        return PATHSEG_LINETO_ABS;
    }
    String pathSegTypeAsLetter() const Q_DECL_OVERRIDE
    {
        return "L";
    }
    String toString() const Q_DECL_OVERRIDE
    {
        return String::format("L %.6lg %.6lg", m_x, m_y);
    }

    void setX(float);
    float x() const;

    void setY(float);
    float y() const;

private:
    SVGPathSegLinetoAbs(float x, float y);

    float m_x;
    float m_y;
};

class SVGPathSegLinetoRel : public SVGPathSeg
{
public:
    static PassRefPtr<SVGPathSegLinetoRel> create(float x, float y)
    {
        return adoptRef(new SVGPathSegLinetoRel(x, y));
    }
    virtual ~SVGPathSegLinetoRel();

    unsigned short pathSegType() const Q_DECL_OVERRIDE
    {
        return PATHSEG_LINETO_REL;
    }
    String pathSegTypeAsLetter() const Q_DECL_OVERRIDE
    {
        return "l";
    }
    String toString() const Q_DECL_OVERRIDE
    {
        return String::format("l %.6lg %.6lg", m_x, m_y);
    }

    void setX(float);
    float x() const;

    void setY(float);
    float y() const;

private:
    SVGPathSegLinetoRel(float x, float y);

    float m_x;
    float m_y;
};

} // namespace WebCore

#endif // ENABLE(SVG)
#endif

