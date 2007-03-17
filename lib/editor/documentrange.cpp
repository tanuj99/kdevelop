/* This file is part of KDevelop
    Copyright (C) 2006 Hamish Rodda <rodda@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "documentrange.h"

using namespace KTextEditor;

namespace KDevelop
{

DocumentRange::DocumentRange(const KUrl& document, const KTextEditor::Cursor& start,
        const KTextEditor::Cursor& end, KTextEditor::Range* parent)
  : Range(start, end)
  , m_document(document)
  , m_parentRange(0)
{
  setParentRange(parent);
}

DocumentRange::DocumentRange(const KUrl& document, const KTextEditor::Range& range, KTextEditor::Range* parent)
  : Range(range)
  , m_document(document)
  , m_parentRange(0)
{
  setParentRange(parent);
}

DocumentRange::DocumentRange(const DocumentRange& copy)
  : Range(copy)
  , m_document(copy.document())
  , m_parentRange(0)
{
  setParentRange(copy.parentRange());
}

DocumentRange::~DocumentRange()
{
  setParentRange(0);

  foreach (DocumentRange* child, m_childRanges)
    child->setParentRange(0);
}

const KUrl& DocumentRange::document() const
{
  return m_document;
}

void DocumentRange::setDocument(const KUrl& document)
{
  m_document = document;
}

// kate: indent-width 2;

const QList< DocumentRange * > & DocumentRange::childRanges() const
{
  return m_childRanges;
}

void DocumentRange::setParentRange(KTextEditor::Range* parent)
{
  if (m_parentRange && !m_parentRange->isSmartRange())
    static_cast<DocumentRange*>(m_parentRange)->m_childRanges.removeAll(this);

  m_parentRange = parent;

  if (m_parentRange && !m_parentRange->isSmartRange()) {
    QMutableListIterator<DocumentRange*> it = static_cast<DocumentRange*>(m_parentRange)->m_childRanges;
    it.toBack();
    while (it.hasPrevious()) {
      it.previous();
      if (start() >= it.value()->end()) {
        it.next();
        it.insert(this);
        return;
      }
    }

    it.insert(this);
  }
}

Range* DocumentRange::parentRange() const
{
  return m_parentRange;
}

}
