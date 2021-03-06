/*
 * This file is part of the DOM implementation for KDE.
 *
 * Copyright (C) 1999-2003 Lars Knoll (knoll@kde.org)
 *           (C) 2001-2003 Dirk Mueller (mueller@kde.org)
 *           (C) 1999 Antti Koivisto (koivisto@kde.org)
 *           (C) 2003 Apple Computer, Inc
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
#ifndef _DOM_CharacterDataImpl_h_
#define _DOM_CharacterDataImpl_h_

#include "xml/dom_nodeimpl.h"
#include "dom/dom_string.h"

namespace DOM
{

class DocumentImpl;
class CharacterData;
class Text;

class CharacterDataImpl : public NodeImpl
{
public:
    CharacterDataImpl(DocumentImpl *doc, DOMStringImpl *_text);

    virtual ~CharacterDataImpl();

    // DOM methods & attributes for CharacterData

    virtual void setData(const DOMString &_data, int &exceptioncode);
    virtual unsigned long length() const;
    virtual DOMString substringData(const unsigned long offset, const unsigned long count, int &exceptioncode);
    virtual void appendData(const DOMString &arg, int &exceptioncode);
    virtual void insertData(const unsigned long offset, const DOMString &arg, int &exceptioncode);
    virtual void deleteData(const unsigned long offset, const unsigned long count, int &exceptioncode);
    virtual void replaceData(const unsigned long offset, const unsigned long count, const DOMString &arg, int &exceptioncode);

    bool containsOnlyWhitespace() const Q_DECL_OVERRIDE;

    // DOM methods overridden from  parent classes

    DOMString nodeValue() const Q_DECL_OVERRIDE;
    void setNodeValue(const DOMString &_nodeValue, int &exceptioncode) Q_DECL_OVERRIDE;

    // Other methods (not part of DOM)

    DOMStringImpl *string() const
    {
        return str;
    }
    DOMString data() const
    {
        return str;
    }

    virtual void checkCharDataOperation(const unsigned long offset, int &exceptioncode);

    bool offsetInCharacters() const Q_DECL_OVERRIDE
    {
        return true;
    }
    int maxCharacterOffset() const Q_DECL_OVERRIDE
    {
        return static_cast<int>(length());
    }

    long maxOffset() const Q_DECL_OVERRIDE;
    long caretMinOffset() const Q_DECL_OVERRIDE;
    long caretMaxOffset() const Q_DECL_OVERRIDE;
    unsigned long caretMaxRenderedOffset() const Q_DECL_OVERRIDE;

    bool rendererIsNeeded(khtml::RenderStyle *) Q_DECL_OVERRIDE;

protected:
    // note: since DOMStrings are shared, str should always be copied when making
    // a change or returning a string
    DOMStringImpl *str;

    void dispatchModifiedEvent(DOMStringImpl *prevValue);
};

// ----------------------------------------------------------------------------

class CommentImpl : public CharacterDataImpl
{
public:
    CommentImpl(DocumentImpl *doc, DOMStringImpl *_text)
        : CharacterDataImpl(doc, _text) {}
    CommentImpl(DocumentImpl *doc)
        : CharacterDataImpl(doc, nullptr) {}
    // DOM methods overridden from  parent classes
    DOMString nodeName() const Q_DECL_OVERRIDE;
    unsigned short nodeType() const Q_DECL_OVERRIDE;
    WTF::PassRefPtr<NodeImpl> cloneNode(bool deep) Q_DECL_OVERRIDE;

    // Other methods (not part of DOM)

    Id id() const Q_DECL_OVERRIDE;
    bool childTypeAllowed(unsigned short type) Q_DECL_OVERRIDE;

    DOMString toString() const Q_DECL_OVERRIDE;
};

// ----------------------------------------------------------------------------

class TextImpl : public CharacterDataImpl
{
public:
    TextImpl(DocumentImpl *impl, DOMStringImpl *_text)
        : CharacterDataImpl(impl, _text) {}
    TextImpl(DocumentImpl *impl)
        : CharacterDataImpl(impl, nullptr) {}

    // DOM methods & attributes for CharacterData

    TextImpl *splitText(const unsigned long offset, int &exceptioncode);

    // DOM Level 3: http://www.w3.org/TR/DOM-Level-3-Core/core.html#ID-1312295772
    DOMString wholeText() const;
    TextImpl *replaceWholeText(const DOMString &newText, int &ec);

    // DOM methods overridden from  parent classes
    DOMString nodeName() const Q_DECL_OVERRIDE;
    unsigned short nodeType() const Q_DECL_OVERRIDE;
    WTF::PassRefPtr<NodeImpl> cloneNode(bool deep) Q_DECL_OVERRIDE;

    // Other methods (not part of DOM)

    bool isTextNode() const Q_DECL_OVERRIDE
    {
        return true;
    }
    Id id() const Q_DECL_OVERRIDE;
    void attach() Q_DECL_OVERRIDE;
    bool rendererIsNeeded(khtml::RenderStyle *) Q_DECL_OVERRIDE;
    khtml::RenderObject *createRenderer(khtml::RenderArena *, khtml::RenderStyle *) Q_DECL_OVERRIDE;
    void recalcStyle(StyleChange = NoChange) Q_DECL_OVERRIDE;
    bool affectedByNoInherit() const Q_DECL_OVERRIDE
    {
        return true;
    }
    bool childTypeAllowed(unsigned short type) Q_DECL_OVERRIDE;

    DOMStringImpl *renderString() const;

    DOMString toString() const Q_DECL_OVERRIDE;
    /** Return the text for the node, with < replaced with &lt; and so on.
     *  @param startOffset The number of characters counted from the left, zero indexed, counting "<" as one character, to start from.  Use -1 to start from 0.
     *  @param endOffset The number of characters counted from the left, zero indexed, counting "<" as one character, to end on.  Use -1 to end at the end of the string.
     *  @return An html escaped version of the substring.
     */
    DOMString toString(long long startOffset, long long endOffset) const;
protected:
    virtual TextImpl *createNew(DOMStringImpl *_str);
};

// ----------------------------------------------------------------------------

class CDATASectionImpl : public TextImpl
{
public:
    CDATASectionImpl(DocumentImpl *impl, DOMStringImpl *_text)
        : TextImpl(impl, _text) {}
    CDATASectionImpl(DocumentImpl *impl)
        : TextImpl(impl) {}

    // DOM methods overridden from  parent classes
    DOMString nodeName() const Q_DECL_OVERRIDE;
    unsigned short nodeType() const Q_DECL_OVERRIDE;
    WTF::PassRefPtr<NodeImpl> cloneNode(bool deep) Q_DECL_OVERRIDE;

    // Other methods (not part of DOM)

    bool childTypeAllowed(unsigned short type) Q_DECL_OVERRIDE;

    DOMString toString() const Q_DECL_OVERRIDE;

protected:
    TextImpl *createNew(DOMStringImpl *_str) Q_DECL_OVERRIDE;
};

// ----------------------------------------------------------------------------

class EditingTextImpl : public TextImpl
{
public:
    EditingTextImpl(DocumentImpl *impl, const DOMString &text);
    EditingTextImpl(DocumentImpl *impl);
    virtual ~EditingTextImpl();

    bool rendererIsNeeded(khtml::RenderStyle *) Q_DECL_OVERRIDE;
};

} //namespace
#endif
