/* This file is part of KDevelop
Copyright (C) 2006 Adam Treat <treat@kde.org>
Copyright (C) 2007 Andreas Pakulat <apaku@gmx.de>

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

#ifndef KDEVCONFIGURATION_H
#define KDEVCONFIGURATION_H

#include <QObject>

#include <kconfig.h>
#include <ksharedconfig.h>

#include "kdevexport.h"

namespace KDevelop
{
class ICore;
class IProject;

/**
The interface to KDevelop's config objects.
Developers using the KDevelop API should use these config objects instead of
the standard KGlobal::config object.  Again, DO NOT USE KGlobal::config() as
it can cause unexpected syncing issues.
@todo the config-parameters need to take an IProject pointer
@todo listen to currentProject changed signal from project controller, so we can update the settings dialog
*/
class KDEVPLATFORM_EXPORT Configuration : public QObject
{
    Q_OBJECT
public:
    enum Mode
    {
        Standard= 0x0,
        LocalProject = 0x1,
        GlobalProject = 0x2
    };
    Q_DECLARE_FLAGS(Modes, Mode)

    static Configuration *self();
    static void initialize( ICore* core );
    virtual ~Configuration();

    /**
     * Used by KCM dialogs to determine which file to save settings to.
     * @return the Mode describing the file to save settings to.
     */
    Mode mode();

    void settingsDialog();

    /**
     * @return A pointer to the standard config object.  This object will point
     * to different config files depending on whether a project is opened.
     * If a project IS NOT opened then the config object will consist of the
     * settings found in $KDEINSTALL/config/kdeveloprc and $USER/.kde/config/kdeveloprc.
     * THE MOST SPECIFIC FILE WILL BE $USER/.kde/config/kdeveloprc.
     *
     * If a project IS opened then it will additionally consist of the settings
     * found in the global project file and the local project file.  THE MOST
     * SPECIFIC FILE WILL BE THE GLOBAL PROJECT FILE.
     */
    KConfig *standard( IProject* );

    /**
     * @return A pointer to the local project config object.  This object will point
     * to different config files depending on whether a project is opened.
     * If a project IS NOT opened then the config object will consist of the
     * settings found in $KDEINSTALL/config/kdeveloprc and $USER/.kde/config/kdeveloprc.
     * THE MOST SPECIFIC FILE WILL BE $USER/.kde/config/kdeveloprc.
     *
     * If a project IS opened then it will additionally consist of the settings
     * found in the global project file and the local project file.  THE MOST
     * SPECIFIC FILE WILL BE THE LOCAL PROJECT FILE.
     */
    KConfig *localProject( IProject*  );

    /**
     * @return A pointer to the global project config object.  This object will point
     * to different config files depending on whether a project is opened.
     * If a project IS NOT opened then the config object will consist of the
     * settings found in $KDEINSTALL/config/kdeveloprc and $USER/.kde/config/kdeveloprc.
     * THE MOST SPECIFIC FILE WILL BE $USER/.kde/config/kdeveloprc.
     *
     * If a project IS opened then it will additionally consist of the settings
     * found in the global project file and the local project file.  THE MOST
     * SPECIFIC FILE WILL BE THE LOCAL GLOBAL PROJECT FILE.
     *
     * This function should RARELY be used as it is operationally the same as standard()
     */
    KConfig *globalProject( IProject*  );

    /**
     * @return A shared pointer to the standard config object.
     */
    KSharedConfig::Ptr sharedStandard( IProject*  );

    /**
     * @return A shared pointer to the local project config object.
     */
    KSharedConfig::Ptr sharedLocalProject( IProject*  );

    /**
     * @return A shared pointer to the global project config object.
     */
    KSharedConfig::Ptr sharedGlobalProject( IProject*  );


    /**
     * same as standard() but uses the currently selected project
     * @see standard( IProject* )
     */
    KConfig *standardCurrentProject();

    /**
     * same as local() but uses the currently selected project
     * @see local( IProject* )
     */
    KConfig *localCurrentProject();

    /**
     * same as global() but uses the currently selected project
     * @see global( IProject* )
     */
    KConfig *globalCurrentProject();

    KSharedConfig::Ptr sharedStandardCurrentProject();
    KSharedConfig::Ptr sharedLocalCurrentProject();
    KSharedConfig::Ptr sharedGlobalCurrentProject();

private:
    Configuration(ICore *parent = 0);
    static Configuration *m_self;
    Q_PRIVATE_SLOT(d, void local() )
    Q_PRIVATE_SLOT(d, void shared() )
    Q_PRIVATE_SLOT(d, void global() )
    class ConfigurationPrivate* const d;
};

}
#endif

// kate: space-indent on; indent-width 4; tab-width: 4; replace-tabs on; auto-insert-doxygen on
