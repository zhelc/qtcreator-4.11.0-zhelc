/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#pragma once

#include <extensionsystem/iplugin.h>

#if defined(PLUGIN2_LIBRARY)
#  define PLUGIN2_EXPORT Q_DECL_EXPORT
#else
#  define PLUGIN2_EXPORT Q_DECL_IMPORT
#endif

namespace Plugin2 {

class PLUGIN2_EXPORT MyPlugin2 : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "plugin" FILE "plugin2.json")

public:
    MyPlugin2() = default;
    ~MyPlugin2() final;

    bool initialize(const QStringList &arguments, QString *errorString) final;
    void extensionsInitialized() final;

private:
    bool initializeCalled = false;
    QObject *object1 = nullptr;
    QObject *object2 = nullptr;
};

} // namespace Plugin2
