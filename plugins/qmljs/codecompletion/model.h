/*
 * This file is part of qmljs, the QML/JS language support plugin for KDevelop
 * Copyright (c) 2013 Sven Brauch <svenbrauch@googlemail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License or (at your option) version 3 or any later version
 * accepted by the membership of KDE e.V. (or its successor approved
 * by the membership of KDE e.V.), which shall act as a proxy
 * defined in Section 14 of version 3 of the license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef QMLJS_MODEL_H
#define QMLJS_MODEL_H

#include "codecompletionexport.h"

#include <language/codecompletion/codecompletionmodel.h>

namespace QmlJS {

class KDEVQMLJSCOMPLETION_EXPORT CodeCompletionModel : public KDevelop::CodeCompletionModel
{
    Q_OBJECT
public:
    explicit CodeCompletionModel(QObject* parent);
protected:
    KDevelop::CodeCompletionWorker* createCompletionWorker() override;
};

}

#endif // QMLJS_MODEL_H
